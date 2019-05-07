#include <sys/serial.h>
#include <sys/videoprints.h>
#include <sys/teclado.h>
#include <sys/io.h>
//char COM2 = 0x2f8;   /* COM2 */
/* Porta   Endereco I/O    IRQ
COM1    3F8              4
COM2    2F8              3
COM3    3E8              4
COM4    2E8              3 */
int main(void)
{
    int COM = 0x3f8; /* COM1 */
    init_serial(COM);
    init_Video();
    init_teclado();
    desenhaTela();

    char historico[20][78];
    int linha = 2;
    
    char msg[64];
    int indexMSG = 0;

    char reader[100];
    int cont = 0; 
    
    while (1)
    {
        if (serial_received(COM)){
            char c = read_serial(COM);
            printc(2,linha,0x06,0x07,c);
            //  linha ++;
            //printc(2,linha,0x06,0x07,c);
             if(c !='0'){
              reader[cont++] = c;    
            } else if(c == '0') {
              reader[cont++] = c;
              prints(2,linha,0x06,0x07,reader);
              linha ++;
              cont = 0;
            }
        }
        tecla(historico, &linha, msg, &indexMSG);
 }
}


/* if (t != ' '){
                 if (t == '*'){
                    // AQUI VAI O LANCE QUE MONTA O PACOTE e envia menssagem
                    indexMSG = 0;
                    linha++;
                    if(linha > 16){
                        linha = 2;
                    }
                    montahistorico(msg, day(), month(), year(), minute(), second(), hour(), historico, linha);
                    t =' ';
                }else{
                     msg[indexMSG++] = t;
                    msg[indexMSG] = '\0'; 
                }
                t = ' ';             
         }   */