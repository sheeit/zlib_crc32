#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <zlib.h>

static void help(const char *progname) __attribute__((noreturn));
unsigned long calculate_crc32(const char *filename);

static unsigned long initial_value;

int main(int argc, char *argv[])
{

	if (argc == 1 || !strcmp("--help", argv[1])
			|| !strcmp("-h", argv[1])) {
		help(argv[0]);
	}

	initial_value = crc32(0, NULL, 0);

	for (++argv; *argv; ++argv)
		printf("%s %08lX\n", *argv, calculate_crc32(*argv));

	exit(EXIT_SUCCESS);
}

unsigned long calculate_crc32(const char *filename)
{
	FILE *f;
	size_t r;
	static unsigned char buf[BUFSIZ];
	unsigned long c;

	f = fopen(filename, "rb");
	if (!f) {
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	c = initial_value;
	while ((r = fread(buf, 1, sizeof buf, f)) > 0u) {
		c = crc32(c, buf, r);
	}

	if (ferror(f)) {
		fprintf(stderr, "ferror: error reading file %s\n", filename);
		if (fclose(f) == EOF)
			perror("fclose");
		exit(EXIT_FAILURE);
	}

	if (fclose(f) == EOF) {
		perror("fclose");
		exit(EXIT_FAILURE);
	}

	return c;
}

static void help(const char *progname)
{
	printf("Usage: %s FILES...\n"
		"Calculate the CRC32 checksum of the files and prints it out "
		"for each file.\n",
		progname);
	exit(EXIT_SUCCESS);
}
