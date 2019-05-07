#ifndef SERIAL_H
#define SERIAL_H

extern void init_serial(int PORT);
extern int serial_received(int PORT);
extern char read_serial(int PORT);
extern int is_transmit_empty(int PORT);
extern void write_serial(char a, int PORT);

#endif