#!/bin/sh
#
# USAGE:
#  When you are ready to commit, run this script from the top source
#  directory, as ./tools/cvscommit.sh.  ./tools/cvsnote.sh will be
#  called (see that file for more information).  Then, your CVS note
#  file will be converted into a ChangeLog entry.  Finally, cvs commit
#  will be called.

# load settings
if [ -f self.cvs.info ] ; then
  . self.cvs.info
fi

# guess at full name
if [ -z "$FULLNAME" ] ; then
  FULLNAME=$(getent passwd $USER | cut -d : -f 5 | cut -d , -f 1)

  if [ -z "$FULLNAME" ] ; then
    FULLNAME="$USER"
  fi
fi

# guess at email domain
DOMAIN=$(hostname -d)
if [ -z "$DOMAIN" ] ; then
  DOMAIN=$(hostname)
  if [ -z "$DOMAIN" ] ; then
    DOMAIN=localhost
  fi
fi

# guess at email
if [ -z "$EMAIL" ] ; then
  EMAIL="$USER@$DOMAIN"
fi

# find fmt command
FMT=$(which fmt)

# -u works?
if echo "hi" | $FMT -u >/dev/null 2>&1 ; then
  FMT_U=-u
else
  FMT_U=
fi

# our path
MYPATH=$(dirname "$0")

# run cvsnote.sh before commit
"$MYPATH/cvsnote.sh"

# begin log output
echo "$(date -u +'%F %T')  $FULLNAME <$EMAIL>" > .cvs.commit.new
echo '' >> .cvs.commit.new
> .cvs.commit.msg

# read log input, format output
exec < .cvs.commit.log
EMPTY="Y"
while read LINE ; do
  if ! echo "$LINE" | grep -q -E '^#' ; then
    if [ -n "$LINE" ] ; then
      EMPTY="N"
      echo "$LINE" >> .cvs.commit.msg
      if [ -n "$FMT" ] ; then
        echo "$LINE" | fmt -s -w 65 $FMT_U | sed -e '1s/^/  * /;1!s/^/    /' >> .cvs.commit.new
      else
        echo "  * $LINE" >> .cvs.commit.new
      fi
    fi
  fi
done

# changelog finish if we are not empty
if test "$EMPTY" != "Y" ; then
  # finish changelog
  echo '' >> .cvs.commit.new
  cat ChangeLog >> .cvs.commit.new

  # prepare changes
  mv -f ChangeLog .ChangeLog~
  mv -f .cvs.commit.new ChangeLog
  mv -f .cvs.commit.log .cvs.commit.log~
else
  cp -f ChangeLog .ChangeLog~
  cp -f .cvs.commit.log .cvs.commit.log~
  rm -f .cvs.commit.new
fi

cvs -q -z3 commit -F .cvs.commit.msg || (
  # failed - revert changes
  mv -f .ChangeLog~ ChangeLog
  mv -f .cvs.commit.log~ .cvs.commit.log
) 

# remove tmp files
rm -f .cvs.commit.msg
