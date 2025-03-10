#FLAGS = -Wall -Wextra -Werror -std=c99

programa: test.o btree.o Sglist.o Qglist.o stack.o queue.o funcEnteros.o
	$(CC) -o $@ $^ $(FLAGS)

test.o: test.c btree.h
	$(CC) -c $< $(FLAGS)

btree.o: btree.c btree.h
	$(CC) -c $< $(FLAGS)

stack.o: stack.c stack.h tipos.h
	$(CC) -c $< $(FLAGS)

queue.o: queue.c queue.h tipos.h
	$(CC) -c $< $(FLAGS)

Sglist.o: Sglist.c Sglist.h tipos.h
	$(CC) -c $< $(FLAGS)

Qglist.o: Qglist.c Qglist.h
	$(CC) -c $< $(FLAGS)

funcEnteros.o: funcEnteros.c funcEnteros.h
	$(CC) -c $< $(FLAGS)

clean:
	rm *.o
	rm programa

.PHONY = clean