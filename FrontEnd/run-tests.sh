#!/bin/bash

# USAGE:
# ./run_tests.sh -t <test type> -d
#
#      -t - test a subset of tests
#      -d - Show the diff output of failed tests
#
#       No flags will run full test suite
#       without diff

# Save current working directory
cwd=$(pwd)

# Location of tests
testDir="$cwd/tests"

# Location of test related logs
testLogsFolder="$testDir/logs/"

# Location of compiled executable used to run tests
executable="$cwd/sqa.out $testLogsFolder"

# Get command line parameters for testing specific tests
# place options you want in the quotations
while getopts "dt:" opt; do
    case $opt in
	# create a case for any option you want
	d)
	    echo "Diffing enabled"
	    diff='t'
	    ;;
	t)
	    testSet=$OPTARG
	    ;;
	\?)
	    echo "Invalid Option: -$OPTARG" >&2
	    exit 1
	    ;;
    esac
done

# Switch case to get the subset of tests if set
if [ ! -z $testSet ]
then
    case $testSet in
	"login")
	    ;;
	"logout")
	    ;;
	"create")
	    ;;
	"buy")
	    ;;
	"sell")
	    ;;
	"refund")
	    ;;
	"addcredit")
	    ;;
  "delete")
	    ;;
	"general")
	    echo $testSet
	    ;;
	*)
	    echo "--------------------------"
	    echo "Not a test group"
	    echo "Available test groups are:"
	    echo "login"
	    echo "logout"
	    echo "create"
	    echo "buy"
	    echo "sell"
	    echo "refund"
	    echo "addcredit"
	    echo "general"
	    echo "--------------------------"
	    exit 1
	    ;;
    esac
fi


# Move to the test directory to begin testing
cd $testDir

# Given the fully qualified filename of a test to
# be run, the test will be run, results will be
# saved to the same directory, and pass or fail
# indicators will be printed to the repl
#
# param $1 - contains the test to be run
runTest() {
    testIn=$1
    testRoot="${testIn%.*}"
    testLog=$testRoot.log
    testName="${testIn##*/}"
    echo "Testing $testName ..."
    $executable < $testIn > $testRoot.realout
    if ! cmp $testRoot.realout $testRoot.out >/dev/null 2>&1; then
	pass="FAILED"
        printf "%-40s %s\n" $testName "Output: FAILED"
    else
	pass="PASSED"
        printf "%-40s %s\n" $testName "Output: PASSED"
    fi


    outputLogs=${testLogsFolder}transactions/*.log

    cp $outputLogs $testRoot.reallog 2> /dev/null
    rm $outputLogs 2> /dev/null

    if [ -f $testLog ]; then
        if ! cmp $testRoot.reallog $testLog >/dev/null 2>&1; then
            printf "%-40s %s\n" $testName "Log: FAILED"
        else
            printf "%-40s %s\n" $testName "Log: PASSED"
        fi

    fi
    if [ ! -z "$diff" ] && [ $pass == "FAILED" ]
    then
	echo "Output log is ${testRoot}.realout"
	echo "Test log is ${testRoot}.out"
	diff -y $testRoot.realout $testRoot.out
    fi

    echo
}

# Iterates through the tests in a given
# tests folder and finds the input
# (*.in) files. Passes the *.in
# file to runTest to be executed
# against the executable
listTests() {
    for testDir in $1/*; do
        if [ -d $testDir ]; then
            for testIn in $testDir/*.in; do
                runTest $testIn
            done
        fi
    done
}


# Entry Point of script
# Iterates through all test folders, or finds
# a a specific folder to run the tests of
# given the -t parameter.
if [ ! -z $testSet ]
then
    tests=$(find $testDir -name "*$testSet")
    for folder in $tests; do
	if [ -d $folder ]; then
            BASENAME=`basename "$folder"`
            if [ "$BASENAME" == "logs" ]; then
		continue
            fi
            listTests $folder
	fi
    done
else
    for folder in $testDir/*; do
	if [ -d $folder ]; then
            BASENAME=`basename "$folder"`
            if [ "$BASENAME" == "logs" ]; then
		continue
            fi
            listTests $folder
	fi
    done
fi



