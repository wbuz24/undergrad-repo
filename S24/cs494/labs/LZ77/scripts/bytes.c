
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

char* construct_filename(char *input, char *n) {
	int i, size, fnsize, ns;
	char *ofname, *fn;
	
	/* Find the last / and return a pointer to it */
	fn = input;

	for (i = strlen(input) - 2; i >= 0; i--) {
		if (input[i] == '/') {
			fn = input + i + 1;
			i = 0;
		}
	}

	fnsize = strlen(fn);
	ns = strlen(n);
	size = fnsize + ns + 10;
	ofname = (char *) malloc(sizeof(char) * size);
	if (ofname == NULL) { perror("malloc output file\n"); exit(1); }

	strcpy(ofname, "data/");
	strncpy(ofname + 5, fn, fnsize - 4);
	strcat(ofname + fnsize + 1, "_");
	strcat(ofname + fnsize + 2, n);
	strcat(ofname + fnsize + ns + 2, ".txt");

	return ofname;
}

int main(int argc, char **argv) {
	struct stat buf;
	long n, curr_size;
	char *filename, *ofn, *strbuf;
	FILE *f, *out;
	int exists, ex;
	
	if (argc != 3) { printf("usage: ./bin/bytes kB input.txt\n"); exit(1); }

	sscanf(argv[1], "%ld", &n);
	n = n * 1000;
	filename = strdup(argv[2]); 
	ofn = construct_filename(filename, argv[1]);

	/* Error check the input file */
	exists = stat(filename, &buf);
	if (exists < 0) { printf("%s does not exist\n", filename); exit(1); }

	/* Open the input for reading and the output for writing */
	f = fopen(filename, "r");
	if (f == NULL) { perror(filename); exit(1); }
	out = fopen(ofn, "w");
	if (out == NULL) { perror(ofn); exit(1); }

	/* Call stat on the output file */
	ex = stat(ofn, &buf);
	if (ex < 0) { printf("%s does not exist\n", ofn); exit(1); }

	strbuf = (char *) malloc(sizeof(char) * 1010);

	/* track the size of the output file and read in kB increments */
	curr_size = buf.st_size;
	while (curr_size < n) {
		fread(strbuf, 1, 1000, f);
		fwrite(strbuf, 1, 1000, out);
		
		/* Need to write code to reset the file pointer */
		ex = stat(ofn, &buf);
		if (ex < 0) { printf("%s does not exist\n", ofn); exit(1); }

		curr_size = buf.st_size;
	}

	printf("%s: %ld %ld\n", ofn, buf.st_size, n);

	free(filename);
	free(strbuf);
	fclose(f);
	fclose(out);

} 
