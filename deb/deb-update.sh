#!/bin/sh

if [ -f 'configure.in' ] ; then
	VERSION=`grep -E "^VERSION=" configure.in | sed 's/^VERSION=\([0-9.]*\).*$/\1/'`
else
	echo "No ./configure.in found"
	exit 1
fi

if [ -n "$1" ] ; then
	NOTES="$1"
else
	NOTES="New release/snapshot."
fi

if [ -f debian/changelog ] ; then
	CHANGELOG=debian/changelog
elif [ -f changelog ] ; then
	CHANGELOG=changelog
else
	echo "Could not find changelog"
	exit 1
fi

REV=1

while grep -q "($VERSION-$REV)" $CHANGELOG ; do
	REV=`expr $REV + 1`
done

if [ -z "$FULLNAME" ] ; then
	FULLNAME=`getent passwd $USER | cut -d : -f 5 | cut -d , -f 1`

	if [ -z "$FULLNAME" ] ; then
		FULLNAME="$USER"
	fi
fi

if [ -z "$EMAIL" ] ; then
	EMAIL="$USER@`hostname -d`"
fi

echo "scriptix ($VERSION-$REV) unstable; urgency=low" > .new-cl
echo >> .new-cl
echo "  * $NOTES" >> .new-cl
echo >> .new-cl 
echo " -- $FULLNAME <$EMAIL> " `date "+%a, %e %b %Y %T %z"` >> .new-cl
echo >> .new-cl

cat $CHANGELOG >> .new-cl
mv $CHANGELOG $CHANGELOG.bak
mv .new-cl $CHANGELOG
