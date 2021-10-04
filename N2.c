#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

void lfr(char *basepath);
	

int main(int argc, char *argv[])
{
	lfr(argv[1]);
	return 0;
}

void lfr(char *basepath)
{
	struct dirent *d;
	char path[100];
	DIR *dir = opendir(basepath);
	if(!dir)
	{
		return;
	}
	while((d = readdir(dir)) != NULL)
	{
		if(strcmp(d-> d_name, ".") != 0 && strcmp(d-> d_name, "..") != 0)
		{
			printf("%s\n", d-> d_name);
			strcpy(path, basepath);
			strcat(path, "/");
			strcat(path, d-> d_name);
			lfr(path);
		}
	}
	closedir(dir);
}
