#ifndef FAMINE_H
#define FAMINE_H

/* Includes */
#include <dirent.h>   // struct dirent
#include <elf.h>      // ElfN_Ehdr, ElfN_Phdr
#include <errno.h>    // errno
#include <fcntl.h>    // open
#include <stddef.h>   // size_t
#include <stdint.h>   // uintN_t
#include <stdlib.h>   // getenv
#include <string.h>   // strcat
#include <sys/stat.h> // mkdir
#include <sys/wait.h> // waitpid
#include <unistd.h>   // execve
#include <stdbool.h>  // bool

/* Macros */
#define SIGNATURE "FAMINE"
#define SIGNATURE_SIZE (sizeof(SIGNATURE) - 1)

#ifdef VERBOSE
# include <stdio.h> // stderr, fprintf()
# define LOG(...) fprintf(stderr, __VA_ARGS__)
#else
# define LOG(...) ((void)0)
#endif

/* External var */
extern char** environ;

/* Structures */
typedef struct s_file {
    const char* path;
    int fd;
    unsigned char* map;
    size_t size;
} t_file;

typedef struct s_elf64 {
    Elf64_Ehdr* ehdr;
    Elf64_Phdr* phdr;
} t_elf64;

typedef struct s_elf32 {
    Elf32_Ehdr* ehdr;
    Elf32_Phdr* phdr;
} t_elf32;

/* Prototypes */
void scan_directory(const char* path);
void process_entry(const char* path, struct dirent* entry);
void process_file(const char* path);

int open_file(t_file* file, const char* path);
void close_file(t_file* file);
int map_file(t_file* file);
void unmap_file(t_file* file);

bool is_file_infected(t_file* file);
bool is_valid_elf(t_file* file);
int process_elf(t_file* file);
int sign_generic_append(t_file* file);

int process_elf64(t_file* file);
int parse_elf64(t_file* file, t_elf64* elf64);
int infect_elf64(t_file* file, t_elf64* elf64);
int sign_elf64_cavity(t_file* file, t_elf64* elf64);

int process_elf32(t_file* file);
int parse_elf32(t_file* file, t_elf32* elf32);
int infect_elf32(t_file* file, t_elf32* elf32);
int sign_elf32_cavity(t_file* file, t_elf32* elf32);

/* daemon */

int service_is_enabled(const char* unit);
int infect_systemd();
void run(const char* cmd, char* const args[]);

#define FAMINE_SERVICE                                                                             \
    "[Unit]\n"                                                                                     \
    "Description=Famine\n"                                                                         \
    "\n"                                                                                           \
    "[Service]\n"                                                                                  \
    "# Type=simple\n"                                                                              \
    "# ExecStart=%h/famine/famine\n"                                                               \
    "# WorkingDirectory=%h\n"                                                                      \
    "Type=oneshot\n"                                                                               \
    "ExecStart=/usr/bin/printf 'hello world\\n'\n"                                                 \
    "\n"                                                                                           \
    "[Install]\n"                                                                                  \
    "WantedBy=default.target\n"

#endif
