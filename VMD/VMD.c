
/*  Vai precisar de rótulo, instrução, atributo 1 e atributo 2

    Fazer um switch case, pegar os valores de cada instrução




*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ROT_LEN 4
#define MAX_ATR_LEN 4
#define MAX_STR_LEN 8
#define MAX_NUM_ATR 2
#define MAX_ROTULOS 16
#define MAX_INST 100

int i = 0;

/*struct Programa {
    char prog[MAX_PROG_LEN];
    int posicao;
};*/

/*struct Programa tabelaDePrograma[MAX_ROTULOS];
int contadorDePrograma = 0;
*/
struct Pilha {
    char *M; //Memória da pilha
    int s; //Topo da pilha
    int capacidade;
};

struct Inst {
    char rotulo[4];
    char instrucao[8];
    char atr1[4];
    char atr2[4];
};

void inicializarPilha(struct Pilha *p, int capacidadeInicial) {
    p->M = (char *)malloc(capacidadeInicial * sizeof(int));
    if (p->M == NULL) {
        printf("Erro ao alocar memória para a pilha.\n");
        exit(1);
    }
    p->s = -1;
    p->capacidade = capacidadeInicial;
}

int pilhaVazia(struct Pilha *p) {
    return p->s == -1;
}

int pilhaCheia(struct Pilha *p) {
    return p->s == p->capacidade - 1;
}

void redimensionarPilha(struct Pilha *p) {
    int novaCapacidade = p->capacidade * 2;
    p->M = (char *)realloc(p->M, novaCapacidade * sizeof(int));
    if (p->M == NULL) {
        printf("Erro ao redimensionar a pilha.\n");
        exit(1);
    }
    p->capacidade = novaCapacidade;
}

void empilhar(struct Pilha *p, char *atr) {
    if (pilhaCheia(p)) {
        printf("Pilha cheia! Redimensionando...\n");
        redimensionarPilha(p);
    }
    p->M[++(p->s)] = *atr;
    printf("Elemento %d empilhado.\n", atr);
}

char desempilhar(struct Pilha *p) {
    if (pilhaVazia(p)) {
        printf("Erro: Pilha vazia!\n");
        return -1;
    } else {
        return p->M[(p->s)--];
    }
}

int topo(struct Pilha *p) {
    if (pilhaVazia(p)) {
        printf("Erro: Pilha vazia!\n");
        return -1;
    } else {
        return p->M[p->s];
    }
}

void liberarPilha(struct Pilha *p) {
    free(p->M);
    p->M = NULL;
    p->s = -1;
    p->capacidade = 0;
}

int analisaInst(char *inst) {
    if (strcmp(inst, "NULL") == 0)
        return 0;
    if (strcmp(inst, "LDC") == 0)
        return 1;
    else if (strcmp(inst, "LDV") == 0)
        return 2;
    else if (strcmp(inst, "ADD") == 0)
        return 3;
    else if (strcmp(inst, "SUB") == 0)
        return 4;
    else if (strcmp(inst, "MULT") == 0)
        return 5;
    else if (strcmp(inst, "DIVI") == 0)
        return 6;
    else if (strcmp(inst, "INV") == 0)
        return 7;
    else if (strcmp(inst, "AND") == 0)
        return 8;
    else if (strcmp(inst, "OR") == 0)
        return 9;
    else if (strcmp(inst, "NEG") == 0)
        return 10;
    else if (strcmp(inst, "CME") == 0)
        return 11;
    else if (strcmp(inst, "CMA") == 0)
        return 12;
    else if (strcmp(inst, "CEQ") == 0)
        return 13;
    else if (strcmp(inst, "CDIF") == 0)
        return 14;
    else if (strcmp(inst, "CMEQ") == 0)
        return 15;
    else if (strcmp(inst, "CMAQ") == 0)
        return 16;
    else if (strcmp(inst, "JMP") == 0)
        return 17;
    else if (strcmp(inst, "JMPF") == 0)
        return 18;
    else if (strcmp(inst, "STR") == 0)
        return 19;
    else if (strcmp(inst, "RD") == 0)
        return 20;
    else if (strcmp(inst, "PRN") == 0)
        return 21;
    else if (strcmp(inst, "START") == 0)
        return 22;
    else if (strcmp(inst, "ALLOC") == 0)
        return 23;
    else if (strcmp(inst, "DALLOC") == 0)
        return 24;
    else if (strcmp(inst, "CALL") == 0)
        return 25;
    else if (strcmp(inst, "RETURN") == 0)
        return 26;
}

