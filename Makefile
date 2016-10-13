OBJ = main.o

all: main.o
	gcc -o ponkotu main.o

main.o: main.c
	gcc -o main.o -c main.c

.PNONY: clean
clean:
	rm *.o

.PNONY: run
run: all
	./ponkotu

