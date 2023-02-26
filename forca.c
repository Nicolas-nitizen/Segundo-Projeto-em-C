#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "forca.h" // header Files ou arquivos de cabeçalhos. Sao arquivos no nosso diretorio, que podem ser chamados para o codigo final, e sempre usando "aspas".

// variaveis globais
char palavrachave[TAMANHO_PALAVRA];
char chutes[26];
int chutesdados = 0;


void abertura(){
    printf("************************************\n");
    printf("*          JOGO DE FORCA           *\n");
    printf("************************************\n\n");
}
void chuta(){
    char chute;
    scanf(" %c", &chute);

    chutes[chutesdados] = chute;
    chutesdados++; // *(variavel) para pegar o conteudo da variavel, e nao o endereço.
}

int jachutou(char letra){
    int achou = 0;

    for ( int j = 0; j < chutesdados; j++){
        if (chutes[j] == letra){
            achou = 1;
            break;
        }
    }
    return achou;

}

void desenhaforca(){

    int erros = chuteserrados();
    
    printf("  _______      \n");
    printf(" |/      |     \n");
    printf(" |      %c%c%c \n", (erros >= 1 ? "(" : " "), (erros >= 1 ? "_" : " "), (erros >= 1 ? ")" : " "));
    printf(" |      %c%c%c \n", (erros >= 3 ? "\\" : " "), (erros >= 2  ? "|" : " "), (erros >= 3 ? "/" : " "));
    printf(" |        %c   \n", (erros >= 2 ? "|" : " "));
    printf(" |      %c %c  \n", (erros >= 4 ? "/" : " "), (erros >= 4 ? "\\" : " "));
    printf(" |             \n");
    printf("_|___          \n");
    printf("\n\n");


    for (int i = 0; i < strlen(palavrachave); i++){

        int achou = jachutou(palavrachave[i]);

        if (achou){
            printf("%c", palavrachave[i]);
        }
        else{
            printf("_");
        }
    }
    printf("\n\n");

}

void escolhepalavra(){
    FILE* f;
    f = fopen("palavras.txt", "r");
    if (f == 0){
        printf("Desculpe-me, banco de dados indisponivel\n\n");
        exit(1);
    }

    int qtddepalavras;
    fscanf(f, "%d", &qtddepalavras);

    srand(time(0));
    int randomico = rand() % qtddepalavras;

    for(int i = 0; i <= randomico; i++){
        fscanf(f, "%s", palavrachave);
    }


    fclose(f);
}

void adicionarpalavra(){

    char quer;
    printf("Voce quer adicionar uma nova palavra? [S/N] ");
    scanf(" %c", &quer);

    if (quer == 'S'){
        char novapalavra[TAMANHO_PALAVRA];
        printf("Qual a nova palavra? ");
        scanf("%s", novapalavra);

        FILE* f;

        f = fopen("palavras.txt", "r+");
        if (f == 0){
            printf("Desculpe-me, banco de dados indisponivel\n\n");
            exit(1);
          }

        int qtd;
        fscanf(f, "%d", &qtd);
        qtd++;

        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d", qtd);

        fseek(f, 0, SEEK_END);
        fprintf(f, "\n%s", novapalavra);
        
        fclose(f);        
    }

}

int acertou(){
    for (int i = 0; i < strlen(palavrachave); i++){
        if (!jachutou(palavrachave[i])){
            return 0;
        }
    }
    return 1;
}

int chuteserrados(){
    int erros = 0;

    for(int i = 0; i < chutesdados; i++){

        int exite = 0;

        for(int j = 0; j < strlen(palavrachave); j++){
            if (chutes[i] == palavrachave[j]){
                exite = 1;
                break;
            }
        }

        if (!exite) erros++;
    }
    return erros;

}

int enforcou(){
  
    return chuteserrados() >= 5;
}


int main(){

    abertura();
    escolhepalavra();
    
    do{
       
        desenhaforca();
        chuta(); // & server para indicar o endereço da variavel, tambem chamado de ponteiro!

    } while (!acertou() && !enforcou()); // "!" torna uma condição em uma condição inversa ( EX: Verdadeira em falsa )
    if (acertou()){
        printf("PARABENS VOCE GANHOU\n\n");

        printf("       ___________      \n");
        printf("      '._==_==_=_.'     \n");
        printf("      .-\\:      /-.    \n");
        printf("     | (|:.     |) |    \n");
        printf("      '-|:.     |-'     \n");
        printf("        \\::.    /      \n");
        printf("         '::. .'        \n");
        printf("           ) (          \n");
        printf("         _.' '._        \n");
        printf("        '-------'       \n\n");
    } else if(enforcou()) {
        printf("VOCE PERDEU!!!\n");
        printf("A Palavra era ** %s **\n\n", palavrachave);

        printf("    _______________         \n");
        printf("   /               \\       \n"); 
        printf("  /                 \\      \n");
        printf("//                   \\/\\  \n");
        printf("\\|   XXXX     XXXX   | /   \n");
        printf(" |   XXXX     XXXX   |/     \n");
        printf(" |   XXX       XXX   |      \n");
        printf(" |                   |      \n");
        printf(" \\__      XXX      __/     \n");
        printf("   |\\     XXX     /|       \n");
        printf("   | |           | |        \n");
        printf("   | I I I I I I I |        \n");
        printf("   |  I I I I I I  |        \n");
        printf("   \\_             _/       \n");
        printf("     \\_         _/         \n");
        printf("       \\_______/           \n");
    }
    adicionarpalavra();
}   
