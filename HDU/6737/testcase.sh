#!/bin/bash  
#Script to write the output into a file  

#Create output file, override if already present  
output=input.txt 
n=$1

echo $n > $output

length=$n
characters=".WBWBWBWBWBWBWBWBWBWB." # 可选的字符集合
#characters=".." # 可选的字符集合

for ((i = 0; i < $length; i++)); do
random_string="" # 存放生成的随机字符串
for ((j = 0; j < $length; j++)); do
    random_index=$((RANDOM % ${#characters})) # 获取随机索引值
    char=${characters:$random_index:1} # 根据索引从字符集合中提取对应字符
    random_string+="$char" # 将字符添加到随机字符串变量中
done
echo $random_string >> $output
done

min_value=0       # 最小值（包含）
max_value=107      # 最大值（不包含）

for ((i = 0; i < $length; i++)); do
random_string="" # 存放生成的随机字符串
for ((j = 0; j < $length; j++)); do
    random=$(($RANDOM % ($max_value - $min_value) + $min_value))
    random_string+="$random "
done
echo $random_string >> $output
done
