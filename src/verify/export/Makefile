all:
	g++ -c -fPIC hello.cc -o hello.o
	g++ -shared -o libhello.so hello.o
	gcc -c main.c
	gcc main.o libhello.so
clean:
	rm -rf *.o *.so a.out
