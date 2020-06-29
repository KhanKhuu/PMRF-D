#!/bin/bash


rm times.txt
make

for i in {1..10}
do
	echo 'NUM_PROCESSES == '$i >> times.txt
	for j in {1..5}
	do
		./run ./Input/iob.dat $i 361 323
	done
done

for ((i=100; i<= 1000; i+=100));
do
	echo 'NUM_PROCESSES == '$i >> times.txt
	for j in {1..5}
	do
		./run ./Input/iob.dat $i 361 323
	done
done

