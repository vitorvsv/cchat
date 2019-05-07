#include <sys/serial.h>
#include <sys/io.h>

void init_serial(int PORT) {
   outb(PORT + 1, 0x00);    // Disable all interrupts
   outb(PORT + 3, 0x80);    // Enable DLAB (set baud rate divisor)
   outb(PORT + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
   outb(PORT + 1, 0x00);    //                  (hi byte)
   outb(PORT + 3, 0x03);    // 8 bits, no parity, one stop bit
   outb(PORT + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
   outb(PORT + 4, 0x0B);    // IRQs enabled, RTS/DSR set
}

int serial_received(int PORT) {
   return inb(PORT + 5) & 1;
}

char read_serial(int PORT) {
   //while (serial_received() == 0);

   if (serial_received(PORT) == 0) {
      return 0;
   }

   return inb(PORT);
}

int is_transmit_empty(int PORT) {
   return inb(PORT + 5) & 0x20;
}

void write_serial(char a, int PORT) {
   //while (is_transmit_empty(PORT) == 0);

   outb(PORT,a);
}