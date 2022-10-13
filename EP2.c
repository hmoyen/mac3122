#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"
#define MAX 30

typedef struct {

    int tamanho;
    char palavra[MAX];


} palavras;

typedef struct {

    int len;
    int dir;
    int posX;
    int posY;
    int idxPalavra;

} espaco;


void reiniciaEspaco(int lin, int col, int tam, int dir, char**tab);
void imprimeTab(char**tab, int lin, int col);

int main() {

    palavras * listaPalavras;
    int lin, col, i,j, qntd, contaLetra, ok, sol,k;
    int contadorEspacos, espacoInicialx, espacoInicialy,  espacoIndex, qntdMaxEspacos;
    char act;
    int **tabInt, atualX, atualY;
    char **tab;
    pilha * idxEspacos;
    espaco * esp;
    idxEspacos = cria();

    scanf("%d %d", &lin, &col);

    while(lin != 0 && col != 0){

        if(lin==0 && col ==0) {
            break;
        }

        tabInt = malloc(lin * sizeof (int *));

        for (i = 0; i < lin; i++){
            tabInt[i] = malloc (col * sizeof(int));
            for (j = 0; j < col ; j++) 
                tabInt[i][j] = 0;
        }

        for(i=0; i< lin; i++)
            for(j=0;j<col;j++)
                scanf("%d", &tabInt[i][j]);
        
        

        scanf("%d", &qntd);

        if(qntd ==1) {
            printf("Nao ha palavras suficientes");
            break;
        }

        listaPalavras = malloc(qntd * sizeof (palavras));

        for(i=0; i<qntd; i++){
            contaLetra = 0;
            scanf(" %c", &act);

            for(j=0; act != '\n'; j++) {

                contaLetra += 1;
                listaPalavras[i].palavra[j] = act;
                scanf("%c", &act);

            }
            listaPalavras[i].tamanho = contaLetra;
        }

        
    qntdMaxEspacos = (col)*lin; /* calculando qual o maximo de esp possivel em um tabuleiro para alocar memoria */

    esp = malloc( qntdMaxEspacos* sizeof (espaco));

    espacoIndex = 0; contadorEspacos = 0;

    for(i=0;i<lin;i++){

        for(j=0;j<col;j++) {

            if(contadorEspacos==0 && tabInt[i][j]==0){

            espacoInicialx = i; 
            espacoInicialy = j;

            }

            if (tabInt[i][j]==0){
                contadorEspacos +=1;
           
            
            }
            
            if (tabInt[i][j]!=0 || j==(col-1)) {

                if(contadorEspacos>1) {

                esp[espacoIndex].len = contadorEspacos;
                esp[espacoIndex].posX = espacoInicialx;
                esp[espacoIndex].posY = espacoInicialy;
                esp[espacoIndex].dir = 0;
                printf("dentro do loop %d \n", (espacoIndex+1));
                espacoIndex+=1;

                }

            contadorEspacos = 0;
            }
    }
    }
    contadorEspacos=0;

   

    for(j=0;j<col;j++){

        for(i=0;i<lin;i++) {

            if(contadorEspacos==0 && tabInt[i][j]==0){

            espacoInicialx = i; 
            espacoInicialy = j;
           

            }

            if (tabInt[i][j]==0){
                contadorEspacos +=1;
                
            
            }
            
            if (tabInt[i][j]!=0 || i==(lin-1)) {

                if(contadorEspacos>1) {

                esp[espacoIndex].len = contadorEspacos;
                
                esp[espacoIndex].posX = espacoInicialx;
                esp[espacoIndex].posY = espacoInicialy;
                esp[espacoIndex].dir = 1;
                printf("oi\n");
                
                espacoIndex+=1;

            }

            contadorEspacos = 0;
        }
    }
    }

    for(i=0;i<espacoIndex;i++) {
        printf("Espaco numero %d \n", (i+1));
        printf("Comprimento: %d \n", esp[i].len);
        printf("Posicao: (%d, %d) \n", esp[i].posX, esp[i].posY);
        printf("Sentido: %d \n",esp[i].dir );

    }

    printf("%d", espacoIndex);

    tab = malloc(lin * sizeof (char *));

    for (i = 0; i < lin; i++){
        tab[i] = malloc (col * sizeof(char));
        for(j=0;j<col;j++) {
            if(tabInt[i][j]==0) {
                tab[i][j] = '-';
            } else {
                tab[i][j] = '*';
            }
        }
    }

    printf("%d", espacoIndex);
    
    for(i=0;i<lin;i++) {
        for(j=0;j<col;j++) {
            printf("%c", tab[i][j]);
        }
        printf("\n");
    }


    contaLetra = 0; ok =1; i =0; sol =1;j=0;
    printf("%d", espacoIndex);

    /* esp horizontais */

     while(i<espacoIndex){
        printf("entreeeei");

        while(j<qntd && !ok){

            esp[i].idxPalavra = j;
            printf("entrei no loop");

            if(listaPalavras[j].tamanho == esp[i].len) {
                printf("entrei no if");
                atualX = esp[i].posX;
                atualY = esp[i].posY;

                for(k=0;k<esp[i].len;k++){
                    printf("entrei no for");
                    if(tab[atualX][atualY] =='-' || 
                    tab[atualX][atualY]== listaPalavras[j].palavra[contaLetra]){
                        tab[atualX][atualY] = listaPalavras[j].palavra[contaLetra];
                        ok =1;
                        if(esp[i].dir==0){
                            atualY++;
                        } else {
                            atualX++;
                        }
                        contaLetra++;
                    } else {
                        
                        break;
                    }
                }

            }
            j++; 

        }

        if(ok){
            empilha(idxEspacos, i);
            i++;
        } else {
        if(pilhaVazia(idxEspacos)){
            sol = 0;
            printf("Nao ha solucao");

        }
        i = desempilha(idxEspacos);
        j = esp[i].idxPalavra;
        reiniciaEspaco(esp[i].posX, esp[i].posY, esp[i].len, esp[i].dir, tab);
        j++;
        }

                
    }

    if (sol){
        imprimeTab(tab, lin, col);

    } 

    for (i = 0; i < lin; i++){
        free(tabInt[i]);
    }
    free(tabInt);
    for (i = 0; i < lin; i++)
        free(tab[i]);
    free(tab);
    free(listaPalavras);
    free(esp);
    scanf("%d %d", &lin, &col);


    }

    return 0;

    }
    
void reiniciaEspaco(int lin, int col, int tam, int dir, char**tab) {

    while(tam>0){
        tab[lin][col]='-';
        if(dir==0){
            col++;
        } else {
            lin++;
        }
    }
    tam--;
}
void imprimeTab(char**tab, int lin, int col){
    int i, j;
    for(i=0;i<lin;i++){
        for(j=0;j<col;j++){
            printf("%c", tab[i][j]);
        }
        printf("\n");
    }
    

}

