// file : pomoc.c 
// date : 2026-06-27
// std  : c23

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "protocol.h"

// this is just the normal arg parsing. 

// function for sending command to the daemon. 
static int send_command(const char *cmd, char *reply, int reply_size) {
    // initialise the socket and crate fd. 
    int fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd < 0) { perror("socket"); return -1; }

    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    snprintf(addr.sun_path, sizeof(addr.sun_path), "%s", SOCKET_PATH);

    if (connect(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        fprintf(stderr, "%s: pomod not running\n", RES_ERR);
        close(fd);
        return -1;
    }

    write(fd, cmd, strlen(cmd));

    int n = read(fd, reply, reply_size - 1);
    if (n > 0) reply[n] = 0;
    else reply[0] = 0;

    close(fd);
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage: pomoc <command> [args]\n");
        return 1;
    }

    char cmd[256];
    char reply[256];
    memset(cmd,   0, sizeof(cmd));
    memset(reply, 0, sizeof(reply));

    if (strcmp(argv[1], "start") == 0) {
        snprintf(cmd, sizeof(cmd), "%s", CMD_START);

    } else if (strcmp(argv[1], "pause") == 0) {
        snprintf(cmd, sizeof(cmd), "%s", CMD_PAUSE);

    } else if (strcmp(argv[1], "end") == 0) {
        snprintf(cmd, sizeof(cmd), "%s", CMD_END);

    } else if (strcmp(argv[1], "status") == 0) {
        if (argc == 2)
            snprintf(cmd, sizeof(cmd), "%s", CMD_STATUS);
        else if (strcmp(argv[2], "active") == 0)
            snprintf(cmd, sizeof(cmd), "%s", CMD_STATUS_ACT);
        else if (strcmp(argv[2], "time") == 0)
            snprintf(cmd, sizeof(cmd), "%s", CMD_STATUS_TIME);
        else if (strcmp(argv[2], "hr") == 0)
            snprintf(cmd, sizeof(cmd), "%s", CMD_STATUS_HR);
        else if (strcmp(argv[2], "min") == 0)
            snprintf(cmd, sizeof(cmd), "%s", CMD_STATUS_MIN);
        else if (strcmp(argv[2], "sec") == 0)
            snprintf(cmd, sizeof(cmd), "%s", CMD_STATUS_SEC);
        else {
            fprintf(stderr, "%s: unknown status field '%s'\n", RES_ERR, argv[2]);
            return 1;
        }

    } else if (strcmp(argv[1], "focus") == 0) {
        if (argc < 3) { fprintf(stderr, "%s: missing args\n", RES_ERR); return 1; }
        if (argc == 4)
            snprintf(cmd, sizeof(cmd), "%s focus %s %s", CMD_INCR, argv[2], argv[3]);
        else
            snprintf(cmd, sizeof(cmd), "%s %s", CMD_SET_FOCUS, argv[2]);

    } else if (strcmp(argv[1], "break") == 0) {
        if (argc < 3) { fprintf(stderr, "%s: missing args\n", RES_ERR); return 1; }
        if (argc == 4)
            snprintf(cmd, sizeof(cmd), "%s break %s %s", CMD_INCR, argv[2], argv[3]);
        else
            snprintf(cmd, sizeof(cmd), "%s %s", CMD_SET_BREAK, argv[2]);

    } else {
        fprintf(stderr, "%s: unknown command '%s'\n", RES_ERR, argv[1]);
        return 1;
    }

    if (send_command(cmd, reply, sizeof(reply)) == 0)
        printf("%s\n", reply);

    return EXIT_SUCCESS;
}
