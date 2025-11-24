read -p "Enter the file name :" name
file=$name".c"
# echo $file
gcc src/$file -o output/$name $(mysql_config --cflags --libs)


./output/$name