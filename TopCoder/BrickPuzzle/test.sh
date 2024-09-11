#!/bin/bash

cnt=$2;

input_folder="$1/input";
output_folder="$1/output";

for num in {1..179}
do

input_file="$input_folder/input$num.txt";
output_file="$output_folder/output$num.txt";

result=`./main < $input_file`;
output=`head -n 1 $output_file`;

if [ $result = $output ]; then
  echo "testcase $num correct!";
else
  echo "testcase $num incorrect! result = $result, expect = $output !";
fi

done 
