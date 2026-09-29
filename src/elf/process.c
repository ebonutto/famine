#include "famine.h"

#include <elf.h> // EI_CLASS, ELFCLASSX

int process_elf(t_file *file)
{
	unsigned char *ident;

	ident = file->map;

	if (ident[EI_CLASS] == ELFCLASS64)
		return (process_elf64(file));

	// return (process_elf32(file));
	return (0);
}
