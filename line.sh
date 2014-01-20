find . -name "*.c"|xargs cat|grep -v -e ^$ -e ^\s*\/\/.*$|wc -l
