#!/bin/bash


folder="champ"
path="/Users/ssoraka/Desktop/days/corewar/material/work/42-corewar/tests/vm/$folder"
tests=($(ls $path | grep ".cor$"))

save="/Users/ssoraka/Desktop/days/corewar/material/work/$folder.txt"
touch $save

##number=(1 20 50 80 150 200 600 800 1400 2400 5000 8000 10000 15000)
##number=(14000 14200 14400 14600 14800 15000)

for file in "${tests[@]}"
do
	need_check=$(cat $save | grep $file | wc -l)
	if [ "$need_check" -eq "0" ]
	then
		echo "_$file"


		##for c in ${!number[@]}
		for (( c=14600; c<=15000; c++ ))
		do
			let num=c*1
			##num="${number[$c]}"

			my=$(./corewar -dump $num $path/$file)
			notmy=$(./corewar1 -d $num $path/$file)

			if [ "$my" == "$notmy" ]
			then
				echo "$file	$num: идентичны."
			else
				echo "$file	$num: имеют различия."
				diff  <(echo "$my" ) <(echo "$notmy")
				exit 0;
			fi
		done
		echo "$file" >> $save
	fi
done
