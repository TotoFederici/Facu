FLAGS = -Wall -Wextra -Werror -std=c99

programa: Queue_glist.o Qglist.o enterosQglist.o
	$(CC) -o $@ $^ $(FLAGS)

Queue_glist.o: Queue_glist.c Qglist.h enterosQglist.h
	$(CC) -c $< $(FLAGS)

Qglist.o: Qglist.c Qglist.h
	$(CC) -c $< $(FLAGS)

enterosQglist.o: enterosQglist.c enterosQglist.h
	$(CC) -c $< $(FLAGS)

clean:
	rm *.o
	rm programa

.PHONY = clean