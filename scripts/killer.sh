#!/bin/bash


folder="valid"
path="./$folder"
script='check.sh'
##path="/Users/ssoraka/Desktop/days/corewar/material/work/42-corewar/tests/vm/$folder"
tests=($(ls $path | grep ".cor$"))

save="./$folder.txt"
error="./errors.txt"

touch $save
touch $error


for file1 in "${tests[@]}"
do
	for file2 in "${tests[@]}"
	do
		need_check=$(cat $save | grep "$file1 $file2" | wc -l)
		if [ "$need_check" -eq "0" ]
		then
			echo "_$file1 $file2"

			./$script $path/$file1 $path/$file2 $error&

			for (( c=1; c<=200; c++ ))
			do
				in_work=$(ps | grep $script | wc -l)
				if [ "$in_work" -gt "1" ]
				then
					echo "сон"
					sleep 1
				fi
			done

			in_work=$(ps | grep $script | wc -l)
			if [ "$in_work" -gt "1" ]
			then
				echo "килл"
				process=$(ps | grep $script | tail -n 1 | cut -d' ' -f1)
				kill -9 $process
			fi

			echo "$file1 $file2" >> $save
		fi
	done
done
