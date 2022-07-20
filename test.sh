#!/bin/bash

# Script responsible executing multiple times the "process" program
nProcesses=$1
kSeconds=$2
rRepetitions=$3

echo "$nProcesses processes"
echo "$kSeconds seconds"
echo "$rRepetitions repetitions"

cd $(dirname $0)

echo "Cleaning result and log files..."
make clean-logs

echo "Executing $nProcesses processes, with $rRepetitions repetitions of $kSeconds s..."
for (( i=1; i<=$nProcesses; i++ ))
do
    ./process $kSeconds $rRepetitions &
done

wait
echo "Execution finished"

echo "Testing result file..."
./test-result $nProcesses $rRepetitions

echo "Testing log file..."
python3 test-log.py

echo "Done!"
