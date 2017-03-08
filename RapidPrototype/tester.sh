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

tests=(login logout create);
maxNum=(5 4 10);
for i in {0..2}; do
    test=$file${tests[$i]}/${tests[$i]};
    for num in $(seq 1 ${maxNum[$i]}); do
        ./a.out < $test$num$input &> output.txt;
        if diff output.txt $test$num$termout >/dev/null; then
            passfail="pass";
        else
            passfail="fail";
        fi
        echo "${tests[i]}$num terminal = $passfail" >> $testName;
        if diff output.txt $test$num$tranout >/dev/null; then
            passfail="pass";
        else
            passfail="fail";
        fi
        echo "${tests[i]}$num transaction = $passfail" >> $testName;
    done
    echo " " >> $testName;
done

cat $testName
rm output.txt
