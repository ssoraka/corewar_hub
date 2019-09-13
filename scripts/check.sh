#!/bin/bash

file1=$1
file2=$2
errors=$3

number=(1 1000 5000 10000 15000 20000 25000)

for c in ${!number[@]}
do
	num="${number[$c]}"

	my=$(./corewar -dump $num $file1 $file2)
	notmy=$(./corewar1 -d $num $file1 $file2)

	if [ "$my" == "$notmy" ]
	then
		echo "идентичны на итерации $num: $file1 $file2."
	else
		echo "имеют различия на итерации $num: $file1 $file2."
		diff  <(echo "$my" ) <(echo "$notmy")
		echo "$file1 $file2" | > errors
		exit 0;
	fi
done
