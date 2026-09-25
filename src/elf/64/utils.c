#include "famine.h"

#include <elf.h> // Elf64_Phdr
#include <limits.h> // UINT64_MAX
#include <stdint.h> // uintX_t

uint64_t elf64_find_next_segment(Elf64_Phdr *phdr, uint32_t phnum, uint32_t index)
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
