run:
	gcc -o memsim memsim.c LRUMethod.c clock.c rand.c -Wall
sample1:
	./memsim traces/sampleTraces/trace1 3 rand debug
sample2:
	./memsim traces/sampleTraces/trace1 3 rand quiet
bzip:
	./memsim traces/realTraces/bzip.trace 8 lru quiet
gcc:
	./memsim traces/realTraces/gcc.trace 4 lru quiet
sixpack:
	./memsim traces/realTraces/sixpack.trace 4 lru quiet
swim:
	./memsim traces/realTraces/swim.trace 4 lru quiet
clean:
	rm memsim