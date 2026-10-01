#include "famine.h"

#include <elf.h> // Elf32_Ehdr, Elf32_Phdr
#include <stdbool.h> // bool, false, true

static bool check_phdrs_bounds(t_file *file, Elf32_Ehdr *ehdr)
{
	if (ehdr->e_phnum == 0)
		return (false);
	if (ehdr->e_phoff > file->size)
		return (false);
	if (ehdr->e_phnum * sizeof(Elf32_Phdr) > file->size - ehdr->e_phoff)
		return (false);
	return (true);
}

int parse_elf32(t_file *file, t_elf32 *elf32)
{
	if (file->size < sizeof(Elf32_Ehdr))
		return (1);

	elf32->ehdr = (Elf32_Ehdr *)file->map;

	if (!check_phdrs_bounds(file, elf32->ehdr))
		return (1);

	elf32->phdr = (Elf32_Phdr *)(file->map + elf32->ehdr->e_phoff);
	return (0);
}
