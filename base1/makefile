main: bin/main.o bin/queue.o bin/tb1.o
	gcc -o $@ $^

bin/main.o: main.c | tb1.h bin
	gcc -c -o $@ $^
bin/tb1.o: tb1.c | Queue.h tb1.h bin
	gcc -c -o $@ $^
bin/queue.o: Queue.c | Queue.h bin
	gcc -c -o $@ $^

bin:
	mkdir $@ 

clean:
	rm -rf bin main