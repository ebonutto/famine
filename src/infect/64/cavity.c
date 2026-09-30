#include "famine.h"

#include <elf.h> // Elf64_Phdr
#include <stdint.h> // uintN_t, UINT64_MAX
#include <string.h> // memcpy()

static uint64_t elf64_find_next_segment(Elf64_Phdr *phdr, uint16_t phnum,
                                        uint16_t index)
{
	uint64_t curr, next, tmp;

	curr = phdr[index].p_offset;
	next = UINT64_MAX;

	for (uint32_t i = 0; i < phnum; i++) {
		if (i == index)
			continue ;

		tmp = phdr[i].p_offset;
		if (tmp > curr && tmp < next)
			next = tmp;
	}
	return (next);
}

int sign_elf64_cavity(t_file *file, t_elf64 *elf64)
{
	uint64_t cave_start, cave_end;

	for (uint32_t i = 0; i < elf64->ehdr->e_phnum; i++) {
		if (elf64->phdr[i].p_offset > file->size)
			continue ;
		if (elf64->phdr[i].p_filesz
		    > file->size - elf64->phdr[i].p_offset)
			continue ;

		cave_start = elf64->phdr[i].p_offset + elf64->phdr[i].p_filesz;
		cave_end = elf64_find_next_segment(elf64->phdr,
		                                   elf64->ehdr->e_phnum,
		                                   (uint16_t)i);

		if (cave_end == UINT64_MAX)
			continue ;
		if (cave_end <= cave_start)
			continue ;
		if (cave_end - cave_start < SIGNATURE_SIZE)
			continue ;
		if (SIGNATURE_SIZE > file->size - cave_start)
			continue ;

		memcpy(file->map + cave_start, SIGNATURE, SIGNATURE_SIZE);
		return (0);
	}
	return (1);
}
