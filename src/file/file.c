#include "famine.h"

#include <sys/mman.h> // MAP_FAILED, MAP_SHARED, PROT_READ, PROT_WRITE, munmap(), mmap()
#include <sys/stat.h> // struct stat, S_ISREG(), fstat()

#include <fcntl.h> // O_RDWR, open()
#include <stddef.h> // NULL
#include <unistd.h> // close()

int open_file(t_file *file, const char *path)
{
	struct stat st;

	file->path = path;
	file->fd = open(path, O_RDWR);
	if (file->fd < 0)
		return (1);

	if (fstat(file->fd, &st) < 0) {
		close(file->fd);
		return (1);
	}

	if (!S_ISREG(st.st_mode) || st.st_size == 0) {
		close(file->fd);
		return (1);
	}

	file->size = st.st_size;
	return (0);
}

void close_file(t_file *file)
{
	close(file->fd);
}

int map_file(t_file *file)
{
	file->map = mmap(NULL, file->size,
	                 PROT_READ | PROT_WRITE,
	                 MAP_SHARED, file->fd, 0);
	if (file->map == MAP_FAILED)
		return (1);
	return (0);
}

void unmap_file(t_file *file)
{
	munmap(file->map, file->size);
}
