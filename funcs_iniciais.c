#include "funcs_iniciais_lib.h"

FILE *fp; 
char* filename = "new.txt";

int main(){
    token tk;
    int linha_main = 0;
    fp = fopen(filename, "r");
    while ( feof(fp) != 1)
    { 
        AnalisadorLexical(fp,&linha_main,&tk);
        print_token(&tk);

    }
}
