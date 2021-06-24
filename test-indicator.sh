#!/bin/bash

make accuracy
for i in {1..1000}
do
	printf "iter: $i\n"
	./indicator
done
