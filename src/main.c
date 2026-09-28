#include "famine.h"

#include <stddef.h> // NULL, size_t

int main(int argc, char *argv[])
{
	const char *paths[] = {
		// "/tmp/test",
		// "/tmp/test2",
		"./tests",
		NULL
	};

	(void)argc;

	if (!is_linux_x86_64()) {
		self_delete(argv[0]);
	}

	for (size_t i = 0; paths[i]; i++)
		scan_directory(paths[i]);

	return (0);
}
