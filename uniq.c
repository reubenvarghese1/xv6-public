#include "types.h"
#include "user.h"
#include "fcntl.h"

void
loadfrompipe(int cflag,int dflag,int iflag){
    char prevline[720]={0};
    char nextline[720]={0};
    int n;
    int startofline=0;
    int next=0;

    char buf[1200];


    int alreadyusedlines[100]={0};
    int alreadyusedlinesprinted[50]={0};
    int dupnumber = 0;
    int printedlinenumber=0;
    int linecounter=1;
    //Previous file in buffer count
    int prevstart =0;
    int prevend =0;int printedfirsttime=0;

    while((n = read(0, buf, sizeof(buf))) > 0){
        int y;
        if(buf[n-1]!= '\n'){
            buf[n] = '\n';
            n++;
        }
        for(y=0;y<n;y++){
            if(buf[y]=='\n'){
                nextline[next]=buf[y];
                next++;
                if (dflag == 1){
                    int q;int calculateascii = 0;
                    int h;
                    //skipping last character hence next-1. Calculating ascii for line
                    for(h=0;h<next-1;h++){
                        calculateascii = calculateascii + nextline[h] + 0;
                    }

                    int ym;
                    //calculating ascii for line and checking if it has been used before
                    for(ym=0;ym<printedlinenumber;ym++){
                        if (alreadyusedlines[ym] == calculateascii){
                            int bk;int contains = 0;
                            //Now to check if it has been printed before
                            for (bk=0;bk<dupnumber;bk++){
                                if(alreadyusedlinesprinted[bk] == calculateascii){
                                    contains=1;
                                    break;
                                }
                            }
                            //print if not already printed
                            if(contains == 0){
                                alreadyusedlinesprinted[dupnumber] = calculateascii;
                                dupnumber++;
                                for (q = startofline; q < y+1; q++) {
                                    printf(1,"%c",buf[q]);
                                }
                            }
                        }
                    }
                    //adding ascii of all lines to the list of used lines
                    alreadyusedlines[printedlinenumber] = calculateascii;
                    printedlinenumber++;
                }

                else{

                    if(strcmp(prevline,nextline)!=0){
                        if (cflag == 1){
                            int yk;
                            //printf("%s","Hi buddy");
                            if(printedfirsttime == 1){
                                printf(1,"%d ",linecounter);
                            }

                            for (yk = prevstart;  yk <prevend ; yk++) {
                                printf(1,"%c",buf[yk]);
                            }
                            linecounter = 1;

                            //If last line and last two lines not equal, then print last line.
                            if(y+2>n){
                                int ymk;
                                printf(1,"%d ",linecounter);
                                for (ymk= prevend;  ymk <n ; ymk++) {
                                    printf(1,"%c",buf[ymk]);
                                }
                            }
                            printedfirsttime =1;
                        }
                        else{
                            int q;
                            for (q = startofline; q < y+1; q++) {
                                printf(1,"%c",buf[q]);
                            }
                        }
                    }
                    else{
                        if (cflag == 1) {
                            //checking if end of file reached
                            linecounter++;
                            if (y + 2 > n) {
                                int ym;
                                printf(1, "%d ", linecounter);
                                for (ym = prevend; ym < n; ym++) {
                                    printf(1, "%c", buf[ym]);
                                }
                            }
                        }
                    }
                }

                //Writing location of previous line ka starting and ending in terms of original buf
                prevstart = startofline;
                prevend = y+1;

                //copying one array to another
                int m;
                for (m = 0; m < 720; m++) {
                    prevline[m] = nextline[m];
                }
                next = 0;
                startofline = y+1;
            }
            else{
                //Put stuff into next line if character isnt new line
                if (iflag ==1){
                    //converting stuff to lowercase for comparison
                    if(buf[y]>='A' && buf[y]<='Z'){
                        nextline[next]=buf[y]+32;
                    }
                    else{
                        nextline[next]=buf[y];
                    }
                }
                else {
                    nextline[next] = buf[y];
                }
                next++;
            }
        }
    }



    if(n < 0){

        printf(1, "Uniq: read error\n");
        exit();
    }
}

