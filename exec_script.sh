clear

gcc -o e1.exe main1.c
gcc -o e2.exe main2.c
gcc -o e3.exe main3.c

./e1.exe && ./e2.exe

FILE="arquivo_final.csv"
touch $FILE
rm -f $FILE

./e3.exe

rm e1.exe && rm e2.exe && rm e3.exe