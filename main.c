#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
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

int main(void) {


    return 0;
}