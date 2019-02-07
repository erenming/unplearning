#include "unp.h"

void str_cli(FILE *fp, int sockfd) {
    pid_t   pid;
    char    sendline[MAXLINE], recvline[MAXLINE];
    if ( (pid = Fork() == 0) ) {    // child: server -> stdout
        while (Readline(sockfd, recvline, MAXLINE) > 0)
            Fputs(recvline, stdout);
        kill(getppid(), SIGTERM);
        exit(0);
    }
    while (Fgets(sendline, MAXLINE, fp) != NULL)
        Write(sockfd, sendline, strlen(sendline));
    Shutdown(sockfd, SHUT_WR);
    pause();
    return;
}