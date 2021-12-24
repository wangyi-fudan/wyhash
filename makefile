# wyhash bench makefile

CXX = g++
CXXFLAGS = -std=c++11 -O2 -s -Wall -march=native

TARGETS = test_vector wyhash0 wyhash1 wyhash2 xxh3scalar xxh3sse2 xxh3avx2

all:	$(TARGETS)

test_vector:	test_vector.cpp wyhash.h
	$(CXX) test_vector.cpp -o test_vector $(CXXFLAGS)

wyhash0:	benchmark.cpp wyhash.h
	$(CXX) benchmark.cpp -o wyhash0 $(CXXFLAGS) -DWYHASH_CONDOM=0

wyhash1:	benchmark.cpp wyhash.h
	$(CXX) benchmark.cpp -o wyhash1 $(CXXFLAGS) -DWYHASH_CONDOM=1

wyhash2:	benchmark.cpp wyhash.h
	$(CXX) benchmark.cpp -o wyhash2 $(CXXFLAGS) -DWYHASH_CONDOM=2

xxh3scalar:	benchmark.cpp
	$(CXX) benchmark.cpp -o xxh3scalar $(CXXFLAGS) -DXXH_VECTOR=0 -DXXH3

xxh3sse2:	benchmark.cpp
	$(CXX) benchmark.cpp -o xxh3sse2 $(CXXFLAGS) -DXXH_VECTOR=1 -DXXH3

xxh3avx2:	benchmark.cpp
	$(CXX) benchmark.cpp -o xxh3avx2 $(CXXFLAGS) -DXXH_VECTOR=2 -DXXH3

clean:
	rm $(TARGETS)

