#include "famine.h"

#include <elf.h> // Elf64_Ehdr, Elf64_Phdr
#include <stdbool.h> // bool, false, true

static bool check_phdrs_bounds(t_file *file, Elf64_Ehdr *ehdr)
{
	if (ehdr->e_phnum == 0)
		return (false);
	if (ehdr->e_phoff > file->size)
		return (false);
	if (ehdr->e_phnum * sizeof(Elf64_Phdr) > file->size - ehdr->e_phoff)
		return (false);
	return (true);
}

int parse_elf64(t_file *file, t_elf64 *elf64)
{
	if (file->size < sizeof(Elf64_Ehdr))
		return (1);

	elf64->ehdr = (Elf64_Ehdr *)file->map;

	if (!check_phdrs_bounds(file, elf64->ehdr))
		return (1);

	elf64->phdr = (Elf64_Phdr *)(file->map + elf64->ehdr->e_phoff);
	return (0);
}