void
load(int fd,int qt,int cflag,int dflag,int iflag)
{
    char *byf = malloc( sizeof(char) * 20);int p;int count=0;int linescount=0;
    while((p = read(qt, byf, sizeof(byf))) > 0){
        int k;
        for(k=0;k<p;k++){
            count++;
            if(byf[k]=='\n'){
                linescount++;
            }
        }
    }
    free(byf);
    char prevline[720]={0};
    char nextline[720]={0};
    int n;
    int startofline=0;
    int next=0;

    //The following arrays are to store the ascii values for the d flag
     int alreadyusedlines[512] = {0};
     int alreadyusedlinesprinted[30] = {0};
    int dupnumber = 0;
    int printedlinenumber=0;
    int linecounter=1;
    //Previous file in buffer count
    int prevstart =0;
    int prevend =0;int printedfirsttime=0;
    char *buf = malloc( sizeof(char) * count);


    while((n = read(fd, buf, count)) > 0){
        int y;
        if(buf[n-1]!= '\n'){
            buf[n] = '\n';
            n++;
        }
        for(y=0;y<n;y++){
            if(buf[y]=='\n'){
                nextline[next]=buf[y];
                next++;
                if (dflag == 1){
                        int q;int calculateascii = 0;
                        int h;
                        //skipping last character hence next-1. Calculating ascii for line
                        for(h=0;h<next-1;h++){
                            calculateascii = calculateascii + nextline[h] + 0;
                        }

                        int ym;
                        //calculating ascii for line and checking if it has been used before
                        for(ym=0;ym<printedlinenumber;ym++){
                            if (alreadyusedlines[ym] == calculateascii){
                                int bk;int contains = 0;
                                //Now to check if it has been printed before
                                for (bk=0;bk<dupnumber;bk++){
                                    if(alreadyusedlinesprinted[bk] == calculateascii){
                                        contains=1;
                                        break;
                                    }
                                }
                                //print if not already printed
                                if(contains == 0){
                                    alreadyusedlinesprinted[dupnumber] = calculateascii;
                                    dupnumber++;
                                    for (q = startofline; q < y+1; q++) {
                                        printf(1,"%c",buf[q]);
                                    }
                                }
                            }
                        }
                        //adding ascii of all lines to the list of used lines
                        alreadyusedlines[printedlinenumber] = calculateascii;
                        printedlinenumber++;
                }

                else{

                    if(strcmp(prevline,nextline)!=0){
                        if (cflag == 1){
                            int yk;
                            if(printedfirsttime == 1){
                                printf(1,"%d ",linecounter);
                            }

                            for (yk = prevstart;  yk <prevend ; yk++) {
                                printf(1,"%c",buf[yk]);
                            }
                            linecounter = 1;

                            //If last line and last two lines not equal, then print last line.
                            if(y+2>n){
                                int ymk;
                                printf(1,"%d ",linecounter);
                                for (ymk= prevend;  ymk <n ; ymk++) {
                                    printf(1,"%c",buf[ymk]);
                                }
                            }
                            printedfirsttime =1;
                        }
                        else{
                            int q;
                            for (q = startofline; q < y+1; q++) {
                                printf(1,"%c",buf[q]);
                            }
                        }
                    }
                    else{
                        if (cflag == 1) {
                            //checking if end of file reached
                            linecounter++;
                            if (y + 2 > n) {
                                int ym;
                                printf(1, "%d ", linecounter);
                                for (ym = prevend; ym < n; ym++) {
                                    printf(1, "%c", buf[ym]);
                                }
                            }
                        }
                    }
                }

                //Writing location of previous line ka starting and ending in terms of original buf
                prevstart = startofline;
                prevend = y+1;

                //copying one array to another
                int m;
                for (m = 0; m < 720; m++) {
                    prevline[m] = nextline[m];
                }
                next = 0;
                startofline = y+1;
            }
            else{
                //Put stuff into next line if character isnt new line
                if (iflag ==1){
                    //converting stuff to lowercase for comparison
                    if(buf[y]>='A' && buf[y]<='Z'){
                        nextline[next]=buf[y]+32;
                    }
                    else{
                        nextline[next]=buf[y];
                    }
                }
                else {
                    nextline[next] = buf[y];
                }
                next++;

            }
        }
    }



    if(n < 0){

        exit();
    }
}

int
main(int argc, char *argv[])
{
    int fd,i,qt;
    int cflag=0;
    int dflag =0;
    int iflag=0;
    int argscount = 0;
    for(i = 1; i < argc; i++){
        if (strcmp(argv[i] , "-c") == 0){
            cflag = 1;
            argscount++;
        }
        else if(strcmp(argv[i] , "-d") == 0){
            cflag = 0;
            dflag = 1;
           // iflag =1;
            argscount++;
        }
        else if(strcmp(argv[i] , "-i") == 0){
            iflag = 1;
            argscount++;
        }
        else{
            continue;
        }
    }

    if((argc-argscount) <=1){
        loadfrompipe(cflag,dflag,iflag);
        exit();
    }
    else{
        for(i = 1; i < argc; i++){
            if (strcmp(argv[i] , "-c") == 0){
                cflag = 1;
                argscount++;
            }
            else if(strcmp(argv[i] , "-d") == 0){
                cflag = 0;
                dflag = 1;
              //  iflag =1;
                argscount++;
            }
            else if(strcmp(argv[i] , "-i") == 0){
                iflag = 1;
                argscount++;
            }
            else{
                if((fd = open(argv[i], O_RDONLY)) < 0){
                    printf(1, "Uniq: cannot open %s\n", argv[i]);
                    exit();
                }
                if((qt = open(argv[i], O_RDONLY)) < 0){
                    printf(1, "Uniq: cannot open %s\n", argv[i]);
                    exit();
                }
                load(fd,qt,cflag,dflag,iflag);
                close(fd);
                close(qt);
            }
        }
    }

    exit();
}