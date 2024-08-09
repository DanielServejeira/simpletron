#include<stdio.h>
#include<locale.h>

#define READ 10
#define WRITE 11
#define LOAD 20
#define STORE 21
#define ADD 30
#define SUBTRACT 31
#define DIVIDE 32
#define MULTIPLY 33
#define BRANCH 40
#define BRANCHNEG 41
#define BRANCHZERO 42
#define HALT 43
#define LIMITE 100

void boasVindas() {
    //Boas vindas;
    printf ("\t /-=-=-=-=-=-=-=-=-=-=-=-=-=-\n"
            "\t | Bem-vindo ao Simpletron! | \n"
            "\t =-=-=-=-=-=-=-=-=-=-=-=-=-=/ \n");

    //Instru��es
    printf ("\nINSTRU��ES\n"
            "1 - Insira uma instru��o ou palavra de dados por vez\n"
            "2 - Quando forem inseridos o n�mero da posi��o e um ponto de interroga��o (?)\n"
            "Insira, ent�o, a palavra para aquela posi��o\n"
            "3 - Insira o valor sentinela -99999 para encerrar a digita��o do programa\n");
    printf("\n");
    system("pause");
    system("cls");
}

void limparMemoria(int *memoria[]) {
    for(int i=0; i<LIMITE; i++) {
        memoria[i] = 0;
    }

    printf("\n\tA mem�ria est� limpa e pronta para ser utilizada\n\n");
    system("pause");
    system("cls");
}

void despejo(int *memoria[], int acumulador, int contadorInstrucao, int registroInstrucao, int codigoOperacao, int operando){
    printf ("\nREGISTROS:"
            "\nacumulador %d"
            "\ncontadorInstrucao %d"
            "\nregistroInstrucao %d"
            "\ncodigoOperacao %d"
            "\noperando %.2d\n",acumulador,contadorInstrucao,registroInstrucao,codigoOperacao,operando);

    printf("\nMEM�RIA:");
    printf("\n\t    0\t    1\t    2\t    3\t    4\t    5\t    6\t    7\t    8\t    9");

    for(int i=0; i<10; i++){
        printf("\n%.2d\t", i*10);
        for(int j=i*10; j<i*10+10; j++){
            if(memoria[j]<0) printf("%.4d\t", memoria[j]);
            else printf("+%.4d\t", memoria[j]);
        }
    }
    printf("\n\n");
}

void montarSimpletron(int *memoria[]) {
    int contadorInstrucao=00, registroInstrucao=+0000, codigoOperacao=00;

    do{
        printf("%.2d ? ", contadorInstrucao);
        scanf("%d",&registroInstrucao);

        if(registroInstrucao == -99999) break;

        if(registroInstrucao>=0 && registroInstrucao <=9999) {
            memoria[contadorInstrucao] = registroInstrucao;
            codigoOperacao = registroInstrucao/100;

            contadorInstrucao++;
        }
        else printf("\n\tErro: instru��o fora da faixa (entre 0 e 9999)\n\n");
    }while(contadorInstrucao<100);

    if(contadorInstrucao == 100) printf("\n\n\tMem�ria cheia\n");
}

void executarSimpletron(int *memoria[]) {
    int aux, acumulador=+0000, contadorInstrucao=00, registroInstrucao=+0000, codigoOperacao=00, operando=00;

    printf("\n\tIn�cio do programa\n\n");

    for(contadorInstrucao=0; codigoOperacao != HALT && contadorInstrucao < LIMITE; contadorInstrucao++) {
        registroInstrucao = memoria[contadorInstrucao];
        codigoOperacao = registroInstrucao/100;
        operando = registroInstrucao%100;

        switch(codigoOperacao) {
            case READ: //L� uma palavra do terminal e a coloca em um local espec�fico da mem�ria
                scanf("%d",&registroInstrucao);

                while(registroInstrucao<-9999 || registroInstrucao>9999) {
                    printf("Insira um n�mero v�lido (entre -9999 e 9999)\n");
                    scanf("%d",&registroInstrucao);
                }

                memoria[operando] = registroInstrucao;
                break;
            case WRITE: //Escreve no terminal uma palavra de um local espec�fico da mem�ria.
                printf("%d\n", memoria[operando]);
                break;
            case LOAD: //Carrega no acumulador uma palavra de um local espec�fico da mem�ria.
                acumulador = memoria[operando];
                break;
            case STORE: //Armazena em um local espec�fico da mem�ria uma palavra do acumulador.
                memoria[operando] = acumulador;
                break;
            case ADD: //Adiciona uma palavra de um local espec�fico da mem�ria � palavra no acumulador (o resultado fica no acumulador).
                registroInstrucao = memoria[operando];

                aux = registroInstrucao + acumulador;

                if(aux<-9999 || aux>9999) printf("\n\tErro: resultado inv�lido no acumulador\n");
                else acumulador = aux;

                break;
            case SUBTRACT: //Subtrai da palavra no acumulador, uma palavra em um local espec�fico da mem�ria (o resultado fica no acumulador).
                registroInstrucao = memoria[operando];

                aux = registroInstrucao - acumulador;

                if(aux<-9999 || aux>9999) printf("\n\tErro: resultado inv�lido no acumulador\n");
                else acumulador = aux;

                break;
            case DIVIDE: //Divide uma palavra em um local espec�fico da mem�ria pela palavra no acumulador (o resultado fica no acumulador).
                registroInstrucao = memoria[operando];

                if(acumulador!=0) aux = registroInstrucao/acumulador;
                else printf("\n\tErro: divis�o por zero\n");

                if(aux<-9999 || aux>9999) printf("\n\tErro: resultado inv�lido no acumulador\n");
                else acumulador = aux;

                break;
            case MULTIPLY: //Multiplica uma palavra em um local espec�fico da mem�ria pela palavra no acumulador (o resultado fica no acumulador).
                registroInstrucao = memoria[operando];

                aux = registroInstrucao * acumulador;

                if(aux<-9999 || aux>9999) printf("\n\tErro: resultado inv�lido no acumulador\n");
                else acumulador = aux;

                break;
            case BRANCH: //Desvia para um local espec�fico da mem�ria
                contadorInstrucao = operando;
                break;
            case BRANCHNEG: //Desvia para um local espec�fico da mem�ria se o acumulador for negativo.
                if(acumulador < 0) contadorInstrucao = operando;
                break;
            case BRANCHZERO: //Desvia para um local espec�fico da mem�ria se o acumulador for zero
                if(acumulador == 0) contadorInstrucao = operando;
                break;
            case HALT: //T�rmino, i.e., o programa completou sua tarefa
                printf("\n\tT�rmino do programa\n\n");
                break;
            default:
                break;
        }
    }

    if(contadorInstrucao == LIMITE) printf("\n\tT�rmino do programa\n\n");

    despejo(memoria, acumulador, contadorInstrucao, registroInstrucao, codigoOperacao, operando);

    system("pause");
    system("cls");
}

void simpletron(int *memoria[]) {
    boasVindas();
    limparMemoria(memoria);

    montarSimpletron(memoria);
    executarSimpletron(memoria);
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    int *memoria[LIMITE];

    simpletron(memoria);

    return 0;
}
