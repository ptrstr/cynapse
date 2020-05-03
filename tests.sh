#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
cd $DIR

retval=0

for i in test/*
do
	echo "Cannot test $i yet. Edit tests.sh"
done

exit $retval
