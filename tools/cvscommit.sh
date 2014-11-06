#!/bin/sh
#
# USAGE:
#  When you are ready to commit, run this script from the top source
#  directory, as ./tools/cvscommit.sh.  ./tools/cvsnote.sh will be
#  called (see that file for more information).  Then, your CVS note
#  file will be converted into a ChangeLog entry.  Finally, cvs commit
#  will be called.


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

FMT=$(which fmt)

# -u works?
if echo "hi" | $FMT -u 2>/dev/null ; then
	FMT_U=-u
else
	FMT_U=
fi

MYPATH=$(dirname "$0")

"$MYPATH/cvsnote.sh"

echo "$(date +'%F')  $FULLNAME <$EMAIL>" > .cvs.commit.new
echo '' >> .cvs.commit.new

> .cvs.commit.msg

exec < .cvs.commit.log
while read LINE ; do
  if ! echo "$LINE" | grep -q -E '^#' ; then
    if [ -n "$LINE" ] ; then
      echo "$LINE" >> .cvs.commit.msg
      if [ -n "$FMT" ] ; then
        echo "$LINE" | fmt -s -w 65 $FMT_U | sed 's/^/    /' | sed '1s/^   /  */g' >> .cvs.commit.new
      else
        echo "$LINE" | sed 's/^/  * /' >> .cvs.commit.new
      fi
    fi
  fi
done

echo '' >> .cvs.commit.new
cat ChangeLog >> .cvs.commit.new

# prepare changes
mv -f ChangeLog .ChangeLog~
mv -f .cvs.commit.new ChangeLog
mv -f .cvs.commit.log .cvs.commit.log~

cvs -z3 commit -F .cvs.commit.msg || (
  # failed - revert changes
  mv -f .ChangeLog~ ChangeLog
  mv -f .cvs.commit.log~ .cvs.commit.log
) 

# remove tmp files
rm -f .cvs.commit.msg
