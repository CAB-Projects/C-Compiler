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


typedef struct node_lista_char node_lista_char;
typedef struct node_lista_char{
    char* ch;
    node_lista_char* anterior;
}node_lista_char;

struct Inst {
    char rotulo[5];
    char instrucao[9];
    char atr1[5];
    char atr2[6];
};

void inicializarPilha(struct node_lista_char *p) {
    p->anterior = 0;
}

void empilhar(node_lista_char** p, char *atr){
    node_lista_char *temp = (node_lista_char*)malloc(sizeof(node_lista_char));
    temp->anterior = *p;
    *p = temp;
    (*p)->ch = atr;
}

char* desempilhar(struct node_lista_char **p) {
    if (*p == NULL) {
        printf("Erro: Pilha vazia!\n");
        return NULL;
    } else {
        char* retorno = (*p)->ch;
        node_lista_char *temp = (node_lista_char*)malloc(sizeof(node_lista_char));
        (*p) = (*p)->anterior;
        free(temp);
        return retorno;
    }
}

void liberarPilha(struct node_lista_char *p) {
    p->ch = NULL;  // PROBLEMA
    p->anterior = 0;
}

int analisaInst(struct Inst *lista) {
    if (strcmp(lista->instrucao, "NULL") == 0)
        return 0;
    if (strcmp(lista->instrucao, "LDC     ") == 0)
        return 1;
    else if (strcmp(lista->instrucao, "LDV     ") == 0)
        return 2;
    else if (strcmp(lista->instrucao, "ADD     ") == 0)
        return 3;
    else if (strcmp(lista->instrucao, "SUB     ") == 0)
        return 4;
    else if (strcmp(lista->instrucao, "MULT    ") == 0)
        return 5;
    else if (strcmp(lista->instrucao, "DIVI    ") == 0)
        return 6;
    else if (strcmp(lista->instrucao, "INV     ") == 0)
        return 7;
    else if (strcmp(lista->instrucao, "AND     ") == 0)
        return 8;
    else if (strcmp(lista->instrucao, "OR      ") == 0)
        return 9;
    else if (strcmp(lista->instrucao, "NEG     ") == 0)
        return 10;
    else if (strcmp(lista->instrucao, "CME     ") == 0)
        return 11;
    else if (strcmp(lista->instrucao, "CMA     ") == 0)
        return 12;
    else if (strcmp(lista->instrucao, "CEQ     ") == 0)
        return 13;
    else if (strcmp(lista->instrucao, "CDIF    ") == 0)
        return 14;
    else if (strcmp(lista->instrucao, "CMEQ    ") == 0)
        return 15;
    else if (strcmp(lista->instrucao, "CMAQ    ") == 0)
        return 16;
    else if (strcmp(lista->instrucao, "JMP     ") == 0)
        return 17;
    else if (strcmp(lista->instrucao, "JMPF    ") == 0)
        return 18;
    else if (strcmp(lista->instrucao, "STR     ") == 0)
        return 19;
    else if (strcmp(lista->instrucao, "RD      ") == 0)
        return 20;
    else if (strcmp(lista->instrucao, "PRN     ") == 0)
        return 21;
    else if (strcmp(lista->instrucao, "START   ") == 0)
        return 22;
    else if (strcmp(lista->instrucao, "ALLOC   ") == 0)
        return 23;
    else if (strcmp(lista->instrucao, "DALLOC  ") == 0)
        return 24;
    else if (strcmp(lista->instrucao, "CALL    ") == 0)
        return 25;
    else if (strcmp(lista->instrucao, "RETURN  ") == 0)
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

void lerInstrucoes(FILE *file, struct Inst lista[MAX_INST]) {
    int count = -1;
    while (strcmp(lista[count].instrucao, "HLT     ") != 0){
        (count)++;
            // Inicializa a estrutura com strings vazias
        /*strcpy(lista[*count].rotulo, "");
        strcpy(lista[*count].instrucao, "");
        strcpy(lista[*count].atr1, "");
        strcpy(lista[*count].atr2, "");*/

        // Analisa e preenche os campos da estrutura
        fgets(lista[count].rotulo, sizeof(lista[count].rotulo), file);
        fgets(lista[count].instrucao, sizeof(lista[count].instrucao), file);
        fgets(lista[count].atr1, sizeof(lista[count].atr1), file);
        fgets(lista[count].atr2, sizeof(lista[count].atr2), file);
 
        // Imprime as informações lidas (opcional)
        printf("%4s %8s %4s %4s\n",
               lista[count].rotulo,
               lista[count].instrucao,
               lista[count].atr1,
               lista[count].atr2);
    }
}

void resolveInst(struct node_lista_char *p, FILE *file, int* count, struct Inst lista[MAX_INST]){
    printf("%8s", lista[*count].instrucao);
    switch (analisaInst(&lista[*count])) {
        case 0: // NULL
            // Nada
            break;
        case 1: // LDC k (Carregar constante)
            empilhar(&p, lista[*count].atr1);
            break;

        case 2: // LDV n (Carregar variavel)
            empilhar(&p, lista[*count].atr1);
            break;

        case 3: // ADD (Somar)
            *lista[*count].atr2 = *desempilhar(&p);
            *lista[*count].atr1 = *desempilhar(&p);
            int resultadoSoma = *(int*)lista[*count].atr1 + *(int*)lista[*count].atr2;
            char* resultadoCharSoma = (char*)&resultadoSoma;
            empilhar(&p, resultadoCharSoma);
            break;

        case 4: // SUB (Subtrair)
            *lista[*count].atr2 = *desempilhar(&p);
            *lista[*count].atr1 = *desempilhar(&p);
            int resultadoSub = *(int*)lista[*count].atr1 - *(int*)lista[*count].atr2;
            char* resultadoCharSub = (char*)&resultadoSub;
            empilhar(&p, resultadoCharSub);
            break;

        case 5: // MULT (Multiplicar)
            *lista[*count].atr2 = *desempilhar(&p);
            *lista[*count].atr1 = *desempilhar(&p);
            int resultadoMul = *(int*)lista[*count].atr1 * *(int*)lista[*count].atr2;
            char* resultadoCharMul = (char*)&resultadoMul;
            empilhar(&p, resultadoCharMul);
            break;

        case 6: // DIVI (Dividir)
            if (*(int*)lista[*count].atr2 != 0){
                *lista[*count].atr2 = *desempilhar(&p);
                *lista[*count].atr1 = *desempilhar(&p);
                int resultadoDiv = *(int*)lista[*count].atr1 / *(int*)lista[*count].atr2;
                char* resultadoCharDiv = (char*)&resultadoDiv;
                empilhar(&p, resultadoCharDiv);
            }
            else
                printf("Erro: Divisão por zero!\n");
            break;

        case 7: // INV (Inverter sinal)
            p->ch = (char*)(- *(int*)p->ch);
            break;

        case 8: // AND (Conjunção)
            *lista[*count].atr2 = *desempilhar(&p);
            *lista[*count].atr1 = *desempilhar(&p);
            int ResultadoAND = (*(int*)lista[*count].atr1 == 1 && *(int*)lista[*count].atr2 == 1) ? 1 : 0;
            char* ResultadoCharAND = (char*)&ResultadoAND;
            empilhar(&p, ResultadoCharAND);
            break;

        case 9: // OR (Disjunção)
            *lista[*count].atr2 = *desempilhar(&p);
            *lista[*count].atr1 = *desempilhar(&p);
            int ResultadoOR = (*(int*)lista[*count].atr1 || *(int*)lista[*count].atr2) ? 1 : 0;
            char* ResultadoCharOR = (char*)&ResultadoOR;
            empilhar(&p, ResultadoCharOR);
            break;

        case 10: // NEG (Negação)
            p->ch = (char*)(1 - *(int*)p->ch);
            break;

        case 11: // CME (Comparar menor)
            *lista[*count].atr2 = *desempilhar(&p);
            *lista[*count].atr1 = *desempilhar(&p);
            int ResultadoCME = (*(int*)lista[*count].atr1 == *(int*)lista[*count].atr2) ? 1 : 0;
            char* ResultadoCharCME = (char*)&ResultadoCME;
            empilhar(&p, ResultadoCharCME);
            break;

        case 12: // CMA (Comparar maior)
            *lista[*count].atr2 = *desempilhar(&p);
            *lista[*count].atr1 = *desempilhar(&p);
            int ResultadoCMA = (*(int*)lista[*count].atr1 > *(int*)lista[*count].atr2) ? 1 : 0;
            char* ResultadoCharCMA = (char*)&ResultadoCMA;
            empilhar(&p, ResultadoCharCMA);
            break;

        case 13: // CEQ (Comparar igual)
            *lista[*count].atr2 = *desempilhar(&p);
            *lista[*count].atr1 = *desempilhar(&p);
            int ResultadoCEQ = (*(int*)lista[*count].atr1 == *(int*)lista[*count].atr2) ? 1 : 0;
            char* ResultadoCharCEQ = (char*)&ResultadoCEQ;
            empilhar(&p, ResultadoCharCEQ);
            break;

        case 14: // CDIF (Comparar desigual)
            *lista[*count].atr2 = *desempilhar(&p);
            *lista[*count].atr1 = *desempilhar(&p);
            int ResultadoCDIF = (*(int*)lista[*count].atr1 != *(int*)lista[*count].atr2) ? 1 : 0;
            char* ResultadoCharCDIF = (char*)&ResultadoCDIF;
            empilhar(&p, ResultadoCharCDIF);
            break;

        case 15: // CMEQ (Comparar menor ou igual)
            *lista[*count].atr2 = *desempilhar(&p);
            *lista[*count].atr1 = *desempilhar(&p);
            int ResultadoCMEQ = (*(int*)lista[*count].atr1 <= *(int*)lista[*count].atr2) ? 1 : 0;
            char* ResultadoCharCMEQ = (char*)&ResultadoCMEQ;
            empilhar(&p, ResultadoCharCMEQ);
            break;

        case 16: // CMAQ (Comparar maior ou igual)
            *lista[*count].atr2 = *desempilhar(&p);
            *lista[*count].atr1 = *desempilhar(&p);
            int ResultadoCMAQ = (*(int*)lista[*count].atr1 >= *(int*)lista[*count].atr2) ? 1 : 0;
            char* ResultadoCharCMAQ = (char*)&ResultadoCMAQ;
            empilhar(&p, ResultadoCharCMAQ);
            break;
        
        case 17: // JMP p (Desviar sempre)
            for (int i = 0; i < MAX_INST; i++) {
                // Verifique se o rótulo da linha atual é igual a lista[count].atr1
                if (strcmp(lista[i].rotulo, lista[*count].atr1) == 0) {
                    // Se for igual, você pode executar a ação desejada
                    *count = i;
                    // Faça o que for necessário quando o rótulo for encontrado
                }
            };
            break;

        case 18: // JMPF p (Desviar se falso)
            if(*desempilhar(&p) == -1){
                for (int i = 0; i < MAX_INST; i++) {
                    // Verifique se o rótulo da linha atual é igual a lista[count].atr1
                    if (strcmp(lista[i].rotulo, lista[*count].atr1) == 0) {
                        // Se for igual, você pode executar a ação desejada
                        *count = i;
                        // Faça o que for necessário quando o rótulo for encontrado
                    }
            }
                };
            break;

        case 19: // STR n (Armazenar valor)
        // PROBLEMA
            p->M[atoi(lista[*count].atr1)] = p->ch[p->s]; 
            p->s -= 1;
            break;
 
        case 20: // RD (Leitura)
            printf("Digite o próximo valor de entrada: ");
            char* entrada;
            scanf("%d", entrada);
            empilhar(&p, entrada);
            break;

        case 21: // PRN (Impressão)
            printf("%d\n", desempilhar(p));
            break;

        case 23: // ALLOC m (Alocar memória)
            for (int k = 1; k < *(int*)lista[*count].atr2; k++){
                p->s = p->s + 1;                // Incrementa o topo da pilha
                int m = atoi(lista[*count].atr1);
                p->ch[p->anterior] = p->ch[m + k];       // Copia o valor de M[m+k] para o topo da pilha
            }
            break;

        case 24: // DALLOC m (Liberar memória)
            for (int k = *(int*)lista[*count].atr2 - 1; k >= 0; k--) {
                p->ch[*lista[*count].atr1 + k] = p->ch[p->anterior];       // Copia o valor do topo da pilha para M[m+k]
                p->anterior = p->anterior - 1;                // Decrementa o topo da pilha
            }
            break;

        case 25: // CALL p (Chamar procedimento ou função)
            for (int i = 0; i < MAX_INST; i++) {
                // Verifique se o rótulo da linha atual é igual a lista[count].atr1
                if (strcmp(lista[i].rotulo, lista[*count].atr1) == 0) {
                    // Se for igual, você pode executar a ação desejada
                    *count = i;
                    // Faça o que for necessário quando o rótulo for encontrado
                }
            break;

        case 26: // Return
            i = desempilhar(&p);
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
void MVD(struct node_lista_char *p, FILE *file) {
    char lerString[50];
    struct Inst lista[MAX_INST];
    int countres = 0;
    lerInstrucoes(file, lista);
    char *result = lista[0].instrucao;
    if (strcmp(lista[0].instrucao, "START   ") != 0) {
        printf("Erro: A primeira instrução deve ser 'START'.\n");
        return;
    }
    while (strcmp(lista[countres].instrucao, "HLT     ") != 0) {
            countres++;
            resolveInst(p, file, &countres, lista);
    }
    printf("\nHLT - FIM DO PROGRAMA");
}

int main() {
    node_lista_char p;
    inicializarPilha(&p);
    FILE *file = fopen("teste.txt", "r");
    MVD(&p, file);
    fclose(file);
    liberarPilha(&p);
    return 0;
}
