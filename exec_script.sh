clear

echo "========================================"

gcc -o e1.exe main1.c
gcc -o e2.exe main2.c

./e1.exe && echo "========================================"
./e2.exe && echo "========================================"

FILE="arquivo_final.csv"
touch $FILE
rm -f $FILE

gcc -o e3.exe main3.c

./e3.exe

rm e1.exe && rm e2.exe && rm e3.exe