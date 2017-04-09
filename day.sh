if [ $# == 1 ]; then 

		cwd=$(pwd)
		frontend="$cwd/FrontEnd"
		backend="$cwd/BackEnd"
		logs="$cwd/logs"
		trans="$cwd/logs/transactions"
		inputDir="$cwd/inputFiles/day$1"

		rm $trans/*;

		cd $frontend
		for input in $inputDir/*.txt;
		do
				./sqa.out < $input > /dev/null
		done

		cat $trans/*.log > $trans/mergedDailyTransactions.txt

		cd $backend
		java UpdateUserAccounts $trans/mergedDailyTransactions.txt $logs/accounts.log $logs/tickets.log 

		cd $cwd

else
		echo "Missing argument: please specify a day (1-5) to run"
fi

