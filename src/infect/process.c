#include "famine.h"

void process_file(const char *path)
{
	t_file file;

	if (file_load(&file, path))
		return ;

	file_unload(&file);
}
