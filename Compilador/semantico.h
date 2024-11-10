#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "definicoes.h"
#include "simbolos.h"

void semantic_error(int n){
    //rever todos os rotulos de erro abaixo (placeholders)
    char* erros[] = {"falta definir",
        "1: ",
        };
    
    printf("Erro semantico");
    printf(" %s ", erros[n]);
    printf("na linha %d\n", *linha);

}

//empilha primeiro token de uma lista
void empilha_token(node_lista_token** pilha, node_lista_token** lista){
    if(*pilha != NULL){//se a pilha ja existir
        node_lista_token* temp = *lista;
        *lista = (*lista)->prox;
        temp->prox = *pilha;
        *pilha = temp;
    }else{ // se for a primeira vez empilhando, aponta para o token
        *pilha = *lista;
        *lista = (*lista)->prox;
        (*pilha)->prox = NULL;
    }
}

int prioridade(enum tipos tipo){
    switch(tipo){
        case se:
        case sou:
        case snao:
            return(1);
        case sdif:
        case smaior:
        case smenor:
        case smenorig:
        case smaiorig:
        case sig:
            return(2);
        case smais:
        case smenos:
            return(3);
        case smult:
        case sdiv:
            return(4);
        case ssinalu:
            return(5);
        default: 
            return(0);
    }
}

int checa_operador(enum tipos tipo){
    switch(tipo){
        case se:
        case sou:
        case snao:
        case sdif:
        case smaior:
        case smenor:
        case smenorig:
        case smaiorig:
        case sig:
        case smais:
        case smenos:
        case smult:
        case sdiv:
        case ssinalu:
            return(1);
        default: 
            return(0);
    }
}

//struct com dados de cada operação (tipos de operadores e resultados e numero de operadores)
typedef struct operacao operacao;
typedef struct operacao{
    int qtd_operadores;
    enum tipos tipos_operadores;
    enum tipos tipo_resultado;
}operacao;

//recebe um sinal e retorna o formato da operacao
operacao formato_operacao(enum tipos tipo){
    operacao retorno;
    switch(tipo){
        case smult:
        case sdiv:
        case smais:
        case smenos:
            retorno.qtd_operadores = 2;
            retorno.tipo_resultado = sinteiro;
            retorno.tipos_operadores = sinteiro;
            break;
        case sdif:
        case smaior:
        case smenor:
        case smenorig:
        case smaiorig:
        case sig:
            retorno.qtd_operadores = 2;
            retorno.tipos_operadores = sinteiro;
            retorno.tipo_resultado = sbooleano;
            break;
        case se:
        case sou:
            retorno.qtd_operadores = 2;
            retorno.tipos_operadores = sbooleano;
            retorno.tipo_resultado = sbooleano;
            break;
        case snao:
            retorno.qtd_operadores = 1;
            retorno.tipos_operadores = sbooleano;
            retorno.tipo_resultado = sbooleano;
            break;
        case ssinalu:
            retorno.qtd_operadores = 1;
            retorno.qtd_operadores = sinteiro;
            retorno.qtd_operadores = sinteiro;
    }
    return(retorno);
}

