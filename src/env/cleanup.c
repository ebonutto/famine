#include "famine.h"

#include <unistd.h> // unlink()

void self_delete(const char *path)
{
	unlink(path);
}
