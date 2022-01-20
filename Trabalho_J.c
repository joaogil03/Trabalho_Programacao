#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define TAMANHO 100

typedef struct
{
    int nif;
    char codigo[50];
    int tempo;
    int distancia;
    int nrPedido;
    int tempoUtilizado; //para sabermos como calcular o custo real e se foi entregue ou nao (enquanto estiver "0", nao esta entregue)
}Utilizacao;

typedef struct
{
    float custo;
    char tipo[50];
    int livre;
    int autonomia;
    char codigo[50];
}Equipamento;

int menu(); // onde vou criar o menu para o Utilizacao
int inserirEquipamento(Equipamento E[TAMANHO], int qt, char cod[50], char tp[50], int autonom, float ct); // inserir a Equipamento
void listarEquipamento(Equipamento E[TAMANHO], int qt);
int removerEquipamento(Equipamento E[TAMANHO], int qt, char cod[50]);
int pedidoUtilizacao(Equipamento E[TAMANHO], Utilizacao U[TAMANHO], int nPedido, int num, char cod[50], int temp, int dist, int qt);
int verificarCodigo(Equipamento E[TAMANHO], int qt, char cod[50]);
int verificarLivre(Equipamento E[TAMANHO], char cod[50], int qt);
int verificarDistancia(Equipamento E[TAMANHO], int qt, int dist, char cod[50]);
void listarPedidos(Utilizacao U[TAMANHO], int nPedido);
int removerPedidos(Equipamento E[TAMANHO],Utilizacao U[TAMANHO], int qt, int contaPed, int nPedido);
int calcularPreco(Utilizacao U[TAMANHO], Equipamento E[TAMANHO], int qt, int contaPed, int nPed);
int verTransacoes(Utilizacao U[TAMANHO], Equipamento E[TAMANHO], char cod[50], int contaPed, int qt);
int entregarEquipamento(Utilizacao U[TAMANHO], Equipamento E[TAMANHO], int contaPed, int nPed, int qt, int tempo);
int LerFicheiroEquipamentos(Equipamento E[TAMANHO]);
void EscreverFicheiroEquipamentos(Equipamento E[TAMANHO], int qt);
int LerFicheiroUtilizacao(Utilizacao U[TAMANHO]);
void EscreverFicheiroUtilizacao(Utilizacao U[TAMANHO], int qt);

int menu()
{
    int opcao;

    do
    {
        printf(" M E N U \n");
        printf("1- Inserir Equipamento\n");
        printf("2- Listar Equipamento\n");
        printf("3- Remover Equipamento\n");
        printf("4- Pedido de utilizacao\n");
        printf("5- Listar pedidos\n");
        printf("6- Remover pedido de utilizacao\n");
        printf("7- Entregar Equipamento\n");
        printf("8- Calcular custo do pedido\n");
        printf("9- Ver Transacoes\n");
        printf("0- Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
    }
    while ((opcao>10)||(opcao<0));  // as opcoes para ja vao de 8 ate 0, logo tem de ser sempre menores que 9 e maiores que 0

    return (opcao);
}

int inserirEquipamento(Equipamento E[TAMANHO], int qt, char cod[50], char tp[50], int autonom, float ct)
{
    if (qt<TAMANHO){
        strcpy(E[qt].codigo,cod);
        strcpy(E[qt].tipo,tp);
        E[qt].autonomia = autonom;
        E[qt].custo = ct;
        E[qt].livre = 1;
        return(1);
    }

    return (0);
}

void listarEquipamento(Equipamento E[TAMANHO], int qt)
{
    int i;

    for ( i = 0; i < qt; i++)
    {
        printf("----------------\n");
        printf("Codigo: %s\n",E[i].codigo);
        printf("Tipo: %s\n",E[i].tipo);
        printf("Autonomia: %d\n",E[i].autonomia);
        printf("Custo: %.2f\n",E[i].custo);
        printf("Livre: %d\n", E[i].livre);
        printf("----------------\n");
    }
}

int removerEquipamento(Equipamento E[TAMANHO], int qt, char cod[50]) 
{
    int i;

    for ( i = 0; i < qt; i++){
        if (strcmp(E[i].codigo,cod)==0){

            if (i == qt-1) //se o codigo estiver na ultima posicao, basta reduzir 1 ao total de equipamentos
                return (1);
            else{ //se nao for a ultima posi��o, trocamos o conteudo da posi��o que queremos remover pela ultima e fazemos -1 ao total de equipamentos
                strcpy(E[i].codigo,E[qt-1].codigo);
                strcpy(E[i].tipo,E[qt-1].tipo);
                E[i].autonomia = E[qt-1].autonomia;
                E[i].custo = E[qt-1].custo;
                E[i].livre = E[qt-1].livre;
                return(1);
            }
        }
    }

    return (0);
}

int pedidoUtilizacao(Equipamento E[TAMANHO], Utilizacao U[TAMANHO], int contaPed, int num, char cod[50], int temp, int dist, int qt)
{
    int i;

    for (i = 0; i < qt; i++){
        if (contaPed<TAMANHO && strcmp(E[i].codigo,cod)==0)
        {
            strcpy(U[contaPed].codigo,cod);
            U[contaPed].nif = num;
            U[contaPed].tempo = temp;
            U[contaPed].tempoUtilizado = 0;
            U[contaPed].distancia = dist;
            U[contaPed].nrPedido=contaPed+1;
            E[i].livre = 0;
            return (1);
        }
    }

    return (0);
}

int verificarCodigo(Equipamento E[TAMANHO], int qt, char cod[50])
{
  int i;
  for ( i = 0; i < qt; i++){
    if (strcmp(E[i].codigo,cod)==0)
      return(1);
  }

  return (0);
}