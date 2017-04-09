# Save current working directory
cwd=$(pwd)

# Location of inputs
weekDir="$cwd/week"

#Where to save output
outDir="$cwd/out-week"

#Logs folder
logsDir="$cwd/logs"

#Transactions folder
transactionsDir="$logsDir/transactions"
mkdir -p $transactionsDir

#Accounts
accountsFile="$logsDir/accounts.log"

#Tickets
ticketsFile="$logsDir/tickets.log"

# Location of compiled executable used to run tests
executable="$cwd/sqa.out"

# Check to ensure day was supplied
if [ -z "$1" ]; then
    echo "No argument supplied"
    exit
fi

# Remove old transaction files
echo "Cleaning transaction logs directory"
rm $transactionsDir/* > /dev/null

echo "Running Day $1 inputs..."
# Execute all daily input files
for dayIn in $weekDir/day$1/*; do
    if [ -f $dayIn ]; then
        $executable < $dayIn > /dev/null
    fi
done

# Merge transaction files
cat $transactionsDir/*.log >> $transactionsDir/merged.log

#Run backend
cd backend
make
java Main $accountsFile $ticketsFile $transactionsDir/merged.log


