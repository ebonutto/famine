#include "famine.h"

int service_is_enabled(const char* unit) {

    char* const argv[] = {"systemctl", "--quiet", "--user", "is-enabled", (char*)unit, NULL};
    pid_t pid = fork();
    int status;

    if (pid < 0)
        return (0);
    if (pid == 0) {
        execve("/usr/bin/systemctl", argv, environ);
        _exit(127);
    }
    if (waitpid(pid, &status, 0) < 0)
        return (0);

    return (WIFEXITED(status) && WEXITSTATUS(status) == 0);
}
