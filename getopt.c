/* getopt.c */
#include <unistd.h>
#include <stdio.h>
int main(int argc, char * argv[])
{
	int aflag=0, bflag=0, cflag=0;
	int ch;
	while ((ch = getopt(argc, argv, "ab:c")) != -1)
	{
		printf("optind: %d\n", optind);
		switch (ch) {
			case 'a':
				printf("HAVE option: -a\n");
				aflag = 1;
				break;
			case 'b':
				printf("HAVE option: -b\n");
				bflag = 1;
				printf("The argument of -b is %s\n", optarg);
				break;
			case 'c':
				printf("HAVE option: -c");
				cflag = 1;
				break;
			case '?':
				printf("Unknown option: %c\n",(char)optopt);
				break;
		}
	}
}
