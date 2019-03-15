#include <stdio.h>
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
        char str[17];

        while(1){
            stat("/home/vagrant/prak2/soal2/hatiku/elen.ku", &st);
            struct passwd *pw = getpwuid(st.st_uid);
            struct group *gr = getgrgid(st.st_gid);

            sprintf(str,"%s%s", pw->pw_name,gr->gr_name);
            //      printf("%s\n", str);

            if( !strcmp(str, "www-datawww-data") ){
                    char *argv[] = {"chmod","777","/home/vagrant/prak2/soal2/hatiku/elen.ku",NULL};
                    execv("bin/chmod", argv);

                    //delete
                    char *argv2[] = {"rm","/home/vagrant/prak2/soal2/hatiku/elen.ku",NULL};
                    execv("/bin/rm", argv2);
            }
            
        }

        exit(EXIT_SUCCESS);
}