#include <stdio.h>
#include <dirent.h>

int main(void)
{
	DIR *dr;
	struct dirent *de;

	dr = opendir(".");
	if (dr == NULL)
		return (1);

	while ((de = readdir(dr)) != NULL) {
		
	}
		printf("%s\n", de->d_name);

	closedir(dr);
	return (0);
}
