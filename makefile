main: main.o
	gcc -Wall -o main main.o -lm

main.o: main.c 
	gcc -Wall -c  main.c -lm
clean:
	-rm -f main.o
	-rm -f main 
