" Vim syntax file
" Language:	Scriptix
" Maintainer:	Sean Middleditch <elanthis@awesomeplay.com>
" Originally c.vim by Bram Moolenaar <Bram@vim.org>
" Last Change:	2002 Oct 06

" Add to your vimrc:
" au BufNewFile,BufRead *.sx			setf scriptix

" For version 5.x: Clear all syntax items
" For version 6.x: Quit when a syntax file was already loaded
if version < 600
  syntax clear
elseif exists("b:current_syntax")
  finish
endif

" A bunch of useful C keywords
syn keyword	cStatement	break return continue
syn keyword	cConditional	if else
syn keyword	cRepeat		while until for do
syn keyword	cClass		new
syn keyword	cSpecOp		in

syn keyword	cTodo		contained TODO FIXME XXX

" cCommentGroup allows adding matches for special things in comments
syn cluster	cCommentGroup	contains=cTodo

" String and Character constants
" Highlight special characters (those which have a backslash) differently
syn match	cSpecial	display contained "\\\(x\x\+\|\o\{1,3}\|.\|$\)"
if !exists("c_no_utf")
  syn match	cSpecial	display contained "\\\(u\x\{4}\|U\x\{8}\)"
endif
syn region	cString		start=+L\="+ skip=+\\\\\|\\"+ end=+"+ contains=cSpecial
syn region	cString		start=+L\='+ skip=+\\\\\|\\'+ end=+'+

syn match	cSpecialError	"L\='\\[^'\"?\\abfnrtv]'"
syn match	cSpecialCharacter "L\='\\['\"?\\abfnrtv]'"
syn match	cSpecialCharacter display "L\='\\\o\{1,3}'"
syn match	cSpecialCharacter display "'\\x\x\{1,2}'"
syn match	cSpecialCharacter display "L'\\x\x\+'"

"when wanted, highlight trailing white space
if exists("c_space_errors")
  if !exists("c_no_trail_space_error")
    syn match	cSpaceError	display excludenl "\s\+$"
  endif
  if !exists("c_no_tab_space_error")
    syn match	cSpaceError	display " \+\t"me=e-1
  endif
endif

"catch errors caused by wrong parenthesis and brackets
syn cluster	cParenGroup	contains=cParenError,cIncluded,cSpecial,cCommentSkip,cCommentString,cComment2String,@cCommentGroup,cCommentStartError,cUserCont,cUserLabel,cCommentSkip,cOctalZero,cNumber,cFloat,cOctal,cOctalError,cNumbersCom
if exists("c_no_bracket_error")
  syn region	cParen		transparent start='(' end=')' contains=ALLBUT,@cParenGroup
  syn match	cParenError	display ")"
  syn match	cErrInParen	display contained "[{}]"
else
  syn region	cParen		transparent start='(' end=')' contains=ALLBUT,@cParenGroup,cErrInBracket
  syn match	cParenError	display "[\])]"
  syn match	cErrInParen	display contained "[\]{}]"
  syn region	cBracket	transparent start='\[' end=']' contains=ALLBUT,@cParenGroup,cErrInParen
  syn match	cErrInBracket	display contained "[);{}]"
endif

"integer number, or floating point number without a dot and with "f".
syn case ignore
syn match	cNumbers	display transparent "\<\d\|\.\d" contains=cNumber,cFloat,cOctalError,cOctal
" Same, but without octal error (for comments)
syn match	cNumbersCom	display contained transparent "\<\d\|\.\d" contains=cNumber,cFloat,cOctal
syn match	cNumber		display contained "\d\+\(u\=l\{0,2}\|ll\=u\)\>"
"hex number
syn match	cNumber		display contained "0x\x\+\(u\=l\{0,2}\|ll\=u\)\>"
syn case match

if exists("c_comment_strings")
  " A comment can contain cString, cCharacter and cNumber.
  " But a "*/" inside a cString in a cComment DOES end the comment!  So we
  " need to use a special type of cString: cCommentString, which also ends on
  " "*/", and sees a "*" at the start of the line as comment again.
  " Unfortunately this doesn't very well work for // type of comments :-(
  syntax match	cCommentSkip	contained "^\s*\*\($\|\s\+\)"
  syntax region cCommentString	contained start=+L\=\\\@<!"+ skip=+\\\\\|\\"+ end=+"+ end=+\*/+me=s-1 contains=cSpecial,cCommentSkip
  syntax region cComment2String	contained start=+L\=\\\@<!"+ skip=+\\\\\|\\"+ end=+"+ end="$" contains=cSpecial
  syntax region  cCommentL	start="//" skip="\\$" end="$" keepend contains=@cCommentGroup,cComment2String,cCharacter,cNumbersCom,cSpaceError
  syntax region cComment	matchgroup=cCommentStart start="/\*" matchgroup=NONE end="\*/" contains=@cCommentGroup,cCommentStartError,cCommentString,cCharacter,cNumbersCom,cSpaceError
