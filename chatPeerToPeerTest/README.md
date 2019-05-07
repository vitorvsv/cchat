# Configurações do Serial

Para fazer esse teste do serial será necessário o QEMU (emulador de hardware)
E do minicom (leitor visual de Serial)
Socat -> Programa virtualizador de portas seriais

Gere duas portas serial utilizando o Socat
socat -d -d pty,raw,echo=0 pty,raw,echo=0

Edite o Makefile disponibilizado pelo professor editando a parte do run

run: $(PROJECT).elf
        $(QEMU) -soundhw pcspk -serial /dev/pts/4 -kernel $<

"-serial /dev/pts/4" Na parte do /dev/pts/4 passe o primeiro arquivo gerado no output do Socat

Execute:
make
make run

Depois execute o minicom para ler a segunda porta gerada pelo Socat

minicom -D /dev/pts/0 -b 38400 -8

Em "/dev/pts/0" coloque o segundo arquivo gerado no output do Socat
Em "38400" defina o boud rate, mesmo que usara no .c para leitura e gravação na porta

Usando seu código de leitura/escrita na serial, escreva na porta serial e veja o resultado no minicom.

Tradução do que esta sendo feito. O minicom gera duas portas seriais virtuais. Por exemplo
/dev/pts/4 e /dev/pts/0, editando o makefile utilizamos o qemu para mapear para um dispositivo a serial
que no nosso caso seria /dev/pts/4. Utilizamos o minicom para ler a serial /dev/pts/0 usando o boud rate 38400
Ou seja, cada vez que escrevemos na porta /dev/pts/4 podemos ler o valor na /dev/pts/0 pois é gerado um tunel entre
essas duas seriais.
