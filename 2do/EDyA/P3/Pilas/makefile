FLAGS = -Wall -Wextra -Werror -std=c99

programa: Stacks_glist.o glist.o enterosGlist.o
	$(CC) -o $@ $^ $(FLAGS)

Stacks_glist.o: Stacks_glist.c glist.h enterosGlist.h
	$(CC) -c $< $(FLAGS)

glist.o: glist.c glist.h
	$(CC) -c $< $(FLAGS)

enterosGlist.o: enterosGlist.c enterosGlist.h
	$(CC) -c $< $(FLAGS)

clean:
	rm *.o
	rm programa

.PHONY = clean