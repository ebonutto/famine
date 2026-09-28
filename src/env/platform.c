#include "famine.h"

#include <sys/utsname.h> // struct utsname, uname()

#include <string.h> // strcmp()

int is_linux_x86_64(void)
{
	struct utsname buf;

	if (uname(&buf) < 0)
		return (0);

	if (strcmp(buf.sysname, "Linux") != 0)
		return (0);

	if (strcmp(buf.machine, "x86_64") != 0)
		return (0);

	return (1);
}