/*void programaList(const char *prog, int posicao) {
    if (contadorDePrograma < MAX_ROTULOS) {
        strcpy(tabelaDePrograma[contadorDePrograma].prog, prog);
        tabelaDePrograma[contadorDePrograma].posicao = posicao;
        contadorDePrograma++;
    } else {
        printf("Erro: número máximo de rótulos atingido.\n");
    }
}*/

int encontrarPosicaoRotulo(char *list, FILE *file) {
    /*for (int i = 0; i < contadorDePrograma; i++) {
        if (strcmp(tabelaDePrograma[i].prog, prog) == 0) {
            return tabelaDePrograma[i].posicao;
        }
    }
    printf("Erro: rótulo %s não encontrado.\n", prog);
    return -1;  // Retorna -1 se o rótulo não for encontrado
*/
    char rot[MAX_STR_LEN];
    int posicao = 0;
    while (fscanf(file, "%s", rot) == 1) {
        for (int j = 0; j < MAX_STR_LEN; j++){
            if (strcmp(rot, list) == 1) {
                return posicao;
            }
        }
        posicao++;
    }
    return -1;
}

void lerInstrucoes(FILE *file, struct Inst lista[], int max_inst, int* count) {
    char ler[50];

    // Loop para ler cada linha do arquivo
    while (fgets(ler, sizeof(ler), file) && *count < max_inst) {
        // Inicializa a estrutura com strings vazias
        strcpy(lista[*count].rotulo, "");
        strcpy(lista[*count].instrucao, "");
        strcpy(lista[*count].atr1, "");
        strcpy(lista[*count].atr2, "");

        // Analisa e preenche os campos da estrutura
        sscanf(ler, "%3s %7s %3s %3s",
               lista[*count].rotulo,
               lista[*count].instrucao,
               lista[*count].atr1,
               lista[*count].atr2);

        // Imprime as informações lidas (opcional)
        printf("%3s %7s %3s %3s\n",
               lista[*count].rotulo,
               lista[*count].instrucao,
               lista[*count].atr1,
               lista[*count].atr2);

        count++;
    }
}

