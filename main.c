#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sll.h"

#define TRUE 1
#define FALSE 0

typedef struct _aluno{
    int id;
    char nome[30];
    float nota;
}Aluno;

void inserirAluno(SLList *meuCofo);
void removerAluno(SLList *meuCofo);
void pesquisarAluno(SLList *meuCofo);
int cmpId(void *a, void *b);
int cmpNome(void *a, void *b);
int cmpNota(void *a, void *b);

int main(void) {
    int aux = 0, opcao = 0, id, resultado;
    char nome[30];
    float nota;
    Aluno *temp;
    SLList *meuCofo;

    meuCofo = sllCreate();

    while(1){
        system("cls");
        printf("1 - Inserir\n");
        printf("2 - Remover\n");
        printf("3 - Pesquisar\n");
        printf("4 - Listar\n");
        printf("5 - Limpar\n");
        printf("6 - Destruir\n:::");
        scanf("%d", &opcao);
        system("cls");

        switch (opcao){
            case 1:
                inserirAluno(meuCofo);
                break;
            case 2:
                removerAluno(meuCofo);
                break;
            case 3:
                pesquisarAluno(meuCofo);
                break;
            case 4:
                temp = (Aluno *) sllGetFirst(meuCofo);
                if(temp == NULL){
                    printf("A colecao esta vazia!\n");
                }else{
                    while(temp != NULL){
                        printf("ID: %d NOME: %s NOTA: %.2f\n", temp->id, temp->nome, temp->nota);
                        temp = sllGetNext(meuCofo);
                    }  
                }
                break;
            case 5:
                do{
                    temp = sllRemoveFirst(meuCofo);
                }while(temp != NULL);
              
                if(temp == NULL){
                    printf("A colecao foi limpa!\n");
                }else{
                    printf("Não foi possivel limpar!\n");
                }
                break;
            case 6:
                resultado = sllDestroy(meuCofo);
                if (resultado){
                    printf("Colecao excluida com sucesso!\n");
                    return 0;
                }
                else{
                    printf("Primeiro limpe a Colecao antes de excluir!\n");
                }
                break;
            default:
                break;
        }
        system("pause");
    }
}

void inserirAluno(SLList *meuCofo){
    int id;
    char nome[30];
    float nota;
    int resultado;

    printf("Insira a ID do Aluno: ");
    scanf("%d", &id);
    printf("Insira o Nome do Aluno: ");
    scanf("%s", nome);
    printf("Insira a Nota do Aluno: ");
    scanf("%f", &nota);

    Aluno *aluno = malloc(sizeof(Aluno));
    
    if(meuCofo != NULL){
        aluno->id=id;
        strcpy(aluno->nome, nome); // copiar um valor da varavel nome pra aluno->nome, usando strcpy
        aluno->nota=nota;
        resultado = sllInsertAsLast(meuCofo, aluno);
        if (resultado){
            printf("Aluno inserido com Sucesso!\n");
        }
        else{
            printf("A colecao esta cheia! Por vafor, exclua para poder inserir.\n");
        }
    }
}
void removerAluno(SLList *meuCofo){
    int id;
    char nome[30];
    float nota;
    int opcao;
    void * resultado;
    while(1){
        printf("Por qual atributo voce deseja remover o Aluno?\n");
        printf("1 - Remover por ID\n");
        printf("2 - Remover por Nome\n");
        printf("3 - Remover por Nota\n");
        scanf("%d", &opcao);

    switch (opcao){
        case 1:
            printf("Insira o ID do Aluno: ");
            scanf("%d", &id);
            resultado = sllRemove(meuCofo, &id, cmpId);
            if(resultado != NULL){
                printf("Removido com Sucesso!\n");
            }
            else{
                printf("Aluno não Removido! Tente novamente.\n");
            }
            return;
            break;
        case 2:
            printf("Insira o Nome do Aluno: ");
            scanf("%s", nome);
            
            resultado = sllRemove(meuCofo, nome, cmpNome);
            if(resultado != NULL){
                printf("Removido com Sucesso!\n");
            }
            else{
                printf("Aluno não Removido! Tente novamente.\n");
            }
            return;
            break;
        case 3:
            printf("Insira a Nota do Aluno:");
            scanf("%f", &nota);
            resultado = sllRemove(meuCofo, &nota, cmpNota);
            if(resultado != NULL){
                printf("Removido com Sucesso!\n");
            }
            else{
                printf("Aluno não Removido! Tente novamente.\n");
            }
            return;
            break;
        default:
            printf("Insira uma opcao valida!\n");
            break;
        
        }
    }
}
void pesquisarAluno(SLList *meuCofo){
    int id;
    char nome[30];
    float nota;
    int opcao;
    Aluno * resultado;
    while(1){
        printf("Por qual atributo voce deseja pesquisar o Aluno?\n");
        printf("1 - Pesquisar por ID\n");
        printf("2 - Pesquisar por Nome\n");
        printf("3 - Pesquisar por Nota\n");
        scanf("%d", &opcao);

    switch (opcao){
        case 1:
            printf("Insira o ID do Aluno: ");
            scanf("%d", &id);
            resultado = (Aluno *) sllQuery(meuCofo, &id, cmpId);
            if(resultado != NULL){
                printf("Aluno Encontrado com Sucesso!\n");
                printf("ID: %d\n", resultado->id);
                printf("Nome: %s\n", resultado->nome);
                printf("Nota: %.2f\n", resultado->nota);
            }
            else{
                printf("Aluno nao Encontrado! Tente novamente.\n");
            }
            return;
            break;
        case 2:
            printf("Insira o Nome do Aluno: ");
            scanf("%s", nome);
            resultado = sllQuery(meuCofo, nome, cmpNome);
            if(resultado != NULL){
                printf("Aluno Encontrado com Sucesso!\n");
                printf("ID: %d\n", resultado->id);
                printf("Nome: %s\n", resultado->nome);
                printf("Nota: %.2f\n", resultado->nota);
            }
            else{
                printf("Aluno nao Encontrado! Tente novamente.\n");
            }
            return;
            break;
        case 3:
            printf("Insira a Nota do Aluno: ");
            scanf("%f", &nota);
            resultado = sllQuery(meuCofo, &nota, cmpNota);
            if(resultado != NULL){
                printf("Aluno Encontrado com Sucesso!\n");
                printf("ID: %d\n", resultado->id);
                printf("Nome: %s\n", resultado->nome);
                printf("Nota: %.2f\n", resultado->nota);
            }
            else{
                printf("Aluno nao Encontrado! Tente novamente.\n");
            }
            return;
            break;
        default:
            printf("Insira uma opcao valida!");
            break;
        }
    }

}

int cmpId(void *a, void *b){
    Aluno *aluno= (Aluno*) a;
    int *id = (int*) b;
    
    if((int) aluno->id == (int) *id){
        return TRUE;
    }
    return FALSE;
}
int cmpNome(void *a, void *b){
    Aluno *aluno= (Aluno*) a;
    char *nome = (char*) b;
    
    if(! strcmp( aluno->nome, nome)){  //compara duas strings   abc abc 0 == false  ! false false = true
        return TRUE;
    }
    return FALSE;
}
int cmpNota(void *a, void *b){
    Aluno *aluno= (Aluno*) a;
    float *nota = (float*) b;

    if((float) aluno->nota == (float) *nota){ 
        return TRUE;
    }
    return FALSE;
}
