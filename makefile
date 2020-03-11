all:	benchhash
benchhash:	benchhash.cpp wyhash/wyhash.h
	g++ benchhash.cpp t1ha/src/t1ha2.c -o benchhash -Ofast -Wall
clean:
	rm benchhash
