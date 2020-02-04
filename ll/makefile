linkedlist_test: linkedlist_test.o
	gcc -g -Wall -I. -o linkedlist_test linkedlist_test.o linkedlist.c -lpthread

linkedlist_test.o: linkedlist_test.c 
	gcc -g -Wall -c  linkedlist_test.c -lpthread
clean:
	-rm -f linkedlist_test.o
	-rm -f linkedlist_test 
