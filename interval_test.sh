#!/bin/bash
#comments
#try to execute the lte-sim platform
#target := LTE-Sim

#var = [100 200 300 400 500]
clear;
S_Time=1000
echo "Total simulation time is ${S_Time}s and the sleep time is {$1}s"

for ((i = 1; i < 10; i+=2));
do
	#echo "The average file size is $i B"
	echo "The average time interval size is {$i}s"
	./LTE-Sim SingleCellWithFemto 2 1 0 1 1 1 0 0 0 1 1 1 3 0 0.1 128 7000000 $S_Time $i 1 0.5
	echo
done
