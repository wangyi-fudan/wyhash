//Modified from Lemire's code
//g++ BenchmarkPRNG.cpp -o BenchmarkPRNG -O2 -fno-tree-vectorize -Wall
#include	<immintrin.h>
#include	<sys/time.h>
#include	<iostream>
#include	<stdint.h>
#include	"wyhash.h"
using namespace std;

static unsigned long long wyseed=123456;

__uint128_t	lehmer64_seed0=123456,	lehmer64_seed1=13456,	lehmer64_seed2=12345;
inline unsigned long long lehmer64(__uint128_t	*lehmer64_seed) {
	*lehmer64_seed*=0xda942042e4dd58b5ull;
	return	*lehmer64_seed>>64;
}

// returns random number, modifies splitmix64_x
// compared with D. Lemire against
// http://grepcode.com/file/repository.grepcode.com/java/root/jdk/openjdk/8-b132/java/util/SplittableRandom.java#SplittableRandom.0gamma
uint64_t splitmix641=123456,splitmix642=12345,	splitmix643=12356;
static inline uint64_t splitmix64(uint64_t	*splitmix64_x) {
  uint64_t z = (*splitmix64_x += UINT64_C(0x9E3779B97F4A7C15));
  z = (z ^ (z >> 30)) * UINT64_C(0xBF58476D1CE4E5B9);
  z = (z ^ (z >> 27)) * UINT64_C(0x94D049BB133111EB);
  return z ^ (z >> 31);
}

uint64_t	rotl(const	uint64_t	x,	int	k){	return (x << k) | (x >> (64 - k));  }
uint64_t	xoshiro256s[4]={78932,872,784,87832};
uint64_t	xoshiro256(void){	
	uint64_t	r=rotl(xoshiro256s[1]*5,7)*9,	t=xoshiro256s[1]<<17;	xoshiro256s[2]^=xoshiro256s[0];	xoshiro256s[3]^=xoshiro256s[1];	xoshiro256s[1]^=xoshiro256s[2];	xoshiro256s[0]^= xoshiro256s[3];	xoshiro256s[2]^=t;	xoshiro256s[3]=rotl(xoshiro256s[3],45);	return r;	
}

typedef __uint128_t pcg128_t;
#define PCG_128BIT_CONSTANT(high, low) ((((pcg128_t)high) << 64) + low)
#define PCG_DEFAULT_MULTIPLIER_128                                             \
  PCG_128BIT_CONSTANT(2549297995355413924ULL, 4865540595714422341ULL)
#define PCG_DEFAULT_INCREMENT_128                                              \
  PCG_128BIT_CONSTANT(6364136223846793005ULL, 1442695040888963407ULL)

struct pcg_state_setseq_128 {
  pcg128_t state;
  pcg128_t inc;
};

typedef struct pcg_state_setseq_128 pcg64_random_t;

static inline void pcg_setseq_128_step_r(struct pcg_state_setseq_128 *rng) {
  rng->state = rng->state * PCG_DEFAULT_MULTIPLIER_128 + rng->inc;
}

// verbatim from O'Neill's except that we skip her assembly:
static inline uint64_t pcg_rotr_64(uint64_t value, unsigned int rot) {
  return (value >> rot) | (value << ((-rot) & 63));
}

static inline uint64_t pcg_output_xsl_rr_128_64(pcg128_t state) {
  return pcg_rotr_64(((uint64_t)(state >> 64u)) ^ (uint64_t)state,
                     state >> 122u);
}

static inline uint64_t
pcg_setseq_128_xsl_rr_64_random_r(struct pcg_state_setseq_128 *rng) {
  pcg_setseq_128_step_r(rng);
  return pcg_output_xsl_rr_128_64(rng->state);
}

static pcg64_random_t pcg64_global; // global state


struct pcg_state_setseq_64 {
  uint64_t
      state;    // RNG state.  All values are possible.  Will change over time.
  uint64_t inc; // Controls which RNG sequence (stream) is
  // selected. Must *always* be odd. Might be changed by the user, never by our
  // code.
};

typedef struct pcg_state_setseq_64 pcg32_random_t;

static pcg32_random_t pcg32_global; // global state

static inline uint32_t pcg32_random_r(pcg32_random_t *rng) {
  uint64_t oldstate = rng->state;
  rng->state = oldstate * UINT64_C(0x5851f42d4c957f2d) + rng->inc;
  uint32_t xorshifted = ((oldstate >> 18) ^ oldstate) >> 27;
  uint32_t rot = oldstate >> 59;
  return (xorshifted >> rot) | (xorshifted << (32 - rot));
}

