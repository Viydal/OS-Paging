run:
	gcc -o memsim memsim.c LRUMethod.c clock.c rand.c -Wall
sample1:
	./memsim traces/sampleTraces/trace1 3 rand debug
sample2:
	./memsim traces/sampleTraces/trace1 3 rand quiet
bzip:
	./memsim traces/realTraces/bzip.trace 8 rand debug
gcc:
	./memsim traces/realTraces/gcc.trace 8 rand debug
sixpack:
	./memsim traces/realTraces/sixpack.trace 8 rand debug
swim:
	./memsim traces/realTraces/swim.trace 8 rand debug
clean:
	rm memsim