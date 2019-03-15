#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

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
    
    
        int count = 1;
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        char folder[18], dir[31], file[11];
    
        while(1){
                sleep(60);
            
                if(count == 1){
                        sprintf(folder, "/home/vagrant/log/%02d:%02d:%d-%02d:%02d",tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min);
                        char *argv[]= {"mkdir",folder,NULL};
                        execv("/bin/mkdir", argv);
                }
            
                strcpy(dir, folder);
                
                sprintf(file,"/log%d.log",count);
                strcat(dir,file);
                    
                char *argv2[]= {"cp","/var/log/syslog",dir,NULL};
                execv("/bin/cp", argv2);

                count = (count+1)%31;
        }
        
        exit(EXIT_SUCCESS);
}