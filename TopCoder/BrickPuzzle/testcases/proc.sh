#!/bin/bash

input_folder="input";
output_folder="output";

for num in {1..179}
do

input_file="$input_folder/input$num.txt";
output_file="$output_folder/output$num.txt";

sed -n "${num}p" input.raw > $input_file;
sed -n "${num}p" output.raw > $output_file;

done 
