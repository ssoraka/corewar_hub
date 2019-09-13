#!/bin/bash

folder="long"
test_path="/Users/ssoraka/Desktop/days/corewar/material/work/42-corewar/tests/vm/$folder"
my_path="/Users/ssoraka/Desktop/days/corewar/material/work"

cd /Users/ssoraka/Desktop/days/corewar/material/work

path="/Users/ssoraka/Desktop/days/corewar/material/work/errors"

file1="2ultima.cor"
file2="4youforkmytralala.cor"

str_count='500'


##./corewar1 -n ./errors/Code_eater.cor ./errors/Code_eater1.cor

##for (( c=6; c<7; c++ ))
##do
	##let last_str=c*100000
	c='1'
	let num=c*5000
	echo $num

	##text1=$(./corewar1 -v 6 text.cor | grep '[IP]' | head -n $last_str | tail -n $str_count)
	##text2=$(./corewar text.cor | grep '[IP]' | head -n $last_str | tail -n $str_count)

	##text1=$(./corewar1 -v 6 Code_Eater.cor Gagnant.cor | grep '[IP]' | head -n $num | tail -n $str_count)
	##text2=$(./corewar Code_Eater.cor Gagnant.cor | grep '[IP]' | head -n $num | tail -n $str_count)
	##text1=$(./corewar1 -v 6 $path/$file1 text.cor $path/$file2 text.cor | grep '[IP]' | tr '\n' ' ' | sed 's/It/*It/g' | sed 's/FAILED/OK/g' | tr '*' '\n' | head -n $num | tail -n $str_count)
	##text2=$(./corewar $path/$file1 text.cor $path/$file2 text.cor | grep '[IP]' | tr '\n' ' ' | sed 's/It/*It/g' | tr '*' '\n' | head -n $num | tail -n $str_count)

	text1=$(./corewar1 -v 6 $path/$file1 $path/$file2 | grep '[IP]' | tr '\n' ' ' | sed 's/It/*It/g' | sed 's/FAILED/OK/g' | tr '*' '\n' | head -n $num | tail -n $str_count)
	text2=$(./corewar $path/$file1 $path/$file2 | grep '[IP]' | tr '\n' ' ' | sed 's/It/*It/g' | tr '*' '\n' | head -n $num | tail -n $str_count)

	echo "$text1" | grep 'lldi'
	##echo "___________"
	##echo "$text2"

	##echo "$text1" > text1.txt
	##echo "$text2" > text2.txt

	##echo "$text2" | grep 'P  141 |'

	if [ "$text1" == "$text2" ]
	then
		echo "$num: идентичны."
	else
		echo "$num: имеют различия."
		diff  <(echo "$text1" ) <(echo "$text2")

		##exit 0;
	fi
##done
