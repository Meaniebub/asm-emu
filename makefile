CFLAGS = -I -Wall.

asm: assembler.c hash.c
	gcc -o asm assembler.c hash.c $(CFLAGS)

clean:
	cmd //C del asm.exe
