#include <sys/wait.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define CC "cc"
#define SOURCE "sample.c"
#define OBJECT "sample.o"
#define TARGET "sample"

static void
run(char *file, char *const argv[])
{
	if (!fork())
		execvp(file, argv);
	wait(NULL);
}

static void
build(void)
{
	char *const compile_arguments[] = {
		CC,
		"-c",
		"-o",
		OBJECT,
		SOURCE,
		NULL
	};
	char *const link_arguments[] = {
		CC,
		"-o",
		TARGET,
		OBJECT,
		NULL
	};

	run(CC, compile_arguments);
	run(CC, link_arguments);
}

static void
clean(void)
{
	char *args[] = {
		"rm",
		"-f",
		OBJECT,
		TARGET,
		NULL
	};

	run("rm", args);
}

static void
usage(void)
{
	fprintf(stderr, "usage: ./build [clean]\n");
	exit(1);
}

int
main(int argc, char *argv[])
{
	if (argc < 2)
		build();
	else if (!strcmp(argv[1], "clean"))
		clean();
	else
		usage();
	return 0;
}
