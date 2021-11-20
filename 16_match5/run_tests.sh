#!/bin/bash

prog="./match5"
correct="/usr/local/ft510/match5/correct-match5"
testfile="tests.txt"

echo "Trying to run 'make' to build your program..."
make clean
make || exit 1

echo "Running your tests from tests.txt..."
IFS=$'\n'
ans=0
for line in `cat $testfile |sed 's/^$/ /'`
do
    echo "test case: '$line'"
    IFS=" " ours=`${correct} $line 2>ours.err`
    our_es=$?
    IFS=" " theirs=`$prog $line 2>theirs.err`
    their_es=$?
    if [ "$our_es" == "1" ] #error case
    then
	if [ "$their_es" != "1" ]
	then
	    echo " - Failed to exit with a failure status"
	    ans=1
	else
	    diff theirs.err ours.err 2>&1
	    if [ "$?" != 0 ]
	    then
		echo " - Error message was incorrect"
		echo "   ours:  "`cat ours.err`
		echo "   yours: "`cat yours.err`
		ans=1
	    elif [ "$theirs" != "" ]
	    then
		echo " - Nothing should be printed to stdout"
		ans=1
	    fi
	fi
    else #success case
	if [ "$their_es" != "0" ]
	then
	    echo " - Failed to exit with a success status"
	    ans=1
	else
	    if [ "$theirs" != "$ours" ]
	    then
		echo " - Output was incorrect"
		echo "   our output:  $ours"
		echo "   your output: $theirs"
		ans=1
	    elif [ -s "$theirs.err" ]
	    then
		echo " - Nothing should be printed to stderr"
		ans=1
	    fi
	fi
    fi
done

echo ""
if [ "$ans" != "0" ]
then
    echo "It looks like you failed some test cases."
    echo "Please fix them and try again."
else
    echo "You passed all of the test cases in tests.txt!"
fi