static inline uint32_t pcg32(void) { return pcg32_random_r(&pcg32_global); }
	
int main(void) {
	timeval beg, end;	unsigned long long	s=0,	n=0x100000000;	//make longer if possible
	cout.precision(3);	cout.setf(ios::fixed);
	cout<<"| PRNG | ns/rand | vs wyrand |\n";
	cout<<"| ---- | ---- | ---- |\n";
	//wyrand
	gettimeofday(&beg, NULL);
    for (size_t	i=0;	i<n;	i++)	s+=wyrand(&wyseed);
    gettimeofday(&end, NULL);
    double	wytime=(end.tv_sec-beg.tv_sec)+1e-6*(end.tv_usec-beg.tv_usec);
	cout<<"| wyrand | "<<wytime*1e9/n<<" | "<<"100.000% |\n";

	//lehmer64
    gettimeofday(&beg, NULL);
    for (size_t	i=0;	i<n;	i++)	s+=lehmer64(&lehmer64_seed0);
    gettimeofday(&end, NULL);
    double	letime=(end.tv_sec-beg.tv_sec)+1e-6*(end.tv_usec-beg.tv_usec);
   	cout<<"| lehmer64 | "<<letime*1e9/n<<" | "<<100*letime/wytime<<"% |\n";

	//3-lehmer64
    gettimeofday(&beg, NULL);
    for (size_t	i=0;	i<n;	i+=3)	s+=lehmer64(&lehmer64_seed0)+lehmer64(&lehmer64_seed1)+lehmer64(&lehmer64_seed2);
    gettimeofday(&end, NULL);
    double	l3time=(end.tv_sec-beg.tv_sec)+1e-6*(end.tv_usec-beg.tv_usec);
   	cout<<"| 3-lehmer64 | "<<l3time*1e9/n<<" | "<<100*l3time/wytime<<"% |\n";

	//splitmix64
    gettimeofday(&beg, NULL);
    for (size_t	i=0;	i<n;	i++)	s+=splitmix64(&splitmix641);
    gettimeofday(&end, NULL);
    double	sptime=(end.tv_sec-beg.tv_sec)+1e-6*(end.tv_usec-beg.tv_usec);
   	cout<<"| splitmix64 | "<<sptime*1e9/n<<" | "<<100*sptime/wytime<<"% |\n";

	//3-splitmix64
    gettimeofday(&beg, NULL);
    for (size_t	i=0;	i<n;	i+=3)	s+=splitmix64(&splitmix641)+splitmix64(&splitmix642)+splitmix64(&splitmix643);
    gettimeofday(&end, NULL);
    double	s3time=(end.tv_sec-beg.tv_sec)+1e-6*(end.tv_usec-beg.tv_usec);
   	cout<<"| 3-splitmix64 | "<<s3time*1e9/n<<" | "<<100*s3time/wytime<<"% |\n";

	//xoshiro256
    gettimeofday(&beg, NULL);
    for (size_t	i=0;	i<n;	i++)	s+=xoshiro256();
    gettimeofday(&end, NULL);
    double	xotime=(end.tv_sec-beg.tv_sec)+1e-6*(end.tv_usec-beg.tv_usec);
   	cout<<"| xoshiro256 | "<<xotime*1e9/n<<" | "<<100*xotime/wytime<<"% |\n";
   	
	//pcg64
    gettimeofday(&beg, NULL);
    for (size_t	i=0;	i<n;	i++)	s+=pcg_setseq_128_xsl_rr_64_random_r(&pcg64_global);
    gettimeofday(&end, NULL);
    double	pctime=(end.tv_sec-beg.tv_sec)+1e-6*(end.tv_usec-beg.tv_usec);
   	cout<<"| pcg64 | "<<pctime*1e9/n<<" | "<<100*pctime/wytime<<"% |\n";
   	   	
	//pcg32
    gettimeofday(&beg, NULL);
    for (size_t	i=0;	i<n;	i++)	s+=pcg32_random_r(&pcg32_global);;
    gettimeofday(&end, NULL);
    double	p3time=(end.tv_sec-beg.tv_sec)+1e-6*(end.tv_usec-beg.tv_usec);
   	cout<<"| pcg32 | "<<p3time*1e9/n<<" | "<<100*p3time/wytime<<"% |\n";

 	return s;
}
