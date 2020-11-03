# !/bin/bash

input="/dev/random"
counter=0
while IFS= read -n1 char; do
    printf %c $char >> ex1.txt
    counter=$(($counter + 1))
    if [ $counter -ge 20 ] 
    then
        break
    fi
done < "$input"