# !/bin/bash

gcc ex2.c -o tee.out
cat /proc/cpuinfo | ./tee.out ex2.txt