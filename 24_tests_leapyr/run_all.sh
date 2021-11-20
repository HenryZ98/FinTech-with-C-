#!/bin/bash

run_tests() {
    testfile="$1"
    IFS=$'\n'
    for line in `awk 'BEGIN {FS=";"}; {print $1}' $testfile`
    do
	year=`echo $line | cut -d',' -f1 2>&1`
	expected=`echo $line | cut -d' ' -f2 2>&1`
	output=`/usr/local/ft510/leap_yr/leap $year $expected 2>&1`
	res=`echo $output | cut -d' ' -f2`
	if [ "$res" != "passed" ]
	then
	    echo "Test case '$line' does not match the program's expected answer" >&2
	    passed=0
	    return
	else
	    echo $output
	fi
    done
}

passed=1
cat tests.txt | tr [:upper:] [:lower:] > temp.txt
run_tests temp.txt >> test_results.txt
cat test_results.txt | sort | uniq > answers.txt
condct=`cat answers.txt | wc -l` 
echo "Conditions tested:"
cat answers.txt
echo "There were ${condct} conditions tested, of 4 possible."
if [ $condct -ne 4 ]
then
    passed=0
fi
if [ "$passed" == "1" ]
then
    echo "PASSED"
else
    echo "FAILED"
fi
rm temp.txt test_results.txt answers.txt
