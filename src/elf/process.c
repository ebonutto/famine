#include "famine.h"

#include <elf.h> // EI_CLASS, ELFCLASSN

int process_elf(t_file *file)
{
	unsigned char *ident;

	ident = file->map;

	if (ident[EI_CLASS] == ELFCLASS64)
		return (process_elf64(file));

	// The ELFCLASS32 condition is already verified in is_valid_elf()
	return (process_elf32(file));
}
