#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void msh_init(void) {
    printf("\033[38;5;28m");
    printf("███╗   ███╗██╗████████╗ ██████╗     ███████╗██╗  ██╗\n");
    printf("████╗ ████║██║╚══██╔══╝██╔═══██╗    ██╔════╝██║  ██║\n");
    printf("██╔████╔██║██║   ██║   ██║   ██║    ███████╗███████║\n");
    printf("██║╚██╔╝██║██║   ██║   ██║   ██║    ╚════██║██╔══██║\n");
    printf("██║ ╚═╝ ██║██║   ██║   ╚██████╔╝    ███████║██║  ██║\n");
    printf("╚═╝     ╚═╝╚═╝   ╚═╝    ╚═════╝     ╚══════╝╚═╝  ╚═╝\n");
    printf("\033[0m\n");
}

char* msh_read_cmd() {
    char* cmd = NULL;
    size_t buf_size = 0;

    if (getline(&cmd, &buf_size, stdin) == -1) {
        if (feof(stdin)) {
            exit(EXIT_SUCCESS);
        }

        fprintf(stderr, "\033[1;31mGetline error (%s)\033[0m\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    return cmd;
}

char** msh_parse_cmd(char* cmd) {
    char* cmd_cpy = strdup(cmd);

    if (!cmd_cpy) {
        fprintf(stderr, "\033[1;31mAllocation error (%s)\033[0m\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    char* token = NULL;
    char* delimiter = " \n";
    char** argv = NULL;
    int argc = 0;

    token = strtok(cmd_cpy, delimiter);

    while (token) {
        argc++;
        token = strtok(NULL, delimiter);
    }

    argv = malloc(sizeof(char*) * (argc + 1));

    if (!argv) {
        fprintf(stderr, "\033[1;31mAllocation error (%s)\033[0m\n", strerror(errno));
        free(cmd_cpy);
        exit(EXIT_FAILURE);
    }

    token = strtok(cmd, delimiter);

    while (token) {
        argv[argc] = token;
        token = strtok(NULL, delimiter);
    }

    argv[argc] = NULL;

    return argv;
}

int msh_execute_cmd(char** argv) {
    pid_t pid = fork();
    int status = 0;

    if (pid == 0) {
        if (execvp(argv[0], argv) == -1) {
            fprintf(stderr, "\033[1;31Execution error (%s)\033[0m\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
    }
    else if (pid < 0) {
        fprintf(stderr, "\033[1;31Process creation error (%s)\033[0m\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    else {
        waitpid(pid, &status, WAIT_MYPGRP);

        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        }
    }

    return -1;
}

int main(void) {


    return 0;
}