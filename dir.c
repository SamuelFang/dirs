#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <errno.h>

int isDirectory(const char *path) {
    struct stat statbuf;
    if (stat(path, &statbuf) != 0)
        return 0;
    return S_ISDIR(statbuf.st_mode);
}

int main(int argc, char *argv[]) {
    char dir_name[100];
    if (argc == 1){
        printf("enter a directory to scan\n");
    }
    else{
        strcpy(dir_name,argv[1]);
    }
	DIR *dir = opendir(dir_name);
    if (dir < 0){
        printf("%s\n", strerror(errno));
    }
	struct dirent *de;
	while ((de=readdir(dir)) != NULL){
		printf("name: %s", de->d_name);
    if(isDirectory(de->d_name)){
		printf(" (directory)");
    }
    else{
		printf(" (file)");
    }
        printf("\n");
		struct stat sb;
		stat(de->d_name, &sb);
		printf("size: %d \n", sb.st_size);
        printf("\n");
	}
	closedir(dir);
	return 0;
}