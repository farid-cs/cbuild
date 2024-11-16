#include <stdlib.h>

int
main(void)
{
	system("cc -c sample.c");
	system("cc -o sample sample.o");
	return 0;
}
