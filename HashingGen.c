#include<stdio.h>
#include<stdlib.h>
#include"HashingGen.h"
#include<string.h>
#define N 11
typedef struct elemento{
    int tipo,key;
    void *item;
}Elemento;


typedef struct elemento{ 
    int tipo;   // Tipo 1 aluno e 2 prof
    int key;      
    void *item;
}*Elemento;

// Ok
void InicializaArq(char * nomeArq, void *obj, int sizeObj){
    FILE *arq = fopen(nomeArq,"wb");
    Elemento a;

    a->item = (void*) malloc(sizeObj);
    memcpy(a->item, obj, sizeObj);
    a->tipo=-1;
    a->key=-1;

    for(int i=0; i<N; i++)
        fwrite(&a, sizeof(struct elemento),1,arq);

    fclose(arq);
}

int hashArq(char *nomeArq, int mat){
    
}
int hash1 (Elemento item, int size){
    return item->key%size;
}

int hash2(Elemento p, int size){
    int key;
    key=size-2-(p->key%(size-2));
    return key;
}

void Inserir(char *nomeArq, int key, void *objeto, int sizeObj){
    int pos = AcharPosicao(nomeArq, key, sizeObj);
    Elemento aux;

    FILE *arq = fopen(nomeArq, "r+b");

    aux->item = (void*) malloc(sizeObj);
    memcpy(aux->item, objeto, sizeObj);

    aux->key = key;
    fseek(arq, pos*sizeof(aux), SEEK_SET);

    fwrite(&aux, sizeof(aux),1,arq);
    fclose(arq);
}

int AcharPosicao(char *nomeArq, int key,int sizeObj){
    Elemento aux;
    aux->item = (void*) malloc(sizeObj);

    int pos = hash1(aux ,N);
    int deslocamento =  hash2(aux, N);

    FILE *arq = fopen(nomeArq, "rb");
    fseek(arq, pos * sizeof(aux), SEEK_SET);
    fread(&aux, sizeof(aux), 1,arq);

    while (aux->key != -1){
        pos = (pos + deslocamento) % N;
        fseek(arq, pos *sizeof(aux), SEEK_SET);
        fread(&aux, sizeof(aux),1, arq);
    }
    fclose(arq);
    return pos;
}

int BuscarObj(char * nomeArq, int key, void *resp, int sizeObj){
    Elemento aux;
    FILE *arq = fopen (nomeArq, "rb");
    int i;

    for(i=0; i<N; i++){
        fread(&aux, sizeof(aux), 1, arq);

        if(aux->key == key){
            resp = (void*) malloc(sizeObj);
            memcpy(resp, aux->item, sizeObj);
            fclose(arq);
            return 1;
        }
    }
    fclose(arq);
    return 0;
}

void leituraCompleta(char * nomeArq){
    Elemento aux;
    FILE *arq = fopen(nomeArq, "rb");
    int i;

    for (i=0; i<N; i++){
        fread(&aux, sizeof(aux), 1, arq);
        if(aux->key != -1)
            printf("%i\n", aux->key);
        else    
            printf("Disponivel - \n");
    }
    printf("\n");
    fclose(arq);
}

// void Printa(Elemento *p, int size){
//     for(int i=0;i<size;i++){
//         if(p[i].tipo==1){
//             Aluno al=(Aluno) p[i].item;
//             printf("\nAluno\n");
//             printf("%d\n",al->matricula);
//             printf("%s\n",al->nome);
//             printf("%s\n",al->email);
//             printf("%.2f\n",al->CR);
//         }else if(p[i].tipo==2){
//             Professor prof=(Professor) p[i].item;//esqueci do = kkkkkkkkkkkkkkkk
//             printf("\nProfessor\n");
//             printf("%d\n",prof->matricula);
//             printf("%s\n",prof->nome);
//             printf("%.2lf\n",prof->salario);
//         }
//     }
// }