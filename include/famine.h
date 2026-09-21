#ifndef FAMINE_H
#define FAMINE_H

/* Structures */
typedef struct s_elf_ctx {
	char *filename;
	off_t filesize;
	void *map;
} t_elf_ctx;

/* Prototypes */
void scan_directory(const char *path);
void process_entry(const char *path, struct dirent *entry);
void process_file(const char *path)

#endif
