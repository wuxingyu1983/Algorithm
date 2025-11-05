#!/bin/bash

cnt=$2;

input_folder="$1/input";
output_folder="$1/output";

for ((num=1;num<=$cnt;num++))
do

input_file="$input_folder/input$num.txt";
output_file="$output_folder/output$num.txt";

result=`./main < $input_file`;
output=`cat $output_file`;

if [ "$result" == "$output" ]; then
  echo "testcase $num correct!";
else
  echo "testcase $num incorrect! result = $result, expect = $output !";
fi

done 
