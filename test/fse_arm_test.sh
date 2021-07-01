#!/bin/bash

echo -e "Argumentos de entrada:
qemu-system-arm                             \ 
-icount shift=auto,align=on -M netduino2    \  
-nographic -monitor null -serial stdio      \ 
-kernel bin/armsemaforo.bin -d int          \ 
< <(while read -r line; do word=(\$line);    \\
sleep \${word[0]}; echo \${word[1]}; done)"

sleep 2

echo ""
qemu-system-arm --version

sleep 2
echo ""
echo "Entrada de teste:
2 R
3 Y
2 S
3 G
2 S
2 S
3 G
3 R
5 Y
5 Y
3 S
3 R
2 S
2 Y
3 G
8 R
7 S
"
echo "Iniciando teste..."
sleep 2

cat test/arm.input | qemu-system-arm     \
-icount shift=auto,align=on -M netduino2 \
-nographic -monitor null -serial stdio   \
-kernel bin/armsemaforo.bin -d int       \
< <(while read -r line; do word=($line); \
sleep ${word[0]}; echo ${word[1]}; done)
