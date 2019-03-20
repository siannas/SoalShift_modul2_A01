#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>

#define SIZE (1024*1024)

int makeDir(char* folder){
        int status;
        status = mkdir(folder, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        return status;
}

int main(){
        pid_t pid, sid;

        pid = fork();

        if (pid < 0) {
        exit(EXIT_FAILURE);
        }

        if (pid > 0) {
        exit(EXIT_SUCCESS);
        }

        umask(0);

        sid = setsid();

        if (sid < 0) {
        exit(EXIT_FAILURE);
        }

        if ((chdir("/")) < 0) {
        exit(EXIT_FAILURE);
        }

        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);
    
        FILE* syslog, *log;
        char buffer[SIZE];
        size_t bytes;
        int count = 0;
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        char folder[50], dir[50], file[50];
    
        while(1){
                sleep(60);

                if(count == 0){
                        sprintf(folder, "/home/vagrant/log/%02d:%02d:%d-%02d:%02d",tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min);
                        while(makeDir(folder)!=0);
                        count = 1;
                }
            
                strcpy(dir, folder);
                sprintf(file,"/log%d.log",count);
                strcat(dir,file);

                syslog = fopen("/var/log/syslog", "r");
                log = fopen(dir, "w+");

                //read write file
                while (0 < (bytes = fread(buffer, 1, sizeof(buffer), syslog)))
                        fwrite(buffer, 1, bytes, log);

                fclose(syslog);
                fclose(log);

                count = (count+1)%31;
        }
        
        exit(EXIT_SUCCESS);
}