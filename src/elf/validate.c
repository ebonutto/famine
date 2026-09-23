#include "famine.h"

#include <elf.h>

int is_valid_elf(t_file *file)
{
	unsigned char *ident;

	if (file->size < EI_NIDENT)
		return (0);

	ident = file->map;

	if ((ident[EI_MAG0] != ELFMAG0)
	    || (ident[EI_MAG1] != ELFMAG1)
	    || (ident[EI_MAG2] != ELFMAG2)
	    || (ident[EI_MAG3] != ELFMAG3))
		return (0);

	// Only little-endian architecture is handled here
	if (ident[EI_DATA] != ELFDATA2LSB)
		return (0);

	if (ident[EI_CLASS] != ELFCLASS64 && ident[EI_CLASS] != ELFCLASS32)
		return (0);

	return (1);
}
