dynamic: dynamic.o libstr.so
	gcc dynamic.c -L. -lstr -o dynamic

libstr.so: str.o
	gcc -shared -Wl,-soname,libstr.so -o libstr.so str.o

str.o: str.c
	gcc -fPIC -c str.c

.PHONY:	clean

clean:
	rm ./dynamic ./str.o ./dynamic.o ./libstr.so
