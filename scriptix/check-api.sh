#!/bin/sh

message() {
	if [ "$QUIET" = "no" ] ; then
		echo
		echo "$1"
	fi
}

ERROR=no
UPDATE=no
CHECK=yes
SORT=no
QUIET=no

while [ -n "$1" ] ; do
	case "$1" in
		update)
			UPDATE=yes
			;;
		nocheck)
			CHECK=no
			;;
		sort)
			SORT=yes
			;;
		quiet)
			QUIET=yes
			;;
	esac
	shift
done

message "Checking Scriptix API"

if [ "$SORT" = "yes" ] ; then
	message " Sorting API list"
	sort -f api.lst | uniq > api.tmp
	mv -f api.tmp api.lst
fi

message " Finding signatures"
echo "" > .api.out
for api in `cat api.lst` ; do
	LINE=`grep -E "^[^)]*$api(\(| )" include/scriptix.h`
	if [ -z "$LINE" ] ; then
		echo
		echo "** ERROR - Interface missing : $api **"
		ERROR=yes
	else
		echo "$LINE" | sed "s/ __INLINE__ / /g" >> .api.out
	fi
done

if [ "$ERROR" = "no" ] ; then
	if [ "$UPDATE" = "yes" ] ; then
		message " Updating signatures"
		cp -f .api.out api.chk
	fi

	if [ "$CHECK" = "yes" ] ; then
		message " Comparing signatures"

		if ! diff -d api.chk .api.out > .api.dif ; then
			cat .api.dif | grep -E "^>" > .api.err
			echo
			echo "** WARNING - Changed API **"
			echo
			cat .api.err
		fi
	fi

	message "** OK **"
	exit 0
else
	exit 1
fi
