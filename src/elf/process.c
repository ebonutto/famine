#include "famine.h"

void process_elf(t_file *file)
{
	if (!is_valid_elf(file))
		return ;

	if (file->map[EI_CLASS] == ELFCLASS64)
		process_elf64(file);

	// else if (file->map[EI_CLASS] == ELFCLASS32)
	// 	process_elf32(file);
}
