static: static.o libstr.a
	gcc -o static static.o -L. -lstr

static.o: static.c
	gcc -c static.c -o static.o

libstr.a: str.o
	ar -rc libstr.a -o str.o

str.o: str.c
	gcc -c str.c -o str.o

.PHONY:	clean

clean:
	rm ./static ./str.o ./static.o ./libstr.a
