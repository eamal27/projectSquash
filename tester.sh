#! /bin/bash
file="../FrontEndRequirements/";

#test login first
login=$file"login/login";
input="_Input.txt";
tranout="_TransactionOutput.txt";
termout="_TerminalOutput.txt";
passfail="pass";
date=$(date +%d-%m-%Y);

for num in {1..5}; do
    ./RapidPrototype/a.out < $login$num$input &> output.txt;
    if diff output.txt $login$num$termout >/dev/null; then
        passfail="pass";
    else
        passfail="fail";
    fi
    echo "login$num terminal = $passfail" >> "Test_$date.txt";
    if diff output.txt $login$num$tranout >/dev/null; then
        passfail="pass";
    else
        passfail="fail";
    fi
    echo "login$num transaction = $passfail" >> "Test_$date.txt";
done

rm output.txt;
