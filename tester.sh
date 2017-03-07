#! /bin/bash
file="FrontEndRequirements/";

#test login first
login=$file"login/login";
input="_Input.txt";
tranout="_TransactionOutput.txt";
termout="_TerminalOutput.txt";
passfail="pass";

for num in {1..10}; do
    ./RapidPrototype/a.out < $login$num$input &> output.txt;
    if [ -z diff output.txt $login$num$termout]; then
        passfail="pass";
    else
        passfail="fail";   
    fi
    echo "test login$num: $passfail" >> test.txt;
done

#for f in $file*; do
#    cp $f $f"_TerminalOutput.txt";
#    cp $f $f"_TransactionOutput.txt";
#    mv $f $f"_Input.txt";
    #mv $f $f".txt";
#done
