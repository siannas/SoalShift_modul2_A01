#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>

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
    
        time_t now;
        double diff;
        struct stat st;
        char* file = "/home/vagrant/Documents/makanan/makan_enak.txt";
        char* new;
        int count = 0;
        FILE* sehat;

        while(1){
            if(stat(file, &st) == -1){
                perror("fail");
                exit(EXIT_FAILURE);
            }
            else{
                time(&now);
                diff = difftime(now, st.st_atime);

                if(diff <= 30 ){
                    sprintf(new,"/home/vagrant/Documents/makanan/makan_sehat%d.txt", ++count);
                    
                    sehat = fopen(new, "w+");
                }
            }
            sleep(5);
        }
        
        exit(EXIT_SUCCESS);
}