#!/bin/bash


test_path="./valid1"

tests=($(ls $test_path | grep ".s$"))


for file in "${tests[@]}"
do
	./asm $test_path/$file
done
