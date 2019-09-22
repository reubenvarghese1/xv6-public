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
load(int fd)
{


    char buf[20];
    char prevline[512]={0};
    char nextline[512]={0};
    int n , i;
    int l =0;
    int start; int end;
    int endoflineafterfor;
    int prev=0;
    int next=0;

    while((n = read(fd, buf, sizeof(buf))) > 0){
        int y;
        for(y=0;y<n;y++){
            nextline[next] = buf[y];
            printf(1,"%s",nextline[next]);
            next++;
//            if(buf[y]=='\n'){
//
//
//                printf(1,"3 found!");
//            }
//            else{
//                //Put stuff into next line if character isnt new line
//                nextline[next] = buf[y];
//                next++;
//            }
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
    int fd,i;
    save();
    if(argc <= 1){
        load(0);
        exit();
    }

    for(i = 1; i < argc; i++){
        if((fd = open(argv[i], O_RDONLY)) < 0){
            printf(1, "Uniq: cannot open %s\n", argv[i]);
            exit();
        }
        load(fd);
        close(fd);
    }

    exit();
}