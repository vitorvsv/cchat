#ifndef TECLADO_H
#define TECLADO_H

extern void print(int x);
extern void init_teclado(void);
extern char map_key(int scancode);
extern char tecla(char** historico,int *linha,char *msg,int *indexMSG);
 
#endif
