#!/bin/sh

echo "working"
# echo $1
clingo -n 20 $1 | /usr/bin/python $2