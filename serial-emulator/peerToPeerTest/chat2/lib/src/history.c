#include <sys/videoprints.h>
#include <sys/serial.h>
#include <sys/io.h>

void montahistorico(char *m, int d, int mo, int y, int min, int sec, int hr, char** t, int line) {
    int i = 16;
    t[line][i++] = ((d / 10)+0x30);
    t[line][i++] = ((d % 10)+0x30);
    t[line][i++] = '/';
    t[line][i++] = ((mo / 10)+0x30);
    t[line][i++] = ((mo % 10)+0x30);
    t[line][i++] = '/';
    t[line][i++] = ((y / 10)+0x30);
    t[line][i++] = ((y % 10)+0x30);
    t[line][i++] = ' ';
    t[line][i++] = ((hr / 10)+0x30);
    t[line][i++] = ((hr % 10)+0x30);
    t[line][i++] = ':';
    t[line][i++] = ((min / 10)+0x30);
    t[line][i++] = ((min % 10)+0x30);
    t[line][i++] = ':';
    t[line][i++] = ((sec / 10)+0x30);
    t[line][i++] = ((sec % 10)+0x30);
    t[line][i++] = ' ';
 
    while (*m) {
        t[line][i++] = *m++;
    }
 
    t[line][i] = '\0';
 
    prints(2,line,0x06,0x07,&t[line][16]);

    int aa = 16;
    for(aa = 16; t[line][aa]=='\0'; aa++){
       write_serial(t[line][aa],0x3f8);
    }
}