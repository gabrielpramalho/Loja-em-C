#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
char FILENAME[] = "loja.data";


typedef struct produtos{
    int id;
    char nome[100];
    float valor;
}Produto;

int cadastrarProduto(Produto * prod){
  FILE * arq = fopen(FILENAME, "a+");
  if(arq == NULL){
      printf("Falha ao abrir arquivo");
      exit(1);
  }

  int result = fwrite(prod, sizeof(Produto), 1, arq);
  fclose(arq);
  return result;
}

void listar(){
  FILE * arq = fopen(FILENAME, "rb");
  if(arq == NULL){
      printf("Falha ao abrir arquivo");
      exit(1);
  }

  Produto aux;

  printf("*********LISTA DE COMPRAS********\n");
  while (fread(&aux, sizeof(Produto), 1, arq)) {
    printf("ID: %d \tNOME: %s \tVALOR: %.2f\n",
            aux.id, aux.nome, aux.valor);
  }
  printf("********************************************\n");
  fclose(arq);
}

void compra(int cod, float * total, int quantidade){
  FILE * arq = fopen(FILENAME, "rb");
  Produto aux;
  int achou = 0;

  if(arq == NULL){
      printf("Falha ao abrir arquivo");
      exit(1);
  }
  while (fread(&aux, sizeof(Produto), 1, arq)) {
    if(aux.id == cod){
      achou = 1;
      break;
    }
  }
  if(achou){
      *total += (aux.valor * quantidade);
  }else {
    printf("Codigo nao encontrado!\n");
  }
  fclose(arq);
  }




int main(){
    int op;
    Produto aux;
    int num;
    float total = 0;
    int n;
    int quantidade;
    do{
        printf("1 - Cadastrar produto\n2 - Exibir\n3 - Efetuar compra\n0 - Sair\nOpcao: ");
        scanf("%d", &op);
        getchar();

        switch (op){
            case 1:
                system("cls");
                printf("Digite o codigo: ");
                scanf("%d", &aux.id);
                getchar();
                printf("Digite o nome: ");
                fgets(aux.nome, 100, stdin);
                aux.nome[strlen(aux.nome)-1] = 0;
                printf("Digite o valor: ");
                scanf("%f", &aux.valor);
                if(cadastrarProduto(&aux)){
                  system("cls");
                  printf("\nItem inserido com sucesso\n");
                }

                break;
            case 2:
                system("cls");
                listar();
                system("pause");
                system("cls");
                break;
            case 3:

                do{
                    system("cls");
                    listar();
                    printf("Digite o ID do produto desejado: ");
                    scanf("%d", &num);
                    printf("Digite a quantidade desejada: ");
                    scanf("%d", &quantidade);
                    compra(num, &total, quantidade);
                    printf("Preco total a pagar: %.2f\n", total);
                    printf("Deseja continuar?\n1 - SIM\t2 - NAO\n");
                    scanf("%d", &n);
                    if(n == 2){
                      system("cls");
                      printf("Compra realizada com sucesso!\n");
                      printf("%.2f\n", total);
                      system("pause");
                      system("cls");
                    }
                  }while(n != 2);

                break;
            case 0:
                break;
        }
    }while(op != 0);

    return 0;
}
