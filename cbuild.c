#include <sys/wait.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define CC "cc"
#define TARGET "sample"

char *const units[][2] = {
	/*  source      object  */
	{ "sample.c", "sample.o"},
	{ "util.c",   "util.o"  },
};

static void
run(char *file, char *const argv[])
{
	if (!fork())
		execvp(file, argv);
	wait(NULL);
}

static void
compile(void)
{
	for (size_t i = 0; i != sizeof units / sizeof units[0]; i++) {
		char *const compile_arguments[] = {
			CC,
			"-c",
			"-o",
			units[i][1],
			units[i][0],
			NULL
		};

		run(CC, compile_arguments);
	}
}

static void
link_objects(void)
{
	char *link_arguments[100] = {
		CC,
		"-o",
		TARGET,
	};

	for (size_t i = 0; i != sizeof units / sizeof units[0]; i++)
		link_arguments[i+3] = units[i][1];

	run(CC, link_arguments);
}

static void
build(void)
{
	compile();
	link_objects();
}

static void
clean(void)
{
	char *args[] = {
		"rm",
		"-f",
		units[0][1],
		TARGET,
		NULL
	};

	run("rm", args);
	system("rm -f *.o");
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
