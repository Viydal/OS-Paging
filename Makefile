run:
	gcc -o memsim memsim.c LRUMethod.c clock.c rand.c -Wall
test:
	./memsim traces/sampleTraces/trace1 3 rand debug
quiet:
	./memsim traces/sampleTraces/trace1 3 rand quiet
real:
	./memsim traces/realTraces/bzip.trace 8 rand quiet
clean:
	rm memsim