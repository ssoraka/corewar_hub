#!/bin/bash

folder="valid"
test_path="/Users/ssoraka/Desktop/days/corewar/material/work/$folder"

tests=($(ls $test_path | grep ".s$"))

rm -rf *.cor

for file in "${tests[@]}"
do
	./asm $test_path/$file
done
