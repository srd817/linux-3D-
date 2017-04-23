edit: keys.o directions.o menu.o new.o seieme.o judge.o begin.o main.o  
	gcc -Wall -Wextra -ansi -o edit keys.o directions.o menu.o new.o seieme.o judge.o begin.o main.o -lm
keys.o: keys.c keys.h
	gcc -Wall -Wextra -ansi -c keys.c -lm 
directions: directions.c directions.h keys.h 
	gcc -Wall -Wextra -ansi -c directions.c -lm 
menu.o: menu.c menu.h keys.h directions.h
	gcc -Wall -Wextra -ansi -c menu.c -lm
new.o:  new.c new.h keys.h directions.h menu.h 
	gcc -Wall -Wextra -ansi -c new.c -lm
seieme.o:  seieme.c seieme.h keys.h directions.h menu.h new.h
	gcc -Wall -Wextra -ansi -c seieme.c -lm
judge.o: judge.c judge.h keys.h directions.h menu.h new.h seieme.h
	gcc -Wall -Wextra -ansi -c judge.c -lm
begin.o: begin.c begin.h keys.h directions.h menu.h new.h seieme.h judge.h
	gcc -Wall -Wextra -ansi -c begin.c -lm
main.o: main.c menu.h keys.h directions.h new.h seieme.h begin.h judge.h
	gcc -Wall -Wextra -ansi -c main.c -lm
.PHONY:clean
clean:
	-rm edit main.o menu.o keys.o directions.o new.o seieme.o judge.o
