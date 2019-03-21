#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <dirent.h>

//fungsi di bawah ini buat ngambil "." sebagai char

const char *get_ext(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}

int isModified(const char *filename) {
	const char *dot;
    if(dot = strrchr(filename, '_')) {
		if(strcmp(dot,"_grey.png")==0) return 1;
	}
	return 0;
}

int main() {
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

  while(1) {
        DIR *d;
        struct dirent *dir;
        char* fdir = "/home/vagrant/modul2/gambar/";

        d = opendir(fdir);
        if (d){
            while ((dir = readdir(d)) != NULL){
				if (isModified(dir->d_name));
                else if(strcmp(get_ext(dir->d_name),"png") == 0){
					char temp[100]=""; //dikasih string kosong biar gak looping
					strncpy(temp, dir->d_name, (strlen(dir->d_name)-4)); //buat ambil nama file tanpa ekstensi .png
					strcat(temp, "_grey.png"); //string temp yang isinya nama file di gabung sama _grey.png dan disimpen di temp

					char olddir[100]=""; //sebagai directory lama (kurang paham gimana maksudnya)
					strcpy(olddir,fdir); //copy nama di home/rimas/modul2/gambar ke olddir
					strcat(olddir, dir->d_name); //olddir nyimpen nama file (kalau gak salah)

					char newdir[100]=""; //sebagai directory baru (kurang paham gimana maksudnya)
					strcpy(newdir, fdir); //copy nama di /home/rimas/modul2/gambar ke newdir
					strcat(newdir, temp); //newdir sekarang digabung dengan temp
				
					rename(olddir, newdir); //me rename olddir menjadi newddir ("[nama file]_grey.png")
                }
            }
        }
        closedir(d);
        sleep(1);
  }
  

  exit(EXIT_SUCCESS);
}