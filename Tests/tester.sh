#! /bin/bash
file="../FrontEndRequirements/";

#test login first
login=$file"login/login";
input="_Input.txt";
tranout="_TransactionOutput.txt";
termout="_TerminalOutput.txt";
passfail="pass";
testNum=1;

while true; do
    testName=Test_$(date +%d-%m-%Y)_$testNum.txt
    if [ -f $testName ]; then
        ((testNum+= 1));
    else
        break;
    fi
done

for num in {1..5}; do
    ./RapidPrototype/a.out < $login$num$input &> output.txt;
    if diff output.txt $login$num$termout >/dev/null; then
        passfail="pass";
    else
        passfail="fail";
    fi
    echo "login$num terminal = $passfail" >> $testName;
    if diff output.txt $login$num$tranout >/dev/null; then
        passfail="pass";
    else
        passfail="fail";
    fi
    echo "login$num transaction = $passfail" >> $testName;
done

rm output.txt
