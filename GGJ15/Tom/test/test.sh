#!/bin/sh

echo "working"
# echo $1
/opt/local/bin/clingo -n 1 $1 | /usr/bin/python $2