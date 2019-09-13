#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
EOC='\033[0;0m'

path_origin="./valid1"
tests=($(ls $path_origin | grep ".cor$"))
path_checked="./valid2"

err="errors.txt"
touch $err


for file in "${tests[@]}"
do

			my=$(hexdump $path_origin/$file)
			notmy=$(hexdump $path_checked/$file)

			if [ "$my" == "$notmy" ]
			then
				echo -e "$GREEN идентичны: $file $EOC"
			else
				echo -e "$RED имеют различия: $file $EOC"
				diff  <(echo "$my" ) <(echo "$notmy")
				echo $file >> $err
				##exit 0;
			fi


done
