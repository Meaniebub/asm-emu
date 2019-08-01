asm: assembler.c hash.c
	gcc -o asm assembler.c hash.c -I -Wall -g