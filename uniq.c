#include "types.h"
#include "user.h"
#include "fcntl.h"

#define N 100

struct test {
    char name;
    int number;
};

void
save(void)
{
    int fd;
    struct test t;
    t.name = 's';
    t.number = 1;

    fd = open("backup", O_CREATE | O_RDWR);
    if(fd >= 0) {
        printf(1, "ok: create backup file succeed\n");
    } else {
        printf(1, "error: create backup file failed\n");
        exit();
    }

    int size = sizeof(t);
    if(write(fd, &t, size) != size){
        printf(1, "error: write to backup file failed\n");
        exit();
    }
    printf(1, "write ok\n");
    close(fd);
}


void
loadfrompipe(){


    char byf[1024];
    int count=0;
    char prevline[720]={0};
    char nextline[720]={0};
    int n , i;
    int l =0;
    int start; int end;
    int endoflineafterfor;
    int prev=0;
    int next=0;
    int p;

    char buf[65536];

    while((n = read(fd, buf, 65536)) > 0){
        int y;
        if(buf[n-1]!= '\n'){
            buf[n] = '\n';
            n++;
        }
        for(y=0;y<n;y++){
            //printf(1,"%c",buf[y]);
            if(buf[y]=='\n'){
                //printf(1,"%c",buf[y-1]);
                nextline[next]=buf[y];
                next++;
                int j;int count = 0;
                if(strcmp(prevline,nextline)!=0){
                    printf(1,"%s",nextline);
                    printf(1,"%s","Unique line above\n");
                }

//                for (j = 0; j < next; j++) {
//                    if(prevline[j] == nextline[j]){
//                        printf(1,"%c",prevline[j]);
//                        count++;
//                    }
//                    else{
//                        break;
//                    }
//                }
//                if(count == next){
//                    int k;
//                    for (k = 0; k < next; k++) {
//                        //printf(1,"%c",prevline[k]);
//                    }
//                }

                //copying one array to another
                int m;
                for (m = 0; m < 720; m++) {
                    prevline[m] = nextline[m];
                }
                next = 0;
                // printf(1,"%s%d","yomana",strlen(prevline));
            }
            else{
                //Put stuff into next line if character isnt new line
                nextline[next] = buf[y];
                next++;
            }
        }
    }



    if(n < 0){

        printf(1, "Uniq: read error\n");
        exit();
    }

    printf(1, "read ok\n");
}

void
load(int fd,int qt)
{



    char byf[1024];
    int count=0;
    char prevline[720]={0};
    char nextline[720]={0};
    int n , i;
    int l =0;
    int start; int end;
    int endoflineafterfor;
    int prev=0;
    int next=0;
    int p;

    while((p = read(qt, byf, sizeof(byf))) > 0){
        int k;
        for(k=0;k<p;k++){
            count++;
        }
    }

    char *buf = malloc( sizeof(char) * count);


    while((n = read(fd, buf, count)) > 0){
        int y;
        if(buf[n-1]!= '\n'){
            buf[n] = '\n';
            n++;
        }
        for(y=0;y<n;y++){
            //printf(1,"%c",buf[y]);
            if(buf[y]=='\n'){
                //printf(1,"%c",buf[y-1]);
                nextline[next]=buf[y];
                next++;
                int j;int count = 0;
                if(strcmp(prevline,nextline)!=0){
                    printf(1,"%s",nextline);
                    printf(1,"%s","Unique line above\n");
                }

//                for (j = 0; j < next; j++) {
//                    if(prevline[j] == nextline[j]){
//                        printf(1,"%c",prevline[j]);
//                        count++;
//                    }
//                    else{
//                        break;
//                    }
//                }
//                if(count == next){
//                    int k;
//                    for (k = 0; k < next; k++) {
//                        //printf(1,"%c",prevline[k]);
//                    }
//                }

                //copying one array to another
                int m;
                for (m = 0; m < 720; m++) {
                    prevline[m] = nextline[m];
                }
                next = 0;
               // printf(1,"%s%d","yomana",strlen(prevline));
            }
            else{
                //Put stuff into next line if character isnt new line
                nextline[next] = buf[y];
                next++;
            }
        }
    }



    if(n < 0){

        printf(1, "Uniq: read error\n");
        exit();
    }

    printf(1, "read ok\n");
}

int
main(int argc, char *argv[])
{
    int fd,i,qt;
    save();
    if(argc <= 1){
        loadfrompipe();
        exit();
    }

    for(i = 1; i < argc; i++){
        if((fd = open(argv[i], O_RDONLY)) < 0){
            printf(1, "Uniq: cannot open %s\n", argv[i]);
            exit();
        }
        if((qt = open(argv[i], O_RDONLY)) < 0){
            printf(1, "Uniq: cannot open %s\n", argv[i]);
            exit();
        }
        load(fd,qt);
        close(fd);
        close(qt);
    }

    exit();
}