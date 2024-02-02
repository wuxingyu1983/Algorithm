#!/bin/bash  
#Script to write the output into a file  

#Create output file, override if already present  
output=input.txt 
n=$1

echo $n > $output

length=$n
characters="WWBWBWBWBWBWWBWBWBWBWBB" # 可选的字符集合
#characters=".." # 可选的字符集合

min_value=1       # 最小值（包含）
max_value=107      # 最大值（不包含）

declare -a arr_board
declare -a arr_cost

for ((i = 0; i < $length; i++)); do
string_board=""
string_cost=""
for ((j = 0; j < $length; j++)); do
    random_index=$((RANDOM % ${#characters})) # 获取随机索引值
    char=${characters:$random_index:1} # 根据索引从字符集合中提取对应字符
    string_board+="$char" # 将字符添加到随机字符串变量中

    if [ ${char} == "." ]; then
        string_cost+="0 "
    else
        random=$(($RANDOM % ($max_value - $min_value) + $min_value))
        string_cost+="$random "
    fi
done
arr_board[$i]=$string_board
arr_cost[$i]=$string_cost
done

for ((i = 0; i < $length; i++)); do
    echo ${arr_board[$i]} >> $output
done

for ((i = 0; i < $length; i++)); do
    echo ${arr_cost[$i]} >> $output
done