void resolveInst(struct Pilha *p, FILE *file, int posicao){
    struct Inst lista[MAX_INST];
    int count = 0;
    lerInstrucoes(file, lista, MAX_INST, &count);
    switch (analisaInst(lista[count].instrucao)) {
        case 0: // NULL
            // Nada
            break;
        case 1: // LDC k (Carregar constante)
            empilhar(p, lista[count].atr1);
            break;

        case 2: // LDV n (Carregar variavel)
            empilhar(p, lista[count].atr1);
            break;

        case 3: // ADD (Somar)
            *(int*)lista[count].atr2 = desempilhar(p);
            *(int*)lista[count].atr1 = desempilhar(p);
            int resultadoSoma = *(int*)lista[count].atr1 + *(int*)lista[count].atr2;
            char* resultadoCharSoma = (char*)&resultadoSoma;
            empilhar(p, resultadoCharSoma);
            break;

        case 4: // SUB (Subtrair)
            *(int*)lista[count].atr2 = desempilhar(p);
            *(int*)lista[count].atr1 = desempilhar(p);
            int resultadoSub = *(int*)lista[count].atr1 - *(int*)lista[count].atr2;
            char* resultadoCharSub = (char*)&resultadoSub;
            empilhar(p, resultadoCharSub);
            break;

        case 5: // MULT (Multiplicar)
            *(int*)lista[count].atr2 = desempilhar(p);
            *(int*)lista[count].atr1 = desempilhar(p);
            int resultadoMul = *(int*)lista[count].atr1 * *(int*)lista[count].atr2;
            char* resultadoCharMul = (char*)&resultadoMul;
            empilhar(p, resultadoCharMul);
            break;

        case 6: // DIVI (Dividir)
            if (*(int*)lista[count].atr2 != 0){
                *(int*)lista[count].atr2 = desempilhar(p);
                *(int*)lista[count].atr1 = desempilhar(p);
                int resultadoDiv = *(int*)lista[count].atr1 / *(int*)lista[count].atr2;
                char* resultadoCharDiv = (char*)&resultadoDiv;
                empilhar(p, resultadoCharDiv);
            }
            else
                printf("Erro: Divisão por zero!\n");
            break;

        case 7: // INV (Inverter sinal)
            p->M[p->s] = -p->M[p->s];
            break;

        case 8: // AND (Conjunção)
            *lista[count].atr2 = desempilhar(p);
            *lista[count].atr1 = desempilhar(p);
            int ResultadoAND = (*(int*)lista[count].atr1 == 1 && *(int*)lista[count].atr2 == 1) ? 1 : 0;
            char* ResultadoCharAND = (char*)&ResultadoAND;
            empilhar(p, ResultadoCharAND);
            break;

        case 9: // OR (Disjunção)
            *lista[count].atr2 = desempilhar(p);
            *lista[count].atr1 = desempilhar(p);
            int ResultadoOR = (*(int*)lista[count].atr1 || *(int*)lista[count].atr2) ? 1 : 0;
            char* ResultadoCharOR = (char*)&ResultadoOR;
            empilhar(p, ResultadoCharOR);
            break;

        case 10: // NEG (Negação)
            p->M[p->s] = 1 - p->M[p->s];
            break;

        case 11: // CME (Comparar menor)
            *lista[count].atr2 = desempilhar(p);
            *lista[count].atr1 = desempilhar(p);
            int ResultadoCME = (*(int*)lista[count].atr1 == *(int*)lista[count].atr2) ? 1 : 0;
            char* ResultadoCharCME = (char*)&ResultadoCME;
            empilhar(p, ResultadoCharCME);
            break;

        case 12: // CMA (Comparar maior)
            *lista[count].atr2 = desempilhar(p);
            *lista[count].atr1 = desempilhar(p);
            int ResultadoCMA = (*(int*)lista[count].atr1 > *(int*)lista[count].atr2) ? 1 : 0;
            char* ResultadoCharCMA = (char*)&ResultadoCMA;
            empilhar(p, ResultadoCharCMA);
            break;

        case 13: // CEQ (Comparar igual)
            *lista[count].atr2 = desempilhar(p);
            *lista[count].atr1 = desempilhar(p);
            int ResultadoCEQ = (*(int*)lista[count].atr1 == *(int*)lista[count].atr2) ? 1 : 0;
            char* ResultadoCharCEQ = (char*)&ResultadoCEQ;
            empilhar(p, ResultadoCharCEQ);
            break;

        case 14: // CDIF (Comparar desigual)
            *lista[count].atr2 = desempilhar(p);
            *lista[count].atr1 = desempilhar(p);
            int ResultadoCDIF = (*(int*)lista[count].atr1 != *(int*)lista[count].atr2) ? 1 : 0;
            char* ResultadoCharCDIF = (char*)&ResultadoCDIF;
            empilhar(p, ResultadoCharCDIF);
            break;

        case 15: // CMEQ (Comparar menor ou igual)
            *lista[count].atr2 = desempilhar(p);
            *lista[count].atr1 = desempilhar(p);
            int ResultadoCMEQ = (*(int*)lista[count].atr1 <= *(int*)lista[count].atr2) ? 1 : 0;
            char* ResultadoCharCMEQ = (char*)&ResultadoCMEQ;
            empilhar(p, ResultadoCharCMEQ);
            break;

        case 16: // CMAQ (Comparar maior ou igual)
            *lista[count].atr2 = desempilhar(p);
            *lista[count].atr1 = desempilhar(p);
            int ResultadoCMAQ = (*(int*)lista[count].atr1 >= *(int*)lista[count].atr2) ? 1 : 0;
            char* ResultadoCharCMAQ = (char*)&ResultadoCMAQ;
            empilhar(p, ResultadoCharCMAQ);
            break;
        
        case 17: // JMP p (Desviar sempre)
            for (int i = 0; i < MAX_INST; i++) {
                // Verifique se o rótulo da linha atual é igual a lista[count].atr1
                if (strcmp(lista[i].rotulo, lista[count].atr1) == 0) {
                    // Se for igual, você pode executar a ação desejada
                    count = i;
                    // Faça o que for necessário quando o rótulo for encontrado
                }
            };
            break;

        case 18: // JMPF p (Desviar se falso)
            for (int i = 0; i < MAX_INST; i++) {
                // Verifique se o rótulo da linha atual é igual a lista[count].atr1
                if (strcmp(lista[i].rotulo, lista[count].atr1) == 0) {
                    // Se for igual, você pode executar a ação desejada
                    count = i;
                    // Faça o que for necessário quando o rótulo for encontrado
                }
            };
            break;

        case 19: // STR n (Armazenar valor)
            p->M[atoi(lista[count].atr1)] = p->M[p->s]; 
            p->s -= 1;
            break;
 
        case 20: // RD (Leitura)
            printf("Digite o próximo valor de entrada: ");
            char* entrada;
            scanf("%d", entrada);
            empilhar(p, entrada);
            break;

        case 21: // PRN (Impressão)
            printf("%d\n", desempilhar(p));
            break;
/*
        case 23: // ALLOC m (Alocar memória)
            for (int k = 0; k < (int)lista[count].atr2; k++){
            p->s = p->s + 1;                // Incrementa o topo da pilha
            p->M[p->s] = p->M[lista[count].atr1 + k];       // Copia o valor de M[m+k] para o topo da pilha
            }
            break;

        case 24: // DALLOC m (Liberar memória)
            for (int k = lista[count].atr2 - 1; k >= 0; k--) {
                p->M[lista[count].atr1 + k] = p->M[p->s];       // Copia o valor do topo da pilha para M[m+k]
                p->s = p->s - 1;                // Decrementa o topo da pilha
            }
            break;
*/
        case 25: // CALL p (Chamar procedimento ou função)
            for (int i = 0; i < MAX_INST; i++) {
                // Verifique se o rótulo da linha atual é igual a lista[count].atr1
                if (strcmp(lista[i].rotulo, lista[count].atr1) == 0) {
                    // Se for igual, você pode executar a ação desejada
                    count = i;
                    // Faça o que for necessário quando o rótulo for encontrado
                }
            break;

        case 26: // Return
            i = desempilhar(p);
        case 27: // NULL (Nada)
            // Não faz nada
            break;


        default:
            printf("Instrução inválida: \n");
            break;
        }
    }
}

// Início da MVD
void MVD(struct Pilha *p, FILE *file) {
    char lerString[50];
    struct Inst lista[MAX_INST];
    int posicao = 0;
    int count = 0;
    lerInstrucoes(file, lista, MAX_INST, &count);
    char *result = lista[count].instrucao;
    if (result != "START") {
        printf("Erro: A primeira instrução deve ser 'START'.\n");
        return;
    }
    while ((result = fgets(lerString, sizeof(lerString), file)) != "HLT") {
            resolveInst(p, file, posicao);
    }
    printf("\nHLT - FIM DO PROGRAMA");
}

int main() {
    struct Pilha p;
    inicializarPilha(&p, 8);
    FILE *file = fopen("teste2.txt", "r");
    MVD(&p, file);
    fclose(file);
    liberarPilha(&p);
    return 0;
}
