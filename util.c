#include <stdio.h>
#include "util.h"

void
eputs(const char *message)
{
	fputs(message, stderr);
}
