#include <stdio.h>
#include <stdlib.h>
#define SIZE 50
#include <string.h>
#include <inttypes.h>

char nome[SIZE][50], placa[SIZE][50], modelo[SIZE][50], marca[SIZE][50];
int cnh[SIZE], pontos[SIZE];
int ano[SIZE], quilometragem[SIZE], categoria[SIZE], disponivel[SIZE], clienteDisponivel[SIZE];
int frota, frotaDisp, frotaLoc, quantidade;
int op;
int sair;
static int linha;
static int cliente;
int qtdDias;
char dataRetirada[SIZE][50], dataEntregaCarro[SIZE][50];

//Estrutura para guardar data
typedef struct
{
    int dia;
    int mes;
    int ano;
} Data;
Data data, dataEntrega;

anobissexto(ano);
unsigned long dist_dias(Data inicio, Data fim);

/* guarda o numero de dias em cada mes para anos normais e bissextos */
int dias_mes[2][13] = {{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
                       {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

void cadastroCliente();
void cadastroVeiculo();
void pesquisaCliente();
void pesquisaVeiculo();
void ListaCliente();
void ListaVeiculo();
void locacao();
void entrega();
void relatorio();
void leituraVeiculo();
void gravarVeiculo();
void menu();
void verificarPontos();
void verificaSair();

int main(void)
{
    leituraVeiculo();
    menu();
}

//menu principal onde acontece a maior parte das ações com o usuário
void menu()
{
    do
    {
        printf("\n|--------------------------------------------------------|");
        printf("\n|--------------- LOCADORA DE VEICULOS GP3 ---------------|");
        printf("\n|--------------------------------------------------------|");
        printf("\n| Frota: %d       |Disponiveis: %d       |Locados: %d     |", frota, frotaDisp, frotaLoc);
        printf("\n|--------------------------------------------------------|");
        printf("\n| [1] Cadastrar Veiculo                                  |");
        printf("\n| [2] Cadastrar Cliente                                  |");
        printf("\n| [3] Pesquisar Veiculo                                  |");
        printf("\n| [4] Pesquisar Cliente                                  |");
        printf("\n| [5] Listar Veiculo                                     |");
        printf("\n| [6] Listar Cliente                                     |");
        printf("\n| [7] Locar Veiculo                                      |");
        printf("\n| [8] Entregar Veiculo                                   |");
        printf("\n| [9] Relatorio                                          |");
        printf("\n| [0] Sair                                               |");
        printf("\n|--------------------------------------------------------|");
        printf("\n| Digite o numero desejado:                              |\n");
        printf("|--------------------------------------------------------|\n");
        scanf("\n%d", &op);

        switch (op)
        {
        case 1:
            cadastroVeiculo();
            break;
        case 2:
            cadastroCliente();
            break;
        case 3:
            pesquisaVeiculo();
            break;
        case 4:
            pesquisaCliente();
            break;
        case 5:
            ListaVeiculo();
            break;
        case 6:
            ListaCliente();
            break;
        case 7:
            locacao();
            break;
        case 8:
            entrega();
            break;
        case 9:
            relatorio();
            break;
        default:
            printf("\n|---------------------------------------------------------|");
            printf("\n|                    VALOR INVALIDO!                      |");
            break;
        }
    } while (op != 0);
}

// metodo feito para cadastrar os veiculos adquiridos pela locadora
void cadastroVeiculo()
{
    do
    {
        printf("\n|----------------- CADASTRO VEICULO ---------------------|");
        printf("\n|--------------------------------------------------------|");
        printf("\n|Digite o numero da placa:                               |\n");
        scanf("\n%s", &placa[linha]);
        printf("\n|Digite a marca:                                         |\n");
        scanf("\n%s", &marca[linha]);
        printf("\n|Digite o modelo:                                        |\n");
        scanf("\n%s", &modelo[linha]);
        printf("\n|Digite o ano de fabricacao:                             |\n");
        scanf("\n%d", &ano[linha]);
        printf("\n|Digite a quilometragem:                                 |\n");
        scanf("\n%d", &quilometragem[linha]);
        printf("\n|Digite a categoria:                                     |\n");
        scanf("\n%d", &categoria[linha]);
        disponivel[linha] = 1;
        // mensagem exibida após o cadastro realizado
        printf("\n|---------------------------------------------------------|");
        printf("\n|           Veiculo cadastrado com sucesso!               |");
        printf("\n|---------------------------------------------------------|\n");
        printf("\n|%s: \n|%s: \n|%s: \n|%d: \n|%d: \n|%d: ", placa[linha], marca[linha], modelo[linha], ano[linha], quilometragem[linha], categoria[linha]);
        printf("\n|---------------------------------------------------------|");
        printf("\n| Digite 1 para continuar ou 0 para sair                  |\n");
        scanf("\n%d", &op);
        //Neste metodo irá ser gravado um arquivo separado chamado backupCadastro para que se esteja tudo dentro das normas os veiculos
        // eles sejam integrados a frota principal
        gravarVeiculo();
        linha++;
        frota++;
        frotaDisp++;
    } while (op == 1);
    if (op == 0)
    {
        menu();
    }
}

// metodo realizado para cadastrar os clientes da locadora
void cadastroCliente()
{
    do
    {

        printf("\n|------------------ CADASTRO CLIENTE --------------------|");
        printf("\n|--------------------------------------------------------|");
        printf("\n Digite o nome:                                          |\n");
        scanf("\n%s", &nome[cliente]);
        printf("\n Digite a CNH:                                           |\n");
        scanf("\n%d", &cnh[cliente]);
        printf("\n|--------------------------------------------------------|");
        printf("\n|               Cadastro realizado com sucesso!          |");
        printf("\n|--------------------------------------------------------|");
        printf("\n| Nome: %s ", nome[cliente]);
        printf("\n| CNH: %d ", cnh[cliente]);
        printf("\n| Pontos: %d ", pontos[cliente]);
        printf("\n|--------------------------------------------------------|");
        printf("\n|      Digite 1 para continuar ou 0 para sair            |\n");
        scanf("\n%d", &op);
        pontos[cliente] = 0;
        clienteDisponivel[cliente] = 1;
        cliente++;
    } while (op == 1);
    if (op == 0)
    {
        menu();
    }
}
// metodo feito para pesquisar os veiculos cadastrados na locadora
void pesquisaVeiculo()
{
    char placaPesquisa[50];
    int categoriaPesquisa;

    int i;
    do
    {

        printf("\n|------------------- PESQQUISA VEICULO -------------------|");
        printf("\n|---------------------------------------------------------|");
        printf("\n| [1] para pesquisar por Placa                            |");
        printf("\n| [2] para pesquisar por Categoria                        |");
        printf("\n| [0] para sair                                           |");
        printf("\n| Digite a opcao desejada                                 |\n");
        scanf("%d", &op);
        printf("\n|---------------------------------------------------------|\n");
        switch (op)
        {
        case 1:

            printf("\n| Digite a Placa:                                         |\n");
            scanf("\n%s", &placaPesquisa);
            for (i = 0; i <= SIZE; i++)
            {
                if (strcmp(placaPesquisa, placa[i]) == 0)
                {
                    printf("\n|-------------------------------|\n |Placa: %s\n |Marca: %s\n |Modelo: %s\n |Ano : %d\n |Quilometragem: %d\n |Categoria: %d\n|-------------------------------|\n ", placa[i], marca[i], modelo[i], ano[i], quilometragem[i], categoria[i]);
                }
            }
            break;
        case 2:
            printf("\n| Digite a categoria:                                     |\n");
            scanf("\n%d", &categoriaPesquisa);
            for (i = 0; i <= SIZE; i++)
            {
                if (categoria[i] == categoriaPesquisa)
                {
                    printf("\n|-------------------------------|\n |Placa: %s\n |Marca: %s\n |Modelo: %s\n |Ano : %d\n |Quilometragem: %d\n |Categoria: %d\n|-------------------------------|\n  ", placa[i], marca[i], modelo[i], ano[i], quilometragem[i], categoria[i]);
                }
            }
            break;
        default:
            printf("\n|---------------------------------------------------------|");
            printf("\n|                 Digite um numero valido                 |");
            break;
        }
    } while (op != 0);
    if (op == 0)
    {
        menu();
    }
}

//  metodo feito para pesquisar os clientes cadastrados na locador
void pesquisaCliente()
{
    char nomePesquisa[50];
    int cnhPesquisa;

    int i;
    do
    {
        printf("\n|------------------- PESQUISA CLIENTE --------------------|");
        printf("\n|---------------------------------------------------------|");
        printf("\n| [1] para pesquisar por Nome                              |");
        printf("\n| [2] para pesquisar por CNH                               |");
        printf("\n| [0] para sair                                            |");
        printf("\n| Digite a opcao desejada                                  |\n");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            printf("\n| Digite o nome:                                          |\n");
            scanf("\n%s", &nomePesquisa);
            for (i = 0; i <= SIZE; i++)
            {
                if (strcmp(nomePesquisa, nome[i]) == 0)
                {
                    printf("\n|-------------------------------|\n |Nome: %s\n |CNH: %d\n |Pontos: %d\n|-------------------------------|\n", nome[i], cnh[i], pontos[i]);
                }
            }
            break;
        case 2:
            printf("\n| Digite a CNH:                                           |\n");
            scanf("\n%d", &cnhPesquisa);
            for (i = 0; i <= SIZE; i++)
            {
                if (cnh[i] == cnhPesquisa)
                {
                    printf("\n|-------------------------------|\n |Nome: %s |CNH: %d |Pontos: %d\n|-------------------------------|\n", nome[i], cnh[i], pontos[i]);
                }
            }
            break;
        default:
            printf("\n|---------------------------------------------------------|");
            printf("\n|              Digite um numero valido!!                  |");
            break;
        }
    } while (op != 0);
    if (op == 0)
    {
        menu();
    }
}
// metodo feito para listar os veiculos cadastrados na locadora
void ListaVeiculo()
{
    int i;
    for (i = 0; i < frota; i++)
    {
        if (placa[i] != NULL)
        {
            printf("\n|-------------------------------|\n |Placa: %s\n |Marca: %s\n |Modelo: %s\n |Ano : %d\n |Quilometragem: %d\n |Categoria: %d\n|------------------------------|\n", placa[i], marca[i], modelo[i], ano[i], quilometragem[i], categoria[i]);
        }
    }
}
// metodo feito para listar os clientes cadastrados na locadora
void ListaCliente()
{
    int i;
    for (i = 0; i < cliente; i++)
    {
        if (nome[i] != NULL)
        {
            printf("\n|-------------------------------|\n |Nome: %s\n |CNH: %d\n |Pontos: %d\n|-------------------------------|\n", nome[i], cnh[i], pontos[i]);
        }
    }
}

void locacao()
{
    char nomePesquisa[20], placaPesquisa[50];
    int i, x;
    char temp[50];
    printf("\t=============================================================\n");
    printf("\t===================== Locacao do veiculo ==================\n");
    printf("\t=============================================================\n\n");

    printf("\n Nome do cliente \n");
    scanf("%s", &nomePesquisa);

    for (x = 0; x <= cliente; x++)
    {
        //Estrutura de decisão para comparar o nome salvo do cliente com o informado
        if (strcmp(nomePesquisa, nome[x]) == 0)
        {
            if (clienteDisponivel[x] != 0)
            {
                printf("\n Placa do veiculo \n ");

                scanf("%s", &placaPesquisa);

                for (i = 0; i <= frota; i++)
                {
                    //Estrutura de decisão para comparar o nome da placa do veiculo salvo com o informado
                    if (strcmp(placaPesquisa, placa[i]) == 0)
                    {
                        if (disponivel[i] != 0)
                        {
                            printf("\n  Data da retirada \n ");

                            scanf("%d/%d/%d", &data.dia, &data.mes, &data.ano);
                            //Aqui ele passa o valor informado na data que seria a data de retirada e
                            //passa para uma variavel temporaria
                            sprintf(temp, "%d/%d/%d", data);
                            //aqui é passado da variavel temporaria para uma variavel que possa armazenar mais
                            //de uma data ou seja cada vez que é alocado um novo carro é introduzida dentro
                            //dessa variavel uma nova data proviniente daquela locação.
                            strcpy(dataRetirada[i], temp);
                            printf("O cliente %s do CNH %d alugou o carro de placa %s de categoria %d com a quilometragem de %d KM, retirado na data de %s.", nome[x], cnh[x], placa[i], categoria[i], quilometragem[i], dataRetirada[i]);
                            linha++;
                            frotaDisp--;
                            frotaLoc++;
                            clienteDisponivel[x] = 0;
                            disponivel[i] = 0;
                            break;
                        }
                        else
                        {
                            printf("Carro indisponivel para alugar");
                            break;
                        }
                    }
                }
            }
            else
            {
                printf("Cliente ja possui um alguel em andamento");
                break;
            }
        }
    }
}

int anobissexto(int ano)
{
    return (ano % 4 == 0) && ((ano % 100 != 0) || (ano % 400 == 0));
}

//Retorna a distancia entre inicio e fim em dias.
//Assume que inicio nao vem depois de fim.

unsigned long dist_dias(Data inicio, Data fim)
{
    unsigned long idias, fdias; //guarda qtos dias tem da data
    // ate o comeco do ano
    unsigned long def_anos = 0;
    //guarda diferenca entre anos das datas inicio e fim medida em dias
    register int i;
    int dbissexto;

    idias = inicio.dia;
    dbissexto = anobissexto(inicio.ano);
    for (i = inicio.mes - 1; i > 0; --i)
        idias += dias_mes[dbissexto][i];

    fdias = fim.dia;
    dbissexto = anobissexto(fim.ano);
    for (i = fim.mes - 1; i > 0; --i)
        fdias += dias_mes[dbissexto][i];

    while (inicio.ano < fim.ano)
        def_anos += 365 + anobissexto(inicio.ano++);

    return def_anos - idias + fdias;
}

void relatorio()
{
    do
    {
        printf("\n\n\n");
        printf("\t=============================================================\n");
        printf("\t======================== RELATORIO ===========================\n");
        printf("\t=============================================================\n\n");
        printf("\n Frota: %d   \n", frota);
        printf("\n Disponiveis: %d \n", frotaDisp);
        printf("\n Locados: %d \n", frotaLoc);
        printf("\t\t\t Desenvolvedores: \n");
        printf("\t\t\t Cassio \n");
        printf("\t\t\t Daniel \n");
        printf("\t\t\t Emanuelle \t  1901570182 \n");
        printf("\n [0] para sair \n");
        printf("\t==============================================================\n\n");
        printf("\n\n\n");
    } while (op == 1);
}

void leituraVeiculo()
{
    char linha1[50];
    char linha2[50];
    char *temp;

    //Nesta parte irá fazer a leitura do arquivo
    FILE *cars = fopen("veiculosCadastrados.txt", "r");
    if (cars != NULL)
    {
        //Nesta parte irá ser lido a primeira linha do arquivo e sera aramazenado a quantidade de veiculos dentro das variaveis frota e frotaDisp
        while (fscanf(cars, "%s", &linha1) != EOF)
        {
            frota = atoi(linha1);
            frotaDisp = atoi(linha1);
            while (fscanf(cars, "%s ", linha2) != EOF)
            {

                //Nesta parte irá ser armazenado dentro da variavel temporaria a primeira parte sendo a da placa
                temp = strtok(linha2, ";");
                strcpy(placa[linha], temp);

                //Nesta parte irá ser armazenado dentro da variavel temporaria a segunda parte da palavra sendo ignorada a primeira
                temp = strtok(NULL, ";");
                strcpy(modelo[linha], temp);

                //Nesta parte irá ser armazenado dentro da variavel temporaria a terceira parte da palavra sendo ignorada a segunda
                temp = strtok(NULL, ";");
                strcpy(marca[linha], temp);

                //Nesta parte irá ser armazenado dentro da variavel temporaria a quarta parte da palavra sendo ignorada a terceira
                temp = strtok(NULL, ";");
                ano[linha] = atoi(temp);

                //Nesta parte irá ser armazenado dentro da variavel temporaria a quinta parte da palavra sendo ignorada a quarta
                temp = strtok(NULL, ";");
                quilometragem[linha] = atoi(temp);

                //Nesta parte irá ser armazenado dentro da variavel temporaria a sexta parte da palavra sendo ignorada a quinta
                temp = strtok(NULL, ";");
                categoria[linha] = atoi(temp);

                //Adiciona a disponibilidade para cada carro criado
                disponivel[linha] = 1;

                //avança o index da matriz
                linha++;
            }
        }
    }
}

void gravarVeiculo()
{
    char linha1[50];
    char linha2[50];
    char *temp;
    int i;
    FILE *cars = fopen("BackupVeiculos.txt", "w");
    quantidade = frota;
    //Nesta primeira parte sera pegado a quantidade total da frota e escrito na primeria linha do arquivo
    fprintf(cars, "%d\n", quantidade);
    for (i = 1; i <= frota; i++)
    {
        if (placa[i] != " ")
        {
            //Nesta primeira parte sera pegado a placa do veiculo e escrito na segunda linha e sera adicionado um ponto e virgula
            // nos demais abaixo sera feito a mesma coisa
            fprintf(cars, "%s", placa[i]);
            fprintf(cars, ";");

            //modelo
            fprintf(cars, "%s", modelo[i]);
            fprintf(cars, ";");

            //marca
            fprintf(cars, "%s", marca[i]);
            fprintf(cars, ";");

            //ano
            fprintf(cars, "%d", ano[i]);
            fprintf(cars, ";");

            //quilometragem
            fprintf(cars, "%d", quilometragem[i]);
            fprintf(cars, ";");

            //Aqui após escrever a ultima parte que seria da categoria é dado uma quebra de linha para ser escrito a proxima linha
            fprintf(cars, "%d\n", categoria[i]);
        }
    }
    fclose(cars);
}

void entrega()
{
    char nomePesquisa[20], data[20], dataentrega[20], placaPesquisa[50];
    int x, i;
    int categoriaPesquisa;
    int temp;
    char temp2[50];
    //int qtdDias;
    //float valor;

    //system ("cls");
    printf("\t=============================================================\n");
    printf("\t===================== Devolucao do veiculo ==================\n");
    printf("\t=============================================================\n\n");
    printf("\n Nome do cliente \n");
    scanf("%s", &nomePesquisa);

    for (x = 0; x < cliente; x++)
    {
        if (clienteDisponivel[x] == 0)
        {
            //Estrutura de decisão para comparar o nome salvo do cliente com o informado
            if (strcmp(nomePesquisa, nome[x]) == 0)
            {
                printf("\n Placa do veiculo: \n ");

                scanf("%s", &placaPesquisa);

                for (i = 0; i <= frota; i++)
                {
                    //Estrutura de decisão para comparar A placa do veiculo salvo com o informado
                    if (strcmp(placaPesquisa, placa[i]) == 0)
                    {
                        temp = i;
                        if (disponivel[i] == 0)
                        {
                            printf("\n  Data da devolucao: \n ");
                            scanf("%d/%d/%d", &dataEntrega.dia, &dataEntrega.mes, &dataEntrega.ano);
                            //É pego da variavel dataEntrega e armazenado dentro de uma variavel de temporaria
                            sprintf(temp2, "%d/%d/%d", dataEntrega);

                            //aqui é novamente passado da variavel temporaria para uma variavel que possa armazenar mais
                            //de uma data ou seja cada vez que é alocado um novo carro é introduzida dentro
                            //dessa variavel uma nova data proviniente daquela locação.
                            strcpy(dataEntregaCarro[i], temp2);

                            verificarPontos(temp, x);

                            printf("\nO cliente %s do CNH %d entregou o carro de placa %s de categoria %d com a quilometragem de %d KM, retirado na data de %s, entregue na data de %s", nome[x], cnh[x], placa[i], categoria[i], quilometragem[i], dataRetirada[i], dataEntregaCarro[i]);
                            frotaDisp++;
                            frotaLoc--;
                            clienteDisponivel[i] = 1;
                            disponivel[i] = 1;
                            break;
                        }
                        else
                        {
                            printf("Dados incorretos, verificar novamente.");
                            break;
                        }
                    }
                }
            }
        }
    }
}

void verificarPontos(int i, int x)
{
    int cate1 = 100;
    int cate2 = 200;
    int cate3 = 300;
    int valorlocacao;
    int kmexce;
    int valorkm = 10;
    int valorkm2 = 20;
    int valorkm3 = 30;
    int opcao;

    printf("\nDigite a quantidade de km percorridos:\n");
    scanf("%d", &kmexce);

    qtdDias = dist_dias(data, dataEntrega);
    printf("\nA quantidade de dias que foi realizada a locacao:  %d \n", qtdDias);
    //printf("\n Digite a quantidade de dias de locacao:\n");
    //scanf("%d", &qtdDias);

    if (categoria[i] == 1)
    {
        //Calculo do valor da locação somando as diárias (número de dias * valor da diária da categoria)
        //A quilometragem (Quilometragem excedente * valor do quilômetro da categoria)
        printf("\t======== O valor total da locacao - CATEGORIA 1 ========\n\n");
        valorlocacao = cate1 * qtdDias + kmexce * valorkm;
        printf("\n VALOR DA LOCACAO: %d \t\t ", valorlocacao);

        //mensagem verificação dos pontos
        printf("\t--->Resgatar os pontos 1 - sim, OUTRO NUMERO - nao. \n\n");
        scanf("%d", &opcao);
        if (opcao == 1)
        {
            pontos[x] += kmexce / 10;
            //x = x + 1;

            // if(pontos >= 1){
            printf("\t PONTOS FIDELIDADE: %d\t\t", pontos[x]);
            // }
        }
    }
    else if (categoria[i] == 2)
    {
        printf("\t======== O valor total da locacao - CATEGORIA 2 ========\n\n");
        valorlocacao = cate2 * qtdDias + kmexce * valorkm2;
        printf("\n VALOR DA LOCACAO: %d\t\t", valorlocacao);
        printf("\t---> Resgatar os pontos 1 - sim, OUTRO NUMERO - nao\n");
        scanf("%d", &opcao);
        if (opcao == 1)
        {
            pontos[x] += kmexce / 10;
            //x = x + 1;
            //  if(pontos >= 1){
            printf("\t PONTOS FIDELIDADE: %d\t\t", pontos[x]);
        }
        //  }
    }
    else if (categoria[i] == 3)
    {
        printf("\t======== O valor total da locacao - CATEGORIA 3 ========\n\n");
        valorlocacao = cate3 * qtdDias + kmexce * valorkm3;
        printf("\t VALOR DA LOCACAO: %d\t\t", valorlocacao);
        printf("\t ---> Resgatar os pontos 1 - sim, OUTRO NUMERO - nao.\n\n");
        scanf("%d", &opcao);
        if (opcao == 1)
        {
            pontos[x] += kmexce / 10;
            //x = x + 1;
            // if(pontos >= 1){
            printf("\n\n\n");
            printf("\t PONTOS FIDELIDADE: %d\t\t\n", pontos[x]);
            printf("\n\n\n");
            // }
        }
    }
}

void verificaSair()
{
    do
    {
        printf("\n\n\n");
        printf("\t=============================================================\n");
        printf("\t==================== PROGRAMA FINALIZADO ====================\n");
        printf("\t=============================================================\n\n");
        printf("\n\n\n");
    } while (op == 1);
}
