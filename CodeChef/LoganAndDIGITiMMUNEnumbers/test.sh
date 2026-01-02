#!/bin/bash  

#Create input file, override if already present  
input=input.txt;

echo 1 > $input;

random=$(($RANDOM % 8 + 1));
a=`head -c $random /dev/random | od -An -tu8`;

random=$(($RANDOM % 8 + 1));
b=`head -c $random /dev/random | od -An -tu8`;

if [$a -lt $b]; then
    echo $a >> $input;
    echo $b >> $input;
else
    echo $b >> $input;
    echo $a >> $input;
fi

random=$(($RANDOM % 8 + 1));
k=`head -c $random /dev/random | od -An -tu8`;
echo $k >> $input;

result1=`./main < $input`;
result2=`./tmp < $input`;

echo `cat $input`;

if [ "$result1" == "$result2" ]; then
    echo "correct!!";
else
    echo "incorrect!";
fi