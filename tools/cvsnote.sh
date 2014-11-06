#!/bin/sh
#
# USAGE:
#  From the top source directory, run ./tools/cvsnote.sh
#  It will open your editor, with a template of a CVS ChangeLog Note,
#  or open a previously edited Note.  Enter your changes, one per
#  line (do *NOT* wrap lines, or let your editor wrap lines).  When
#  you are ready to commit, run ./tools/cvscommit.sh (which will
#  also call this script one last time before committing).

if [ -f self.cvs.info ] ; then
  . self.cvs.info
fi

if [ -z "$FULLNAME" ] ; then
  FULLNAME=$(getent passwd $USER | cut -d : -f 5 | cut -d , -f 1)

  if [ -z "$FULLNAME" ] ; then
    FULLNAME="$USER"
  fi
fi

DOMAIN=$(hostname -d)
if [ -z "$DOMAIN" ] ; then
  DOMAIN=$(hostname)
  if [ -z "$DOMAIN" ] ; then
    DOMAIN=localhost
  fi
fi

if [ -z "$EMAIL" ] ; then
  EMAIL="$USER@$DOMAIN"
fi

if [ -z "$EDITOR" ] ; then
  for EDITOR in `which editor` `which vim` `which vi` ; do
    break
  done
fi

if [ ! -f .cvs.commit.log ] ; then
  echo "# Commit By: $FULLNAME <$EMAIL>" >> .cvs.commit.log
  echo '# Put one change on each line.  Do not try to wrap' >> .cvs.commit.log
  echo '# Long lines; the script will do that for you.  Be' >> .cvs.commit.log
  echo '# careful your editor does not try to wrap them for' >> .cvs.commit.log
  echo '# you.  Also, any line starting with a # will be' >> .cvs.commit.log
  echo '# ignored by the script.' >> .cvs.commit.log
fi

#has blank line already?
if expr $(tail -n 1 .cvs.commit.log | wc -L) '>' 0 ; then
  echo >> .cvs.commit.log # blank line
fi
LINES=$(wc -l < .cvs.commit.log)
$EDITOR .cvs.commit.log "+$LINES"
