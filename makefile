CXX=g++-9
all:	test_vector benchmark0 benchmark1 benchmark2 
test_vector:	test_vector.cpp wyhash.h makefile
	$(CXX) test_vector.cpp -o test_vector -O3 -s  -Wall -march=native
#	./test_vector
benchmark0:	benchmark.cpp wyhash.h makefile
	$(CXX) benchmark.cpp -o benchmark0 -O3 -s  -Wall -march=native -DWYHASH_CONDOM=0
#	./benchmark0
benchmark1:	benchmark.cpp wyhash.h makefile
	$(CXX) benchmark.cpp -o benchmark1 -O3 -s  -Wall -march=native -DWYHASH_CONDOM=1
#	./benchmark1
benchmark2:	benchmark.cpp wyhash.h makefile
	$(CXX) benchmark.cpp -o benchmark2 -O3 -s  -Wall -march=native -DWYHASH_CONDOM=2
#	./benchmark2
clean:
	rm test_vector benchmark0 benchmark1 benchmark2
