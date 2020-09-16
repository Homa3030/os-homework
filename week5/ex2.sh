# !/bin/bash

N=$1

while true; do
    if ! ln 'numbers.txt' numbers.lock
    then
       sleep 1
    else
        #Critical region begins
        for j in `seq 1 $N`
        do
            number=0

            for i in `cat numbers.txt`
            do
                number=$i
            done

            number=$(($number+1))

            echo $number >> numbers.txt

        done
        #Critical region ends

        rm numbers.lock
        break
    fi
done

#The race condition manifests itself very soon. We can observe this by looking at duplicate numbers.