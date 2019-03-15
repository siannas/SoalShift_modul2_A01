#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
   pid_t cpid;
   char buf;

   if (pipe(pipefd) == -1) {
       perror("pipe");
       exit(EXIT_FAILURE);
   }

   cpid = fork();
   if (cpid == -1) {
       perror("fork");
       exit(EXIT_FAILURE);
   }

   if (cpid == 0) {    /* Child reads from pipe */
       int pipefd[2];
       pid_t cpid2;
       cpid2 = fork();
       
       if(cpid == 0){
           close(pipefd[1]);          /* Close unused write end */
            while (read(pipefd[0], &buf, 1) > 0)
                    write(STDOUT_FILENO, &buf, 1);

            write(STDOUT_FILENO, "\n", 1);
            close(pipefd[0]);
            _exit(EXIT_SUCCESS);                
       }else{
            close(pipefd[0]);          /* Close unused read end */
       
            char *argv[]= {"ls","campur2/*.txt",NULL};
            execv("/bin/ls", argv);
           
            write(pipefd[1], argv[1], strlen(argv[1]));
            close(pipefd[1]);          /* Reader will see EOF */        
           
            wait(NULL);                /* Wait for child */
            exit(EXIT_SUCCESS);    
       }
       

   } else {            /* Parent writes argv[1] to pipe */

       char *argv[]= {"unzip","campur2.zip",NULL};
       execv("/bin/unzip", argv);
       
       wait(NULL);                /* Wait for child */
       exit(EXIT_SUCCESS);
   }
}
