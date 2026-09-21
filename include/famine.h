#ifndef FAMINE_H
#define FAMINE_H

/* Includes */
#include <dirent.h> // struct dirent
#include <stddef.h> // size_t

/* Structures */
typedef struct s_file {
	const char *path;
	int fd;
	void *map;
	size_t size;
} t_file;

/* Prototypes */
void scan_directory(const char *path);
void process_entry(const char *path, struct dirent *entry);

void process_file(const char *path);

int file_load(t_file *file, const char *path);
void file_unload(t_file *file);

#endif
