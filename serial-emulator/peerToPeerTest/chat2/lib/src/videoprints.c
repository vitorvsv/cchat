#include <sys/io.h>
#include <sys/videoprints.h>

unsigned short *video;

// Inicializa o video
void init_Video(){
    
    video = (unsigned short *)0xB8000;

}
// Função sem retorno que imprime um char na tela
void printc(int x, int y, int fcolor, int bcolor, int c){
    
    video[x + y * 80] = (fcolor << 8) | (bcolor << 12) | c;

}
// Função sem retorno que imprime uma string na tela
void prints(int x, int y, int fcolor, int bcolor, char *str){

    int inicio = x + y * 80;

    while (*str){

     video[inicio] = (fcolor << 8) | (bcolor << 12) | *str;

     inicio++;
     str++;
    }
}

void limpaTela() {
    int i = 0;
    int j = 0;

    // uma linha tem 80 colunas e 24 linhas
    for (i = 0; i < 80; i++) {
       for (j = 0; j < 24; j++) {
        printc(i, j, 0x00, 0x00, ' ');
        }
    }    
}

void desenhaLinha(int sizeL, int x, int y, int letterColor, int bgColor, char c) {
    int i = 0;

    // uma linha tem 80 colunas e 24 linhas
    for (i = 0; i < sizeL; i++) {
        printc(i, y, letterColor, bgColor, c);
    }
}

void desenhaColuna(int sizeL, int x, int y, int letterColor, int bgColor, char c) {
    int i = 0;

    //tem 80 colunas e 24 linhas
    for (i = 0; i < sizeL; i++) {
        printc(x, i, letterColor, bgColor, c);
    }
}

void desenhaTela(){

    limpaTela();

    desenhaColuna(24, 0, 0, 0x07, 0x00, '-');
    desenhaColuna(24, 79, 0, 0x07, 0x00, '-');
    
    desenhaLinha(80, 0, 0, 0x07, 0x00, '-');
    desenhaLinha(80, 0, 22, 0x07, 0x00, '-');
    desenhaLinha(80, 0, 24, 0x07, 0x00, '-');

    printc(1, 23, 0x07, 0x00, '>');
}





