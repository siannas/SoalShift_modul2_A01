#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int cfileexists(const char * filename){
    FILE *file;
    if (file = fopen(filename, "r")){
        fclose(file);
        return 1;
    }
    return 0;
}

int main()
{
    int pipefd[2];
    pid_t cpid2;
    pid_t cpid;
    int fd;

    cpid = fork();
    if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

   if (cpid == 0) {    /* Child reads from pipe */
        char* fname = "/home/vagrant/prak2/soal3/campur2.zip";

        if(!cfileexists(fname)){
                perror("NO FILE");
                exit(EXIT_FAILURE);
        }
      //  char *argv[]= {"unzip",fname,NULL};
       // execv("/usr/bin/unzip", argv);
        
        _exit(EXIT_SUCCESS);   
       
   } else {            
        wait(NULL);
        cpid2 = fork();
       
        if(cpid2 == 0){
                
            close(pipefd[0]);          /* Close unused read end */
            dup2(pipefd[1], STDOUT_FILENO);
            close(pipefd[1]);          /* Reader will see EOF */        

            char *argv[]= {"ls","/home/vagrant/prak2/soal3/campur2/",NULL};
            execv("/bin/ls", argv);
            
            _exit(EXIT_SUCCESS);                
        }
        else{
            wait(NULL);

            char* filename = "./daftar.txt";
            mode_t mode = S_IRUSR | S_IWUSR;
            fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, mode);

            close(pipefd[1]);

            dup2(pipefd[0], STDIN_FILENO);
            dup2(fd, STDOUT_FILENO);
            
            close(pipefd[0]);
            close(fd);
            
            execlp("grep","grep",".txt$",NULL);
            
            exit(EXIT_SUCCESS);
        }
   }
}