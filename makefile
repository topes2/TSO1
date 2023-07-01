main: bin/main.o bin/Queue.o bin/funcs.o
	gcc -o $@ $^ 

bin/main.o: main.c | Queue.h funcs.h bin
	gcc -c -o $@ $^
bin/Queue.o: Queue.c | Queue.h bin
	gcc -c -o $@ $^ 
bin/funcs.o: funcs.c | funcs.h bin
	gcc -c -o $@ $^

bin:
	mkdir bin
clean: 
	rm -rf bin main