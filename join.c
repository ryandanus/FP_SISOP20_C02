#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"
#include <stddef.h>

typedef struct  file
{
	char array[1000];
}isi;


char buf1[100000], buf2[100000];

char *
	strtok(s, delim) register char *s;
register const char *delim;
{
	register char *spanp;
	register int c, sc;
	char *tok;
	static char *last;

	if (s == NULL && (s = last) == NULL)
		return (NULL);

	/*
	 * Skip (span) leading delimiters (s += strspn(s, delim), sort of).
	 */
cont:
	c = *s++;
	for (spanp = (char *)delim; (sc = *spanp++) != 0;)
	{
		if (c == sc)
			goto cont;
	}

	if (c == 0)
	{ 
		last = NULL;
		return (NULL);
	}
	tok = s - 1;

	/*
	 * Scan token (scan for delimiters: s += strcspn(s, delim), sort of).
	 * Note that delim must have one NUL; we stop if we see that, too.
	 */
	for (;;)
	{
		c = *s++;
		spanp = (char *)delim;
		do
		{
			if ((sc = *spanp++) == c)
			{
				if (c == 0)
					s = NULL;
				else
					s[-1] = 0;
				last = s;
				return (tok);
			}
		} while (sc != 0);
	}
	/* NOTREACHED */
}

int main(int argc, char const *argv[])
{
	isi datafile1[100];
	isi datafile2[100];
	if(argc < 3){
		printf(1,"Error:Join files.....\n");
		exit();
	}
	int file1,file2;
	if ((file1 = open(argv[1], 0)) < 0)
	{ // Error handling : cannot read file 1
		printf(1, "Failed to read files %s\n", argv[1]);
		exit();
	}
	if ((file2 = open(argv[2], 0)) < 0)
	{ // Error handling : cannot read file 2
		printf(1, "failed to read %s\n", argv[2]);
		exit();
	}
	read(file1, buf1, sizeof(buf1));
	read(file2, buf2, sizeof(buf2));

	char *pch = strtok(buf1, " \n");
	int temp = 0;
	while (pch != NULL)
	{
		strcpy(datafile1[temp].array,pch);
		pch = strtok(NULL," \n");
		temp++;
	}
	temp = 0;
	char *data = strtok(buf2," \n");
	while (data != NULL)
	{
		strcpy(datafile2[temp].array,data);
		data = strtok(NULL," \n");
		temp++;
	}
	int  i =0;
	while (i < temp)
	{
		printf(1,"%s %s\n",datafile1[i].array,datafile2[i].array);
		i++;
	}
	
	
	
	close(file1);
	close(file2);
	exit();
}