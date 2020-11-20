CXX=g++
all:	test_vector wyhash0 wyhash1 wyhash2 xxh3scalar xxh3sse2 xxh3avx2
test_vector:	test_vector.cpp wyhash.h makefile
	$(CXX) test_vector.cpp -o test_vector -O3 -s  -Wall -march=native
wyhash0:	benchmark.cpp wyhash.h makefile
	$(CXX) benchmark.cpp -o wyhash0 -O3 -s  -Wall -march=native -DWYHASH_CONDOM=0
wyhash1:	benchmark.cpp wyhash.h makefile
	$(CXX) benchmark.cpp -o wyhash1 -O3 -s  -Wall -march=native -DWYHASH_CONDOM=1
wyhash2:	benchmark.cpp wyhash.h makefile
	$(CXX) benchmark.cpp -o wyhash2 -O3 -s  -Wall -march=native -DWYHASH_CONDOM=2
xxh3scalar:	benchmark.cpp makefile
	$(CXX) benchmark.cpp -o xxh3scalar -O3 -s  -Wall -march=native -DXXH_VECTOR=0 -DXXH3
xxh3sse2:	benchmark.cpp makefile
	$(CXX) benchmark.cpp -o xxh3sse2 -O3 -s  -Wall -march=native -DXXH_VECTOR=1 -DXXH3
xxh3avx2:	benchmark.cpp makefile
	$(CXX) benchmark.cpp -o xxh3avx2 -O3 -s  -Wall -march=native -DXXH_VECTOR=2 -DXXH3
clean:
	rm test_vector wyhash0 wyhash1 wyhash2 xxh3scalar xxh3sse2 xxh3avx2

