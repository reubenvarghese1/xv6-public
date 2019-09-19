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
load(void)
{
    int fd;
    struct test t;


    char buf[20];
    size_t nbytes;
    ssize_t bytes_read;
    nbytes = sizeof(buf);


    fd = open("testing.txt", O_RDONLY);
    if(fd >= 0) {
        printf(1, "ok: read backup file succeed\n");
    } else {
        printf(1, "error: read backup file failed\n");
        exit();
    }

    int n;

    while((n = read(fd, buf, nbytes)) > 0)
        write(1, buf, n);
    if(n < 0){
        printf(1, "Uniq: read error\n");
        exit();
    }

    printf(1, "read ok\n");
    close(fd);
}

int
main(void)
{
    save();
    load();

    exit();
}