#include "famine.h"

#include <elf.h> // EI_CLASS, ELFCLASSX

void process_elf(t_file *file)
{
	unsigned char *ident;

	ident = file->map;

	if (ident[EI_CLASS] == ELFCLASS64)
		process_elf64(file);

	// else if (ident[EI_CLASS] == ELFCLASS32)
	// 	process_elf32(file);
}
