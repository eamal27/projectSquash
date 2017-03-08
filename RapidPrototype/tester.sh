#! /bin/bash
file="../FrontEndRequirements/";

#test order login-logout
login=$file"login/login";
logout=$file"logout/logout";
create=$file"create/create";
input="_Input.txt";
tranout="_TransactionOutput.txt";
termout="_TerminalOutput.txt";
passfail="pass";
testNum=1;

while true; do
    testName=Tests/Test_$(date +%d-%m-%Y)_$testNum.txt
    if [ -f $testName ]; then
        ((testNum+= 1));
    else
        break;
    fi
done
#login test
for num in {1..5}; do
    ./a.out < $login$num$input &> output.txt;
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
#logout test
    echo " " >> $testName;
for num in {1..4}; do
    ./a.out < $logout$num$input &> output.txt;
    if diff output.txt $logout$num$termout >/dev/null; then
        passfail="pass";
    else
        passfail="fail";
    fi
    echo "logout$num terminal = $passfail" >> $testName;
    if diff output.txt $logout$num$tranout >/dev/null; then
        passfail="pass";
    else
        passfail="fail";
    fi
    echo "logout$num transaction = $passfail" >> $testName;
done
#create test
    echo " " >> $testName;
for num in {1..11}; do
    ./a.out < $create$num$input &> output.txt;
    if diff output.txt $create$num$termout >/dev/null; then
        passfail="pass";
    else
        passfail="fail";
    fi
    echo "create$num terminal = $passfail" >> $testName;
    if diff output.txt $create$num$tranout >/dev/null; then
        passfail="pass";
    else
        passfail="fail";
    fi
    echo "create$num transaction = $passfail" >> $testName;
done

cat $testName
rm output.txt
