#!/bin/bash
#comments
#try to execute the lte-sim platform
#target := LTE-Sim

#var = [100 200 300 400 500]
clear;
S_Time=$2
echo "Total simulation time is ${S_Time}s and the Sleep time is ${1}s"
for ((i = 3000000; i < 14000000; i+=2000000));
do
	echo "The average file size is ${i}Bytes"
	#echo "The average time interval size is $i s"
	./LTE-Sim SingleCellWithFemto 2 1 0 1 1 1 0 0 0 1 1 1 3 0 0.1 128 $i $S_Time 5 1 $1
	echo
done
