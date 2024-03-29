CFLAGS += -ansi -pedantic -Werror -Wall -Wextra -O1

all: sage

sage: sage.o nil.o pair.o generic.o parse.o symbol.o evaluate.o enviroment.o \
boolean.o value.o closure.o intrinsic.o integer.o character.o operator.o
	$(CC) $(LDFLAGS) -o sage sage.o nil.o pair.o generic.o parse.o \
symbol.o evaluate.o enviroment.o boolean.o value.o closure.o intrinsic.o \
integer.o character.o operator.o

sage.o: sage.c value.h generic.h
	$(CC) $(CFLAGS) -c -o sage.o sage.c

parse.o: parse.c parse.h value.h
	$(CC) $(CFLAGS) -c -o parse.o parse.c

generic.o: generic.c generic.h value.h
	$(CC) $(CFLAGS) -c -o generic.o generic.c

evaluate.o: evaluate.c evaluate.h value.h
	$(CC) $(CFLAGS) -c -o evaluate.o evaluate.c

nil.o: nil.c nil.h value.h
	$(CC) $(CFLAGS) -c -o nil.o nil.c

pair.o: pair.c pair.h value.h
	$(CC) $(CFLAGS) -c -o pair.o pair.c

symbol.o: symbol.c symbol.h value.h
	$(CC) $(CFLAGS) -c -o symbol.o symbol.c

enviroment.o: enviroment.c enviroment.h value.h
	$(CC) $(CFLAGS) -c -o enviroment.o enviroment.c

boolean.o: boolean.c boolean.h value.h
	$(CC) $(CFLAGS) -c -o boolean.o boolean.c

value.o: value.c value.h
	$(CC) $(CFLAGS) -c -o value.o value.c

closure.o: closure.c closure.h value.h
	$(CC) $(CFLAGS) -c -o closure.o closure.c

intrinsic.o: intrinsic.c intrinsic.h value.h
	$(CC) $(CFLAGS) -c -o intrinsic.o intrinsic.c

integer.o: integer.c integer.h value.h
	$(CC) $(CFLAGS) -c -o integer.o integer.c

character.o: character.c character.h value.h
	$(CC) $(CFLAGS) -c -o character.o character.c

operator.o: operator.c operator.h value.h
	$(CC) $(CFLAGS) -c -o operator.o operator.c

clean:
	rm -f sage
	rm -f sage.o
	rm -f nil.o
	rm -f pair.o
	rm -f symbol.o
	rm -f generic.o
	rm -f evaluate.o
	rm -f enviroment.o
	rm -f parse.o
	rm -f boolean.o
	rm -f value.o
	rm -f closure.o
	rm -f intrinsic.o
	rm -f integer.o
	rm -f character.o
	rm -f operator.o

