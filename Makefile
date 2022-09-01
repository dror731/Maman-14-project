assembler:main.o macro.o first_check.o symbol.o word.o print_files.o
	gcc -Wall -ansi -pedantic print_files.o word.o symbol.o first_check.o macro.o main.o -o assembler
main.o: main.c main.h
	gcc -c -Wall -ansi -pedantic main.c -o main.o
macro.o: macro.c macro.h
	gcc -c -Wall -ansi -pedantic macro.c -o macro.o
first_check.o: first_check.c first_check.h
	gcc -c -Wall -ansi -pedantic first_check.c -o first_check.o
symbol.o: symbol.c symbol.h
	gcc -c -Wall -ansi -pedantic symbol.c -o symbol.o
word.o: word.c word.h
	gcc -c -Wall -ansi -pedantic word.c -o word.o
print_files.o: print_files.c print_files.h
	gcc -c -Wall -ansi -pedantic print_files.c -o print_files.o
