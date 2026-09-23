#include "famine.h"

#include <stddef.h> // NULL

int main(void)
{
	const char *paths[] = {
		// "/tmp/test",
		// "/tmp/test2",
		"./tests",
		NULL
	};

	for (size_t i = 0; paths[i]; i++)
		scan_directory(paths[i]);

	return (0);
}
