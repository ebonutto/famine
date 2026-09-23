#include "famine.h"

void process_file(const char *path)
{
	t_file file;

	if (load_file(&file, path))
		return ;

	process_elf(&file);

	unload_file(&file);
}
