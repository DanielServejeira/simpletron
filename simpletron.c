#include <stdio.h>
#include <locale.h>

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

void boas_vindas() {
    //Boas vindas;
    printf ("\t /-=-=-=-=-=-=-=-=-=-=-=-=-=-\n"
            "\t | Bem-vindo ao Simpletron! | \n"
            "\t =-=-=-=-=-=-=-=-=-=-=-=-=-=/ \n");

    //Instruções
    printf ("\nINSTRUÇÕES\n"
            "1 - Insira uma instrução ou palavra de dados por vez\n"
            "2 - Quando forem inseridos o número da posição e um ponto de interrogação (?)\n"
            "Insira, então, a palavra para aquela posição\n"
            "3 - Insira o valor sentinela -99999 para encerrar a digitação do programa\n");
    printf("\n");
    system("pause");
    system("cls");
}

void limpar_memoria(int *memoria[]) {
    for(int i=0; i<LIMITE; i++) {
        memoria[i] = 0;
    }

    printf("\n\tA memória está limpa e pronta para ser utilizada\n\n");
    system("pause");
    system("cls");
}

void despejo(int *memoria[], int acumulador, int contador_instrucao, int registro_instrucao, int codigo_operacao, int operando){
    printf ("\nREGISTROS:"
            "\nacumulador %d"
            "\ncontadorInstrucao %d"
            "\nregistroInstrucao %d"
            "\ncodigoOperacao %d"
            "\noperando %.2d\n",acumulador,contador_instrucao,registro_instrucao,codigo_operacao,operando);

    printf("\nMEMÓRIA:");
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

void montar_simpletron(int *memoria[]) {
    int contador_instrucao=00, registro_instrucao=+0000, codigo_operacao=00;

    do{
        printf("%.2d ? ", contador_instrucao);
        scanf("%d",&registro_instrucao);

        if(registro_instrucao == -99999) break;

        if(registro_instrucao>=0 && registro_instrucao <=9999) {
            memoria[contador_instrucao] = registro_instrucao;
            codigo_operacao = registro_instrucao/100;

            contador_instrucao++;
        }
        else printf("\n\tErro: instrução fora da faixa (entre 0 e 9999)\n\n");
    }while(contador_instrucao<100);

    if(contador_instrucao == 100) printf("\n\n\tMemória cheia\n");
}

void executar_simpletron(int *memoria[]) {
    int aux, acumulador=+0000, contador_instrucao=00, registro_instrucao=+0000, codigo_operacao=00, operando=00;

    printf("\n\tInício do programa\n\n");

    for(contador_instrucao=0; codigo_operacao != HALT && contador_instrucao < LIMITE; contador_instrucao++) {
        registro_instrucao = memoria[contador_instrucao];
        codigo_operacao = registro_instrucao/100;
        operando = registro_instrucao%100;

        switch(codigo_operacao) {
            case READ: //Lê uma palavra do terminal e a coloca em um local específico da memória
                scanf("%d",&registro_instrucao);

                while(registro_instrucao<-9999 || registro_instrucao>9999) {
                    printf("Insira um número válido (entre -9999 e 9999)\n");
                    scanf("%d",&registro_instrucao);
                }

                memoria[operando] = registro_instrucao;
                break;
            case WRITE: //Escreve no terminal uma palavra de um local específico da memória.
                printf("%d\n", memoria[operando]);
                break;
            case LOAD: //Carrega no acumulador uma palavra de um local específico da memória.
                acumulador = memoria[operando];
                break;
            case STORE: //Armazena em um local específico da memória uma palavra do acumulador.
                memoria[operando] = acumulador;
                break;
            case ADD: //Adiciona uma palavra de um local específico da memória à palavra no acumulador (o resultado fica no acumulador).
                registro_instrucao = memoria[operando];

                aux = registro_instrucao + acumulador;

                if(aux<-9999 || aux>9999) printf("\n\tErro: resultado inválido no acumulador\n");
                else acumulador = aux;

                break;
            case SUBTRACT: //Subtrai da palavra no acumulador, uma palavra em um local específico da memória (o resultado fica no acumulador).
                registro_instrucao = memoria[operando];

                aux = registro_instrucao - acumulador;

                if(aux<-9999 || aux>9999) printf("\n\tErro: resultado inválido no acumulador\n");
                else acumulador = aux;

                break;
            case DIVIDE: //Divide uma palavra em um local específico da memória pela palavra no acumulador (o resultado fica no acumulador).
                registro_instrucao = memoria[operando];

                if(acumulador!=0) aux = registro_instrucao/acumulador;
                else printf("\n\tErro: divisão por zero\n");

                if(aux<-9999 || aux>9999) printf("\n\tErro: resultado inválido no acumulador\n");
                else acumulador = aux;

                break;
            case MULTIPLY: //Multiplica uma palavra em um local específico da memória pela palavra no acumulador (o resultado fica no acumulador).
                registro_instrucao = memoria[operando];

                aux = registro_instrucao * acumulador;

                if(aux<-9999 || aux>9999) printf("\n\tErro: resultado inválido no acumulador\n");
                else acumulador = aux;

                break;
            case BRANCH: //Desvia para um local específico da memória
                contador_instrucao = operando;
                break;
            case BRANCHNEG: //Desvia para um local específico da memória se o acumulador for negativo.
                if(acumulador < 0) contador_instrucao = operando;
                break;
            case BRANCHZERO: //Desvia para um local específico da memória se o acumulador for zero
                if(acumulador == 0) contador_instrucao = operando;
                break;
            case HALT: //Término, i.e., o programa completou sua tarefa
                printf("\n\tTérmino do programa\n\n");
                break;
            default:
                break;
        }
    }

    if(contador_instrucao == LIMITE) printf("\n\tTérmino do programa\n\n");

    despejo(memoria, acumulador, contador_instrucao, registro_instrucao, codigo_operacao, operando);

    system("pause");
    system("cls");
}

void simpletron(int *memoria[]) {
    boas_vindas();
    limpar_memoria(memoria);

    montar_simpletron(memoria);
    executar_simpletron(memoria);
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    int *memoria[LIMITE];

    simpletron(memoria);

    return 0;
}
