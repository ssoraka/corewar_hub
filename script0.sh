#!/bin/bash

folder="champ"
test_path="/Users/ssoraka/Desktop/days/corewar/material/work/42-corewar/tests/vm/$folder"
my_path="/Users/ssoraka/Desktop/days/corewar/material/work"

tests=($(ls $test_path | grep ".s$"))
cd $test_path

for file in "${tests[@]}"
do
	$my_path/asm $file
done

cd $my_path
