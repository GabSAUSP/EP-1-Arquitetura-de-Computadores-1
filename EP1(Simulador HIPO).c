/* Gabriel Silva Alvarenga */

/* O processador executa instruções a partir do endereço zero.
 * as instruções DDF e DFF não precisam ser codificadas.
 * as instruções de deslocamento preservam o sinal.
 * a instrução PAR termina o simulador. */
 
#include <stdio.h>
#include <stdlib.h>


#define MSIZE 10000

int M[MSIZE];  // representa a memória do HIPO.

void loadM (char *imgFileName) {
	FILE *fp;
	fp=fopen (imgFileName, "rt");
	int i=0;
	while (!feof(fp)) {
		printf ("lendo linha %d ", i);
		/* quem escrever o conteúdo da memória deve ter o cuidado de fazê-lo 
		 * conforme a especificação. Esta função não checa. */
		/* podem acontecer coisas inesperadas caso falte ou sobre \n no arquivo. 
		 * */
		fscanf (fp, "%d\n", &(M[i]));
		printf ("conteúdo: %d ", M[i]);
		++i;
	}
	fclose(fp);
}

void dumpM () {
	for (int i=0;i<MSIZE;i++) {
		printf ("(%d,%d)\t", i, M[i]);
	}
}

int acc;
int pc;  // ou ai
int mbr; // talvez não seja necessário.


void executa() {
    acc = 0;
    pc = 0;
    
    while (1) {

        int instr = M[pc] / 100; // obtém o valor da instrução (dois primeiros dígitos)
        int EE = M[pc] % 100;   // obtém o valor do endereço (dois últimos dígitos)

        switch (instr) {
        case 11: // CEA
            acc = M[EE];
            break;
        case 12: // CAE
            M[EE] = acc;
            break;
        case 21: // SOM
            acc += M[EE];
            break;
        case 22: // SUB
            acc -= M[EE];
            break;
        case 23: // MUL
            acc *= M[EE];
            break;
        case 24: // DIV
            acc = acc / M[EE];
            break;
        case 25: // MOD
            acc = acc % M[EE];
            break;
        case 31: // LER
            scanf("%d", &M[EE]);
            break;
        case 41: // IMP
            printf("%d\n", M[EE]);
            break;
        case 50: // NOP
            break;
        case 51: // DES
            pc = EE-2;
            break;
        case 52:  // DPO
            if (acc > 0) {
                pc = EE - 1;
            }
            break;
        case 53:  // DPZ
            if (acc >= 0) {
                pc = EE - 1;
            }
            break;
        case 54:  // DNE
            if (acc < 0) {
                pc = EE - 1;
            }
            break;
        case 55:  // DNZ
            if (acc <= 0) {
                pc = EE - 1;
            }
            break;
        case 56:  // DDZ
            if (acc != 0) {
                pc = EE - 1;
            }
            break;
        case 57:  // DZZ
            if (acc == 0) {
                pc = EE - 1;
            }
            break;
        case 61: // ADE
            acc = acc % 100 * 10;
            break;
        case 62: // ADD
            acc = acc / 10;
            break;
        case 70: // PAR
            return;
            default:
                printf("Instrucao invalida\n");
                return;
        }

        pc++;  
        
        
    }
}

int main (int argc, char *argv[]) {
    puts ("Hello");
    if (argc>1) {
        /* Um computador frequentemente tem um programa que carrega um 
		 * executável na memória. Esse programa é mais complicado que o tipo
		 * de programa que é suficiente para oferecer um entendimento básico
		 * dos conceitos que quero explorar na disciplina. Por isso, a carga de
		 * um programa na memória, neste simulador, é algo feito "por fora"
		 * da simulação.
		 * */
        loadM(argv[1]);
        dumpM();  

        
        

        executa();
    }
}
