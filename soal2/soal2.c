#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>

int main(){
        struct stat st;
        char str[17];

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
        else{
                printf("%s\n",str);
        }

        return;
}