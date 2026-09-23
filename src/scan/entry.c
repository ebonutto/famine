#include "famine.h"

#include <sys/stat.h> // DT_DIR, DT_UNKNOWN, DT_REG, struct stat, lstat(), S_ISDIR(), S_ISREG()

#include <limits.h> // PATH_MAX
#include <stdio.h> // snprintf()
#include <string.h> // strcmp()

static int get_entry_type(const char *full_path)
{
	struct stat st;

	if (lstat(full_path, &st) < 0)
		return (DT_UNKNOWN);
	if (S_ISDIR(st.st_mode))
		return (DT_DIR);
	if (S_ISREG(st.st_mode))
		return (DT_REG);
	return (DT_UNKNOWN);
}

void process_entry(const char *path, struct dirent *entry)
{
	int ret;
	char full_path[PATH_MAX];
	int type;

	if (strcmp(entry->d_name, ".") == 0
	    || strcmp(entry->d_name, "..") == 0)
		return ;

	ret = snprintf(full_path, sizeof(full_path), "%s/%s",
	               path, entry->d_name);
	if (ret < 0 || (size_t)ret >= sizeof(full_path))
		return ;

	type = entry->d_type;
	if (type == DT_UNKNOWN)
		type = get_entry_type(full_path);

	// if (type == DT_DIR)
	// 	return (scan_directory(full_path));

	if (type == DT_REG)
		return (process_file(full_path));
}
