#include "famine.h"

#include <dirent.h> // DIR, struct dirent, closedir(), opendir(), readdir()

void scan_directory(const char *path)
{
	DIR *dir;
	struct dirent *entry;

	dir = opendir(path);
	if (dir == NULL)
		return ;

	while ((entry = readdir(dir)) != NULL) {
		process_entry(path, entry);
	}

	closedir(dir);
}
