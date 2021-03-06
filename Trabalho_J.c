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
            else{ //se nao for a ultima posi??????o, trocamos o conteudo da posi??????o que queremos remover pela ultima e fazemos -1 ao total de equipamentos
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
int verificarLivre(Equipamento E[TAMANHO], char cod[50], int qt)
{
  
  int a;

  for (a = 0; a < qt; a++){
    if (strcmp(E[a].codigo,cod)==0 && E[a].livre==1)
        return (1);
  }
  printf("Nao esta disponivel\n");

  return(0);
}

int verificarDistancia(Equipamento E[TAMANHO], int qt, int dist, char cod[50])
{
  int i;
  for ( i = 0; i < qt; i++){
    if (strcmp(E[i].codigo,cod)==0 && E[i].autonomia>=dist)
      return(1);

  }
  printf("Escolha uma distancia menor\n");

  return(0);
}

void listarPedidos(Utilizacao U[TAMANHO], int nPedido)
{
  int i;
  for ( i = 0; i < nPedido; i++)
  {
      printf("----------------------\n");
      printf("Numero de Pedido: %d\n", U[i].nrPedido);
      printf("NIF: %d\n", U[i].nif);
      printf("Codigo: %s\n", U[i].codigo);
      printf("Tempo: %d\n", U[i].tempo);
      printf("Distancia: %d\n", U[i].distancia);
      printf("----------------------\n");
  }
}

int removerPedidos(Equipamento E[TAMANHO],Utilizacao U[TAMANHO], int qt, int contaPed, int nPedido)
{
  int i, a;

  for ( i = 0; i < contaPed; i++){

    if (nPedido == U[i].nrPedido){

      for (a = 0; a < qt; a++){
        if (strcmp(E[a].codigo, U[i].codigo) == 0) {
            E[a].livre = 1;
            break;
        }
      }

      if (i == contaPed-1)
        return (1);
      else{
        strcpy(U[i].codigo,U[contaPed-1].codigo);
        U[i].nif = U[contaPed-1].nif;
        U[i].tempo = U[contaPed-1].tempo;
        U[i].distancia = U[contaPed-1].distancia;

        return(1);
      }
    }
  }
  return (0);
}

int entregarEquipamento(Utilizacao U[TAMANHO], Equipamento E[TAMANHO], int contaPed, int nPed, int qt, int tempo)
{
    int i,a;

    //ciclo para encontrar o pedido
    for (i = 0; i < contaPed; i++){
        if (nPed == U[i].nrPedido){

            if (U[i].tempoUtilizado > 0){
                printf("Este Equipamento ja foi entregue\n");
            }

            U[i].tempoUtilizado = tempo;

            //dentro do pedido verificar qual o equipamento e marcar como "livre"
            for (a = 0; a < qt; a++){
                if (strcmp(E[a].codigo,U[i].codigo)==0){
                    E[a].livre=1;
                    printf("Livre: %d\n", E[a].livre);
                    return(1);
                }
            }
        }
    }

    printf("Esse Equipamento nao foi requisitada, logo nao pode ser entregue\n");

   return(0);
}

int calcularPreco(Utilizacao U[TAMANHO], Equipamento E[TAMANHO], int qt, int contaPed, int nPed)
{
    int i, a;
    float preco, precoUtiliz;

    //ciclo para encontrar o pedido
    for (i = 0; i < contaPed; i++){
        if (nPed == U[i].nrPedido){

            //dentro do pedido posicionar no equipamento
            for (a = 0; a < qt; i++){
                if (strcmp(E[i].codigo,U[i].codigo)==0){
                    preco= U[i].tempo * E[a].custo;
                    precoUtiliz= U[i].tempoUtilizado * E[a].custo;

                    printf("Preco a pagar (Tempo Previsto): %d * %.2f = %.2f euros\n", U[i].tempo, E[a].custo, preco);
                    printf("Preco a pagar (Tempo Utilizado): %d * %.2f = %.2f euros\n", U[i].tempoUtilizado, E[a].custo, precoUtiliz);
                    return(1);
                }
            }
        }
    }

    return 0;
}

int verTransacoes (Utilizacao U[TAMANHO], Equipamento E[TAMANHO], char cod[50], int contaPed, int qt)
{
    int i,a;

    //ciclo para verificar os pedidos do codigo
    for (i = 0; i < contaPed; i++){
        if (strcmp(U[i].codigo,cod)==0){

            //dentro do pedido posicionar no equipamento
            for (a = 0; a < qt; i++){
                if (strcmp(E[a].codigo,cod)==0){
                      printf("----------------------\n");
                      printf("Numero de Pedido: %d\n", U[i].nrPedido);
                      printf("NIF: %d\n", U[i].nif);
                      printf("Codigo: %s\n", U[i].codigo);
                      printf("Tempo Previsto: %d\n", U[i].tempo);
                      printf("Tempo Utilizado: %d\n", U[i].tempoUtilizado);
                      printf("Distancia Prevista: %d\n", U[i].distancia);
                      printf("Autonomia Restante: %d\n", E[a].autonomia);
                      printf("----------------------\n");
                      break;
                }
            }
        }
    }
return 0;
}

//fun??????o para ler ficheiro equipamentos e carregar o array de Equipamentos
int LerFicheiroEquipamentos(Equipamento E[TAMANHO]){
    int i=0;

    FILE * ficheiro;

    ficheiro = fopen("Equipamentos.txt","r");

    if (ficheiro != NULL){ //verificar se o ficheiro existe
        while ((fgets(E[i].codigo,50, ficheiro) != NULL) && i<1000){
            E[i].codigo[strlen(E[i].codigo) -1]='\0';

            fgets(E[i].tipo,50, ficheiro);
            E[i].tipo[strlen(E[i].tipo) -1]='\0';

            fscanf(ficheiro,"%d\n", &E[i].autonomia);
            fscanf(ficheiro,"%f\n", &E[i].custo);
            fscanf(ficheiro,"%d\n", &E[i].livre);

            i++;
        }
        fclose(ficheiro);

        return i; //para retornar o n??? de registos do array
    }

    return 0;
}

//fun??????o para reescrever o ficheiro com os equipamentos, com o conteudo do array de equipamentos
void EscreverFicheiroEquipamentos(Equipamento E[TAMANHO], int qt){
    int i;
    FILE * ficheiro; //descritor do ficheiro

    ficheiro = fopen("Equipamentos.txt","w"); //abrir ficheiro para escrita

    for (i=0;i<qt;i++){
        fprintf(ficheiro, "%s\n", E[i].codigo); //1??? linha - codigo de equipamento
        fprintf(ficheiro, "%s\n", E[i].tipo);
        fprintf(ficheiro, "%d\n", E[i].autonomia);
        fprintf(ficheiro, "%2f\n", E[i].custo);
        fprintf(ficheiro, "%d\n", E[i].livre);

    }
    fclose(ficheiro);
}

//fun??????o para ler ficheiro Pedidos de utiliza??????o e carregar a estrutura Utilizacao
int LerFicheiroUtilizacao(Utilizacao U[TAMANHO]){
    int i=0;

    FILE * ficheiro;

    ficheiro = fopen("Utilizacao.txt","r");

    if (ficheiro != NULL){ //verificar se o ficheiro existe
        while ((fgets(U[i].codigo,50, ficheiro) != NULL) && i<1000){
            U[i].codigo[strlen(U[i].codigo) -1]='\0';

            fscanf(ficheiro,"%d\n", &U[i].nif);
            fscanf(ficheiro,"%d\n", &U[i].tempo);
            fscanf(ficheiro,"%d\n", &U[i].tempoUtilizado);
            fscanf(ficheiro,"%d\n", &U[i].distancia);
            fscanf(ficheiro,"%d\n", &U[i].nrPedido);

            i++;
        }
        fclose(ficheiro);

        return i; //para retornar o n??? de registos do array
    }

    return 0;
}

//fun??????o para reescrever o ficheiro com os pedidos, com o conteudo do array de pedidos de utilizacao
void EscreverFicheiroUtilizacao(Utilizacao U[TAMANHO], int qt){
    int i;
    FILE * ficheiro; //descritor do ficheiro

    ficheiro = fopen("Utilizacao.txt","w"); //abrir ficheiro para escrita

    for (i=0;i<qt;i++){
        fprintf(ficheiro, "%s\n", U[i].codigo); //1??? linha - codigo de equipamento
        fprintf(ficheiro, "%d\n", U[i].nif);
        fprintf(ficheiro, "%d\n", U[i].tempo);
        fprintf(ficheiro, "%d\n", U[i].tempoUtilizado);
        fprintf(ficheiro, "%d\n", U[i].distancia);
        fprintf(ficheiro, "%d\n", U[i].nrPedido);
    }
    fclose(ficheiro);
}

int main(int argc, char *argv[])
{
    Utilizacao Uti[TAMANHO];
    int contaPedidos=0;  // contador dos pedidos
    int tempo, distancia, nif;
    char codigoU[50];
    int uinserir, vcodigoU, vdistancia, premov;
    int numPedido=0;
    int tempoUtiliz=0;

    Equipamento Equip[TAMANHO];
    int opcao;
    int livre=0, autonomia, quantidade=0;
    char codigoM[50];
    char tipo[50];
    float custo;
    int minserido, mremov, vcodigoM;
    int sdistancia=autonomia;
    int entregarm;
    int cpreco;

    //ler ficheiros e carregar arrays "Uti" e "Equip"
    quantidade = LerFicheiroEquipamentos(Equip);
    contaPedidos = LerFicheiroUtilizacao(Uti);

    do {
        opcao= menu();
        switch (opcao){

            case 1:      // inserir Equipamento
                printf("Codigo: ");
                scanf("%s", codigoM);

                vcodigoM=verificarCodigo(Equip,quantidade,codigoM);

                while (vcodigoM==1){
                    printf("Esse codigo ja existe\n");
                    printf("Codigo: ");
                    scanf("%s", codigoM);
                    vcodigoM=verificarCodigo(Equip,quantidade,codigoM);
                }

                printf("Tipo: ");
                scanf("%s", tipo);
                printf("Autonomia: ");
                scanf("%d", &autonomia);
                printf("Custo: ");
                scanf("%f", &custo);

                minserido = inserirEquipamento(Equip,quantidade,codigoM,tipo,autonomia,custo);
                if (minserido == 1)
                {
                    printf("Inserido!\n");
                    quantidade++;
                    livre++;

                    EscreverFicheiroEquipamentos(Equip, quantidade); //escrever ficheiro equipamentos, j??? com o este novo
                }
                else
                    printf("Nao inserido!\n");

                break;

            case 2:                   // listar Equipamento
                listarEquipamento(Equip, quantidade);
                break;

            case 3:
                printf("Codigo: ");
                scanf("%s", codigoM);
                mremov = removerEquipamento(Equip, quantidade, codigoM);
                while (mremov==0){
                    printf("Esse codigo nao existe\n");
                    printf("Codigo: ");
                    scanf("%s", codigoM);
                    mremov = removerEquipamento(Equip, quantidade, codigoM);
                }
                printf("Removido\n");
                quantidade--;

                EscreverFicheiroEquipamentos(Equip, quantidade); //escrever ficheiro equipamentos, j??? sem o equipamento removido
                break;

            case 4:
                printf("Codigo: ");
                scanf("%s", codigoU);
                vcodigoU=verificarCodigo(Equip,quantidade,codigoU);

                while (vcodigoU==0)
                {
                    printf("Nao existe esse codigo\n");
                    printf("Codigo: ");
                    scanf("%s", codigoU);
                    vcodigoU=verificarCodigo(Equip,quantidade,codigoU);
                }

                vcodigoU=verificarLivre(Equip,codigoU,quantidade);
                if (vcodigoU == 0){
                    break;
                }

                printf("NIF: ");
                scanf("%d", &nif);
                printf("Tempo: ");
                scanf("%d", &tempo);
                printf("Distancia: ");
                scanf("%d", &distancia);
                vdistancia=verificarDistancia(Equip,quantidade,distancia,codigoU);

                while (vdistancia==0)
                {
                    printf("Distancia: ");
                    scanf("%d", &distancia);
                    vdistancia=verificarDistancia(Equip,quantidade,distancia,codigoU);
                }

                uinserir = pedidoUtilizacao(Equip, Uti, contaPedidos, nif, codigoU, tempo, distancia, quantidade);

                if (uinserir == 1)
                {
                    printf("O pedido foi registado!\n");
                    contaPedidos++;
                    sdistancia= sdistancia - distancia;

                    EscreverFicheiroUtilizacao(Uti, contaPedidos); //escrever ficheiro pedidos, j??? com o este novo
                }
                else
                    printf("Pedido recusado!\n");

                break;

            case 5:
                listarPedidos(Uti,contaPedidos);
                break;

            case 6:
                printf("Numero do Pedido: ");
                scanf("%d", &numPedido);
                premov=removerPedidos(Equip,Uti,quantidade,contaPedidos, numPedido);

                while (premov==0)
                {
                    printf("Nao existe esse Pedido\n");
                    printf("Numero do Pedido: ");
                    scanf("%d", &numPedido);
                    premov=removerPedidos(Equip,Uti,quantidade,contaPedidos, numPedido);
                }
                printf("Removido\n");
                contaPedidos--;

                EscreverFicheiroUtilizacao(Uti, contaPedidos); //escrever ficheiro pedidos, j??? sem o pedido removido
                break;

            case 7: // entregar veiculos
                printf("Numero do Pedido: ");
                scanf("%d", &numPedido);
                printf("Tempo utilizado: ");
                scanf("%d", &tempoUtiliz);

                entregarm=entregarEquipamento(Uti,Equip,contaPedidos,numPedido,quantidade,tempoUtiliz);
                if (entregarm==0)
                    break;

                printf("Entregue\n");

                EscreverFicheiroUtilizacao(Uti, contaPedidos); //escrever ficheiro pedidos, j??? com o pedido entregue
                break;

            case 8:
                printf("Numero do Pedido: ");
                scanf("%d", &numPedido);
                cpreco=calcularPreco(Uti,Equip,quantidade,contaPedidos,numPedido);

                while (cpreco==0)
                {
                    printf("Numero de ordem: ");
                    scanf("%d", &numPedido);
                    cpreco=calcularPreco(Uti,Equip,quantidade,contaPedidos,numPedido);
                }

                break;

            case 9:
                // ver transacoes
                printf("Codigo: ");
                scanf("%s", codigoM);
                vcodigoM=verificarCodigo(Equip,quantidade,codigoM);

                if (vcodigoM==0){
                    printf("Esse codigo nao existe\n");
                    break;
                }

                verTransacoes(Uti,Equip,codigoM,contaPedidos, quantidade);

                break;

        }
    } while (opcao != 0);

    return(0);
}

