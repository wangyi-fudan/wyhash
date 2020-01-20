#define WYHASH32
#define	WYHANZI
#include	<sys/mman.h>
#include	<sys/stat.h>
#include	<stdio.h>
#include	<unistd.h>
#include	"wyhash.h"
#include	<fcntl.h>
void	wysum(const	char	*F){
	int	fd;	struct	stat	sb;
	fd=open(F,	O_RDONLY);
	if(fd<0)	return;
	fstat(fd,	&sb);
	uint8_t	*p=(uint8_t*)mmap(NULL,	sb.st_size,	PROT_READ,	MAP_SHARED,	fd,	0);
	if(p==MAP_FAILED)	return;
	char	s[13];
	wy2hanzi(s,	wyhash(p,sb.st_size,0));
	munmap(p,	sb.st_size);	close(fd);
	printf("%s\t%s\n",	s,	F);
}
int	main(int	ac,	char	**av){
	for(int	i=1;	i<ac;	i++)	wysum(av[i]);
	return	0;
}
