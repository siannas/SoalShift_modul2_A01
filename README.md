# SoalShift_modul2_A01

index |
--- | 
[nomor 1](#no1) |
[nomor 2](#no2) |
[nomor 3](#no3) |
[nomor 4](#no4) |
[nomor 5](#no5) |

### <a name="no1" ></a>Nomor 1
---
 Elen mempunyai pekerjaan pada studio sebagai fotografer. Suatu hari ada seorang klien            yang bernama Kusuma yang meminta untuk mengubah nama file yang memiliki ekstensi            .png menjadi “[namafile]_grey.png”. Karena jumlah file yang diberikan Kusuma tidak          manusiawi, maka Elen meminta bantuan kalian untuk membuat suatu program C yang            dapat mengubah nama secara otomatis dan diletakkan pada direktori         /home/[user]/modul2/gambar. Catatan : Tidak boleh menggunakan crontab

Penjelasan

 ```c
 ...
 DIR *d;
struct dirent *dir;
char* fdir = "/home/vagrant/modul2/gambar/";
d = opendir(fdir);
...
 ```
Menggunakan struct dirent untuk membaca file di direktori nantinya.
sebelumnya harus memasukkan alamat direktori ke DIR pointer.

 ```c
 while ((dir = readdir(d)) != NULL)
 ```
 Melakukan pembacaan semua file yang ada dalam direktori.

 ```c
 if (isModified(dir->d_name));
else if(strcmp(get_ext(dir->d_name),"png") == 0)
 ```
 apabila file pernah diubah namanya menjadi (nama file)_grey.png, maka tidak dilakukan apa-apa. Apabila extension .png saja, maka dilakukan pengubahan nama file tersebut.


### <a name="no2" ></a>Nomor 2
---
 Pada suatu hari Kusuma dicampakkan oleh Elen karena Elen dimenangkan oleh orang            lain. Semua kenangan tentang Elen berada pada file bernama “elen.ku” pada direktori            “hatiku”. Karena sedih berkepanjangan, tugas kalian sebagai teman Kusuma adalah          membantunya untuk menghapus semua kenangan tentang Elen dengan membuat         program C yang bisa mendeteksi owner dan group dan menghapus file “elen.ku” setiap             3 detik dengan syarat ketika owner dan grupnya menjadi “www-data”. Ternyata kamu            memiliki kendala karena permission pada file “elen.ku”. Jadi, ubahlah permissionnya          menjadi 777. Setelah kenangan tentang Elen terhapus, maka Kusuma bisa move on. Catatan: Tidak boleh menggunakan crontab 

Penjelasan

```c
...
if(stat(loc, &st) != -1){
    ...
```
menggunakan struct stat untuk mengambil informasi file.

```c
struct passwd *pw = getpwuid(st.st_uid);
struct group *gr = getgrgid(st.st_gid);
```
mengambil informasi uid dan gid dari stat.

```c
sprintf(str,"%s%s", pw->pw_name,gr->gr_name);
if( !strcmp(str, "www-datawww-data") ){...}
```
selanjutnya membandingkan nama owner dan group file, apabila memiliki nama www-data maka harus dihapus.


### <a name="no3" ></a>Nomor 3
---
Diberikan file campur2.zip. Di dalam file tersebut terdapat folder “campur2”.  Buatlah program C yang dapat : i)  mengekstrak file zip tersebut. ii) menyimpan daftar file dari folder “campur2” yang memiliki ekstensi .txt ke dalam file              daftar.txt.  Catatan:  ○ Gunakan fork dan exec. ○ Gunakan minimal 3 proses yang diakhiri dengan exec. ○ Gunakan pipe ○ Pastikan file daftar.txt dapat diakses dari text editor

Penjelasan

```c
int pipefd[2];
pid_t cpid2;
pid_t cpid;
int fd;

cpid = fork();

if (pipe(pipefd) == -1) {...}
```
mengalokasikan pipe pada array of integer pipefd[2]. lalu melakukan fork yang pertama.


```c
if (cpid == 0) {    /* Child reads from pipe */
       char* fname = "/home/vagrant/prak2/soal3/campur2.zip";
       
       ...
       char *argv[]= {"unzip",fname,NULL};
       execv("/usr/bin/unzip", argv);
       ...
       
} else { ... }   /*parent*/
```
Pada process pertama kita akan mengunzip file campur2.zip .

```c
/*parent*/
 cpid2 = fork();
       
 if(cpid2 == 0){

     close(pipefd[0]);         
     dup2(pipefd[1], STDOUT_FILENO);
     close(pipefd[1]);

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
```
berikutnya melakukan fork yang kedua. Pada child processnya kita mengclose pipe untuk readnya. baru menduplikasi pipefd[1] dengan standart output sehingga output dari execv akan dapat diteruskan ke process lainnya.

barulah pada parent process, kita mengclose pipe untuk write dan menduplikasi pipefd[0] ke standart input. baru kita menduplikasi fd dengan standart output yang mana sebelumnya kita mengalokasikan fd sebagai file output yang telah kita open(). baru mengeksekusi execv grep untuk mengambil hanya .txt saja.


### <a name="no4" ></a>Nomor 4
---
Dalam direktori /home/[user]/Documents/makanan terdapat file makan_enak.txt yang       berisikan daftar makanan terkenal di Surabaya. Elen sedang melakukan diet dan           seringkali tergiur untuk membaca isi makan_enak.txt karena ngidam makanan enak.          Sebagai teman yang baik, Anda membantu Elen dengan membuat program C yang            berjalan setiap 5 detik untuk memeriksa apakah file makan_enak.txt pernah dibuka           setidaknya 30 detik yang lalu (rentang 0 - 30 detik). Jika file itu pernah dibuka, program Anda akan membuat 1 file makan_sehat#.txt di             direktori /home/[user]/Documents/makanan dengan '#' berisi bilangan bulat dari 1         sampai tak hingga untuk mengingatkan Elen agar berdiet

Contoh: File makan_enak.txt terakhir dibuka pada detik ke-1 Pada detik ke-10 terdapat file makan_sehat1.txt dan makan_sehat2.txt 
3/14/2019 Soal Shift Modul 2 - Google Dokumen
https://docs.google.com/document/d/1OyQL7uNpg36ykwTYZjVaGGIwz0D9qGnRtZILcmQmo3A/edit 3/3
 
Catatan:  - dilarang menggunakan crontab - Contoh nama file : makan_sehat1.txt, makan_sehat2.txt, dst

Penjelasan

```c
time_t now;
double diff;
struct stat st;
char* file = "/home/vagrant/Documents/makanan/makan_enak.txt";
char* new;
int count = 0;
FILE* sehat;

if(stat(file, &st) == -1){..}
```
Melakukan fungsi stat() untuk mendapatkan informasi file.

```c
...
else{
    time(&now);
    diff = difftime(now, st.st_atime);

    if(diff <= 30 ){
        sprintf(new,"/home/vagrant/Documents/makanan/makan_sehat%d.txt", ++count);

        sehat = fopen(new, "w+");
    }
}
```
berikutnya mengambil waktu saat ini dengan fungsi time(). Selanjutnya melihat perbedaan waktu antara waktu saat ini dengan waktu terakhir kali dimodifikasi. apabila selisih waktu diantara 30 detik maka akan dibuat file reminder dengan nama makan_sehat(count).txt.


### <a name="no5" ></a>Nomor 5
---
 Kerjakan poin a dan b di bawah: a. Buatlah program c untuk mencatat log setiap menit dari file log pada syslog ke              /home/[user]/log/[dd:MM:yyyy-hh:mm]/log#.log Ket: - Per 30 menit membuat folder /[dd:MM:yyyy-hh:mm] - Per menit memasukkan log#.log ke dalam folder tersebut ‘#’ : increment per menit. Mulai dari 1 b. Buatlah program c untuk menghentikan program di atas. NB: Dilarang menggunakan crontab dan tidak memakai argumen ketika menjalankan          program. 
 
 Penjelasan 
 
 ```c
 while(1){
         sleep(60);

         if(count == 0){
                 t = time(NULL);
                 tm = *localtime(&t);
                 sprintf(folder, "/home/vagrant/log/%02d:%02d:%d-%02d:%02d",tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min);
                 makeDir(folder);
                 count = 1;
         }

         ...
 }
 ```
 program akan bekerja setiap menit sehingga kita sleep selama 60 detik. Setiap count masih 0 maka akan dibuatkan folder baru.
 
 ```c
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
 ```
 selanjutnya membuat file baru pada variable pointer File dengan nama log dan kita melakukan copy dari file syslog ke dalamnya. berikutnya increment count dengan 1 dan kita mod dengan 31 karena kita ingin tiap 30 menit akan mereset count menjadi 0 kembali untuk membuat folder.
