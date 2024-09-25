
all: singlethread multithread

singlethread: singlethread.c
	gcc -Wall -pg singlethread.c -o singlethread

multithread: multithread.c
	gcc -Wall -pg multithread.c -o multithread -lpthread

.PHONY: clean
clean:
	rm singlethread multithread

# Probably will need "sudo" access for this
.PHONY: benchmark
benchmark:
	perf stat -d ./singlethread
	perf stat -d ./multithread
