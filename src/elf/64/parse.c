#include "famine.h"

#include <elf.h> // Elf64_Ehdr, Elf64_Phdr

int parse_elf64(t_file *file, t_elf64 *elf64)
{
	if (file->size < sizeof(Elf64_Ehdr))
		return (1);

	elf64->ehdr = (Elf64_Ehdr *)file->map;

	if (elf64->ehdr->e_phnum == 0)
		return (1);
	if (elf64->ehdr->e_phoff > file->size)
		return (1);
	if (elf64->ehdr->e_phnum * sizeof(Elf64_Phdr) > file->size - elf64->ehdr->e_phoff)
		return (1);

	elf64->phdr = (Elf64_Phdr *)(file->map + elf64->ehdr->e_phoff);
	return (0);
}
