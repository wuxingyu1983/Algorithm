#!/bin/bash

for i in {1..30}
do
for j in {1..13}
do
   ./tmp $i $j 999999937 >> output.txt 
done
done
