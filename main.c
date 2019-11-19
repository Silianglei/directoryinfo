#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

int main (int argc, char *argv[]) {
  //recieve input
	char directory[1000];
	if (argc == 1) {
		fgets(directory, sizeof(directory), stdin);
		directory[strlen(directory) - 1] = '\0';
	}
	else {
		strcpy(directory, argv[1]);
	}

	DIR *direct = opendir(directory);
	long size = 0;
  if (errno > 0){
    printf("%s\n", strerror(errno));
    return 0;
  } //if directory doesnt exist

	struct dirent *file;
	printf("\nINFORMATION REGARDING [%s]\n", directory);
	while ((file = readdir(direct)) != NULL) {
		if (file->d_type == 4) {
			printf("DIR");
		}
		else {
			printf("---");
		}
		struct stat f;
		stat(file->d_name, &f);
		size += f.st_size;
		printf(" %s (%lldB)\n", file->d_name, f.st_size); //print out info
	}
	printf("DIRECTORY SIZE: %ld bytes\n\n", size);
}
