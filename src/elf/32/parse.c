#include "famine.h"

#include <elf.h> // ElfN_Ehdr, ElfN_Phdr

int parse_elf32(t_file *file, t_elf32 *elf32)
{
	if (file->size < sizeof(Elf32_Ehdr))
		return (1);

	elf32->ehdr = (Elf32_Ehdr *)file->map;

	if (elf32->ehdr->e_phnum == 0)
		return (1);
	if (elf32->ehdr->e_phoff > file->size)
		return (1);
	if (elf32->ehdr->e_phnum * sizeof(Elf32_Phdr)
	    > file->size - elf32->ehdr->e_phoff)
		return (1);

	elf32->phdr = (Elf32_Phdr *)(file->map + elf32->ehdr->e_phoff);
	return (0);
}
