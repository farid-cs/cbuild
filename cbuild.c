#include <sys/wait.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LEN(a) (sizeof (a) / sizeof (a)[0])

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
print_command(char *const argv[])
{
	while (*argv) {
		printf("%s ", *argv);
		argv++;
	}
	puts("");
}

static void
compile(void)
{
	for (size_t i = 0; i != LEN(units); i++) {
		char *const compile_args[] = {
			CC,
			"-c",
			"-o",
			units[i][1],
			units[i][0],
			NULL
		};

		print_command(compile_args);
		run(CC, compile_args);
	}
}

static void
link_objects(void)
{
	char *link_args[LEN(units) + 4] = {
		CC,
		"-o",
		TARGET,
	};

	for (size_t i = 0; i != LEN(units); i++)
		link_args[i+3] = units[i][1];

	print_command(link_args);
	run(CC, link_args);
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
	char *clean_args[LEN(units) + 4] = {
		"rm",
		"-f",
		TARGET,
	};

	for (size_t i = 0; i != LEN(units); i++)
		clean_args[i+3] = units[i][1];

	print_command(clean_args);
	run("rm", clean_args);
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
