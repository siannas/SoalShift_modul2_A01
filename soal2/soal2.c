#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
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

        struct stat st;
        char str[25];
        char loc[] = "/home/vagrant/prak2/soal2/hatiku/elen.ku";

        while(1){
            if(stat(loc, &st) != -1){
                struct passwd *pw = getpwuid(st.st_uid);
                struct group *gr = getgrgid(st.st_gid);

                sprintf(str,"%s%s", pw->pw_name,gr->gr_name);

                if( !strcmp(str, "www-datawww-data") ){
  
                        char mode[] = "0777";
                        int i = strtol(mode, 0, 8);

                        if(chmod (loc, i) >=0 ){
                                remove(loc);
                        }
                }
            }
        }

    exit(EXIT_SUCCESS);
}