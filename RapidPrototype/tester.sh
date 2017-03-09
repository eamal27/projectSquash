#! /bin/bash
file="../FrontEndRequirements/";

#test order login-logout-create
input="_Input.txt";
tranout="_TransactionOutput.txt";
termout="_TerminalOutput.txt";
passfail="pass";
testNum=1;

while true; do
    testName=Tests/Test_$(date +%d-%m-%Y)_$testNum.txt;
    if [ -f $testName ]; then
        ((testNum+= 1));
    else
        break;
    fi
done

tests=(login logout create delete addcredit);
maxNum=(5 4 10 6 9);
testNum=1;
for i in {0..4}; do
    test=$file${tests[$i]}/${tests[$i]};
    for num in $(seq 1 ${maxNum[$i]}); do
        ./a.out Tests/Recent/trans < $test$num$input &> Tests/Recent/${tests[$i]}Output$num.txt;
        if diff Tests/Recent/${tests[$i]}Output$num.txt $test$num$termout >/dev/null; then
            passfail="pass";
        else
            passfail="fail";
        fi
        echo "${tests[i]}$num terminal = $passfail" >> $testName;
        if diff Tests/Recent/trans$testNum.txt $test$num$tranout >/dev/null; then
            passfail="pass";
        else
            passfail="fail";
        fi
        echo "${tests[i]}$num transaction = $passfail" >> $testName;
        ((testNum+=1));
    done
    echo " " >> $testName;
done

cat $testName
