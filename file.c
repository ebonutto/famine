#include "famine.h"

#include <sys/mman.h> // MAP_FAILED, MAP_PRIVATE, PROT_READ, PROT_WRITE, munmap(), mmap()
#include <sys/stat.h> // struct stat, S_ISREG(), stat()
#include <unistd.h>   // close()

#include <fcntl.h> // O_RDONLY, open()

int map_file(t_famine_ctx *ctx, const char *filename)
{
	int fd;
	struct stat st;

	fd = open(filename, O_RDONLY);
	if (fd < 0) {
		return (1);
	}

	if (stat(filename, &st) < 0) {
		close(fd);
		return (1);
	}

	if (!S_ISREG(st.st_mode)) {
		close(fd);
		return (1);
	}

	ctx->map = mmap(NULL, st.st_size, PROT_READ | PROT_WRITE,
	                MAP_PRIVATE, fd, 0);
	if (ctx->map == MAP_FAILED) {
		close(fd);
		return (1);
	}

	ctx->filesize = st.st_size;

	close(fd);
	return (0);
}

void unmap_file(t_woody_ctx *ctx)
{
	munmap(ctx->map, ctx->filesize);
}