else
  syn region	cCommentL	start="//" skip="\\$" end="$" keepend contains=@cCommentGroup,cSpaceError
  syn region	cComment	matchgroup=cCommentStart start="/\*" matchgroup=NONE end="\*/" contains=@cCommentGroup,cCommentStartError,cSpaceError
endif
" keep a // comment separately, it terminates a preproc. conditional
syntax match	cCommentError	display "\*/"
syntax match	cCommentStartError display "/\*"me=e-1 contained

syn keyword     cType		String Array Int Block

"syn keyword	cStructure	struct union enum typedef

" Highlight User Labels
syn cluster	cMultiGroup	contains=cIncluded,cSpecial,cCommentSkip,cCommentString,cComment2String,@cCommentGroup,cCommentStartError,cUserCont,cUserLabel,cOctalZero,cNumber,cFloat,cOctal,cOctalError,cNumbersCom
syn region	cMulti		transparent start='?' skip='::' end=':' contains=ALLBUT,@cMultiGroup
" Avoid matching foo::bar() in C++ by requiring that the next char is not ':'
syn cluster	cLabelGroup	contains=cUserLabel
syn match	cUserCont	display "^\s*\I\i*\s*:$" contains=@cLabelGroup
syn match	cUserCont	display ";\s*\I\i*\s*:$" contains=@cLabelGroup
syn match	cUserCont	display "^\s*\I\i*\s*:[^:]"me=e-1 contains=@cLabelGroup
syn match	cUserCont	display ";\s*\I\i*\s*:[^:]"me=e-1 contains=@cLabelGroup

syn match	cUserLabel	display "\I\i*" contained

if exists("c_minlines")
  let b:c_minlines = c_minlines
else
  if !exists("c_no_if0")
    let b:c_minlines = 50	" #if 0 constructs can be long
  else
    let b:c_minlines = 15	" mostly for () constructs
  endif
endif
exec "syn sync ccomment cComment minlines=" . b:c_minlines

" Define the default highlighting.
" For version 5.7 and earlier: only when not done already
" For version 5.8 and later: only when an item doesn't have highlighting yet
if version >= 508 || !exists("did_c_syn_inits")
  if version < 508
    let did_c_syn_inits = 1
    command -nargs=+ HiLink hi link <args>
  else
    command -nargs=+ HiLink hi def link <args>
  endif

  HiLink cCommentL		cComment
  HiLink cCommentStart		cComment
  HiLink cLabel			Label
  HiLink cUserLabel		Label
  HiLink cConditional		Conditional
  HiLink cRepeat		Repeat
  HiLink cCharacter		Character
  HiLink cSpecialCharacter	cSpecial
  HiLink cNumber		Number
  HiLink cOctal			Number
  HiLink cOctalZero		PreProc	 " link this to Error if you want
  HiLink cFloat			Float
  HiLink cOctalError		cError
  HiLink cParenError		cError
  HiLink cErrInParen		cError
  HiLink cErrInBracket		cError
  HiLink cCommentError		cError
  HiLink cCommentStartError	cError
  HiLink cSpaceError		cError
  HiLink cSpecialError		cError
  HiLink cOperator		Operator
  HiLink cStructure		Structure
  HiLin cIncluded		cString
  HiLink cError			Error
  HiLink cStatement		Statement
  HiLink cPreCondit		PreCondit
  HiLink cType			Type
  HiLink cConstant		Constant
  HiLink cCommentString		cString
  HiLink cComment2String	cString
  HiLink cCommentSkip		cComment
  HiLink cString		String
  HiLink cComment		Comment
  HiLink cSpecial		SpecialChar
  HiLink cTodo			Todo
  HiLink cClass			Operator
  HiLink cSpecOp		Operator

  delcommand HiLink
endif

let b:current_syntax = "scriptix"

" vim: ts=8
