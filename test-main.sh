#!/bin/bash

make benchmark
for i in {1..1000}
do
	printf "iter: $i\n"
	./main
done
