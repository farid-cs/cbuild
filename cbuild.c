#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
build()
{
	system("cc -c sample.c");
	system("cc -o sample sample.o");
}

void
clean()
{
	system("rm *.o sample");
}

void
usage()
{
	fprintf(stderr, "usage: ./build [clean]\n");
}

int
main(int argc, char *argv[])
{
	if (argc < 2) {
		build();
		return 0;
	}
	if (!strcmp(argv[1], "clean")) {
		clean();
		return 0;
	}
	usage();
	return 1;
}
