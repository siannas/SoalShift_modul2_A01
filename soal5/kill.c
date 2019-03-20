#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <error.h>
#include <signal.h>
#include <unistd.h>
#include <syslog.h>

int main()
{
    FILE *getPIDS;
    char line[100];

    pid_t killpid;
    // setuid to that of root//
    pid_t mypid   = getpid();
    pid_t myppid  = getppid();

    getPIDS = popen("pidof soal5","r");
    while (fgets(line,sizeof line,getPIDS)) {
        int i  = atoi(line);
        kill(i,SIGKILL);
    }
}