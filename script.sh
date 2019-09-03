#!/bin/bash

tests=($(ls /Users/ssoraka/Desktop/days/corewar/material/work/op | grep .cor))

save='/Users/ssoraka/Desktop/days/corewar/material/work/file.txt'
touch $save

for file in "${tests[@]}"
do
	need_check=$(cat $save | grep $file | wc -l)
	if [ "$need_check" -eq "0" ]
	then
		echo "_$file_"
		for (( c=1; c<=100; c++ ))
		do
			my=$(./corewar -dump $c op/$file)
			notmy=$(./corewar1 -d $c op/$file)

			if [ "$my" == "$notmy" ]  # Подавление вывода.
			then
				echo "$file	$c: идентичны."
			else
				echo "$file	$c: имеют различия."
				diff  <(echo "$my" ) <(echo "$notmy")
				exit 0;
			fi
		done
		echo "$file" >> $save
	fi
done
