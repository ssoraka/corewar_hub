#!/bin/bash


folder="errors"
path="/Users/ssoraka/Desktop/days/corewar/material/work/$folder"
##path="/Users/ssoraka/Desktop/days/corewar/material/work/42-corewar/tests/vm/$folder"
tests=($(ls $path | grep ".cor$"))

save="/Users/ssoraka/Desktop/days/corewar/material/work/$folder.txt"
save1="/Users/ssoraka/Desktop/days/corewar/material/work/erroresss.txt"

touch $save
touch $save1

number=(1 20 50 80 150 200 600 800 1400 2400 3000 4400 4450 5000 8000 10000 15000 20000)
##number=(10000 11200 12400 13600 14800 15000)

for file1 in "${tests[@]}"
do
	for file2 in "${tests[@]}"
	do
		need_check=$(cat $save | grep "$file1 $file2" | wc -l)
		if [ "$need_check" -eq "0" ]
		then
			echo "_$file1 $file2"


			##for (( c=1; c<=50; c++ ))
			for c in ${!number[@]}
			do
				##let num=7100+c*1
				num="${number[$c]}"

				my=$(./corewar -dump $num $path/$file1 $path/$file2)
				notmy=$(./corewar1 -d $num $path/$file1 $path/$file2)

				if [ "$my" == "$notmy" ]
				then
					echo "$file1 $file2	$num: идентичны."
				else
					echo "$path/$file1 $path/$file2	$num: имеют различия."
					diff  <(echo "$my" ) <(echo "$notmy")
					echo "$file1 $file2" >> $save1
					##exit 0;
				fi
			done
			echo "$file1 $file2" >> $save
		fi
	done
done
