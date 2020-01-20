#define	WYHASH32
#define	WYSUM
#include	<sys/mman.h>
#include	<sys/stat.h>
#include	<stdio.h>
#include	<unistd.h>
#include	"wyhash.h"
#include	<fcntl.h>
void	summary(const	char	*F){
	int	fd;	struct	stat	sb;
	fd=open(F,	O_RDONLY);
	if(fd<0)	return;
	fstat(fd,	&sb);
	uint8_t	*p=(uint8_t*)mmap(NULL,	sb.st_size,	PROT_READ,	MAP_SHARED,	fd,	0);
	if(p==MAP_FAILED)	return;
	char	s[15];
	printf("%s\t%s\n",	wysum(p,sb.st_size,s),	F);
	munmap(p,	sb.st_size);	close(fd);
}
int	main(int	ac,	char	**av){
	for(int	i=1;	i<ac;	i++)	summary(av[i]);
	return	0;
}
