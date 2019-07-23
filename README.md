# y86-64 assembler and emulator, written in C.

## Assembler
Takes the opcodes from opcode.txt and inserts them into a hashtable. Next, parses the source y86 .txt file, turning memnonics and addresses
into machine code. Stores symbols and literals in their respective hashtables. Finally, outputs a binary file comprising the assembled machine code. While compiling, include hash.c. The opcode.txt file should be included in the same directory as the compiled .exe, and the filepath to the y86 source code should be passed as a command line argument.

## Emulator
Parses the binary file created by