//recebe expressao como lista de tokens (esquerda = início) e transforma em lista pos-fixa (reordena a lista) e retorna o início
node_lista_token* converte_inf_posfix(node_lista_token* lista_infix){
    node_lista_token* retorno_pos = NULL; // endereço de retorno (início da lista posfixa)
    node_lista_token* lista_pos = NULL; // ponteiro para ultimo elemento adicionado na lista posfixa
    node_lista_token* pilha = NULL; // topo da pilha

    while(lista_infix != NULL){
        if(lista_infix->tk.simbolo == sinteiro || lista_infix->tk.simbolo == sidentificador){ //Se for variável ou número copia na saída;     
            if(lista_pos != NULL){ // se não for a primeira vez, muda o ponteiro prox e atualiza ponteiro lista
                lista_pos->prox = lista_infix;
                lista_pos = lista_pos->prox;
            }else{ //se for a primeira vez, só aponta para token e seta o ponteiro que vai ser retornado
                lista_pos = lista_infix;
                retorno_pos = lista_infix;
            }
            lista_infix = lista_infix->prox;
        }else if(lista_infix->tk.simbolo == sabre_parenteses){ //Se for abre-parênteses empilha; 
            empilha_token(&pilha, &lista_infix);
        }else if(lista_infix->tk.simbolo == sfecha_parenteses){ //Se for fecha-parênteses, desempilha tudo copiando na saída até o primeiro abre-parênteses
            while (pilha->tk.simbolo != sabre_parenteses){
                lista_pos->prox = pilha;
                lista_pos = lista_pos->prox;
                pilha = pilha->prox;
            }
            
            //desempilha abre parentesis
            node_lista_token* temp_free = pilha;
            pilha = pilha->prox;
            free(temp_free);

            lista_infix = lista_infix->prox;
        }else if(checa_operador(lista_infix->tk.simbolo)){
            /*Se for operador, empilha após percorrer desempilhando e copiando na saída todos os operadores com precedência maior ou igual ao 
            que será empilhado, isso até encontrar o primeiro operador com precedência menor, terminar a pilha ou encontrar o primeiro abreparênteses*/
            while(pilha != NULL && pilha->tk.simbolo != sabre_parenteses && (prioridade(lista_infix->tk.simbolo) <= prioridade(pilha->tk.simbolo))){
                lista_pos->prox = pilha;
                lista_pos = lista_pos->prox;
                pilha = pilha->prox;
            }

            //empilha
            empilha_token(&pilha, &lista_infix);
        }
    }

    //Se terminar a expressão, desempilhar copiando na saída todos os operadores ainda existentes na pilha
    lista_pos->prox = pilha;
    return retorno_pos;
}

///recebe expressao pos-fixa e faz a analise semantica retornando seu tipo (sinteiro / sbooleano) - destroi a lista no processo
enum tipos semantico_expressao(node_lista_token* lista_posfix){
    // percorre a lista empilhando os valores, e desempilhando conforme encontra operadores
    node_lista_token* pilha = NULL;

    while(lista_posfix != NULL){
        if(lista_posfix->tk.simbolo == sinteiro || lista_posfix->tk.simbolo == sidentificador){ //se for variável, empilha
            if(lista_posfix->tk.simbolo == sidentificador){
                //procurar tabela
                if(lista_posfix->tk.simbolo == sidentificador){
                    entrada_tab_simbolos* entrada_tabela_operador;
                    entrada_tabela_operador = busca_ident(lista_posfix->tk.lexema);
                    if(entrada_tabela_operador == NULL){
                        semantic_error(0);
                        return serro;
                    }
                    lista_posfix->tk.simbolo = entrada_tabela_operador->tipo;
                }
            }
            empilha_token(&pilha, &lista_posfix);
        
        }else if(checa_operador(lista_posfix->tk.simbolo)){ //se for operador, ver quantos desempilhar, e checa se os tipos estão corretos
            operacao analisando = formato_operacao(lista_posfix->tk.simbolo);
            /// guardar os 2 operadores e mandar para geracao de codigo após desempilhar (ordem ao contrario)
            for(int i = 0; i<analisando.qtd_operadores; i++){
                if(pilha->tk.simbolo != analisando.tipos_operadores){
                    semantic_error(0);
                    return serro;   
                }else{
                    node_lista_token* temp_free = pilha;
                    pilha = pilha->prox;
                    free(temp_free);
                }
            } 

            ///gera código (?) - exemplo: c b div -> manda (em diferentes funções) c, b, div, nessa ordem - entrada da tabela inteira (se for numero, manda só o numero).
            ///lembrar de colocar um if vendo se é numero ou identificador para mandar pela funcao certa. 

            //empilha resultado
            token temp_token;
            temp_token.simbolo = analisando.tipo_resultado;
            node_lista_token* temp_node = novo_no_token(temp_token);
            
            temp_node->prox = pilha;
            pilha = temp_node; 

            //tira o operador da lista
            temp_node = lista_posfix;
            lista_posfix = lista_posfix->prox;
            free(temp_node);
        }
    }
    if(pilha->prox != NULL){
            semantic_error(0);
            return serro;
        }

    return (pilha->tk.simbolo);
}