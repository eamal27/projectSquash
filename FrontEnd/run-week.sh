#!/bin/bash

#Run the day test 5 times with each "day of the week test"
for i in {1..5}; do
    ./run-day.sh $i
done
