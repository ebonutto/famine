#include "famine.h"

#include <elf.h> // EI_NIDENT, EI_CLASS, EI_DATA, EI_MAGN, ELFCLASSN, ELFDATA2LSB, ELFMAGN
#include <stdbool.h> // bool, false, true

bool is_valid_elf(t_file *file)
{
	unsigned char *ident;

	if (file->size < EI_NIDENT)
		return (false);

	ident = file->map;

	if ((ident[EI_MAG0] != ELFMAG0)
	    || (ident[EI_MAG1] != ELFMAG1)
	    || (ident[EI_MAG2] != ELFMAG2)
	    || (ident[EI_MAG3] != ELFMAG3))
		return (false);

	// Only little-endian architecture is handled here
	if (ident[EI_DATA] != ELFDATA2LSB)
		return (false);

	if (ident[EI_CLASS] != ELFCLASS64 && ident[EI_CLASS] != ELFCLASS32)
		return (false);

	return (true);
}
