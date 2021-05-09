all: compile
	./main

compile:
	gcc -g main.c -o main

valgrind: compile
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./main

clean:
	rm -f main
	ls -l