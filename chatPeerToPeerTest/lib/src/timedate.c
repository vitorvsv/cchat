#include <sys/timedate.h>

int year() {
    int year = 0;
    outb(0x70, 0x09);
    char v = inb(0x71);
    char a = (v & 0x0F); //+ 0x30;
    char a2 = ((v & 0xF0) >> 4) * 10; // + 0x30;
    year = a + a2; //(a2 << 8) | a;
    return year;
}
 
int month() {
    int month = 0;
    outb(0x70, 0x08);
    char v = inb(0x71);
    char m = (v & 0x0F); // + 0x30;
    char m2 = ((v & 0xF0) >> 4) *10; //+ 0x30;
    month = m + m2; //(m2 << 8) | m;
    return month;
}
 
int day() {
    int day = 0;
    outb(0x70, 0x07);
    char v = inb(0x71);
    char d = (v & 0x0F);
    char d2 = ((v & 0xF0) >> 4) * 10;
    day = d + d2;
    return day;
}
 
int hour() {
    int hour = 0;
    outb(0x70, 0x04);
    char v = inb(0x71);
    char hr = (v & 0x0F);
    char hr2 = ((v & 0xF0) >> 4) * 10;
    hour = hr + hr2;
    return hour;
}
 
int minute() {
    int minute = 0;
    outb(0x70, 0x02);
    char v = inb(0x71);
    char min = (v & 0x0F); //+ 0x30;
    char min2 = ((v & 0xF0) >> 4) * 10; //+ 0x30;
    minute = min + min2; //(min2 << 8) | min;
    return minute;
}
 
int second() {
    int second = 0;
    outb(0x70, 0x00);
    char v = inb(0x71);
    char seg = (v & 0x0F);
    char seg2 = ((v & 0xF0) >> 4) * 10;
    second = seg + seg2;
    return second;
}