#include "famine.h"

#include <elf.h> // EI_CLASS

void process_elf(t_file *file)
{
	unsigned char *ident;

	if (!is_valid_elf(file))
		return ;

	ident = file->map;

	if (ident[EI_CLASS] == ELFCLASS64)
		process_elf64(file);

	// else if (ident[EI_CLASS] == ELFCLASS32)
	// 	process_elf32(file);
}
