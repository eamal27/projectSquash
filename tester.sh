#! /bin/bash
file="$1"

for f in $file*; do
    cp $f $f"_TerminalOutput.txt";
    cp $f $f"_TransactionOutput.txt";
    mv $f $f"_Input.txt";
    #mv $f $f".txt";
done
