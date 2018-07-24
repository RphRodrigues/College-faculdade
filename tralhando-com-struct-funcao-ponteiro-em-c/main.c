/*
 *  Matéria: Tecnicas de programação              Professor: Vilson Berilli
 *
 *  Inicio do projeto:  05/05/2018                Versão: 1.0
 *
 *  Última atualização: 19/06/2018
 *
 */

//=====================BIBLIOTECAS AUXILIARES======================

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

//====================DEFINIÇÕES DE CONSTANTES=====================

#define cod_S8  2001
#define cod_S9  2002
#define cod_S10 2003
#define cod_Iphone6 1001
#define cod_Iphone9 1002
#define cod_IphoneX 1003
#define TOTAL_USUARIOS 10

//====================PROTÓTIPO DAS ESTRUTURAS=====================

struct _CATALOGO
{
    int  codigoProduto;
    int  quantidadeEstoque;
    char marca[10];
    char usuario[10];
    char nomeProduto[10];
    char *descricao;

};

typedef struct _USUARIOS
{
    char nick[10];
    char password[8];

} USUARIOS;

typedef struct CALCULO
{
    int s8;          int iphone6;
    int s9;          int iphone9;
    int s10;         int iphoneX;
    int samsung;     int apple;

} CALCULO;

//=================PROTÓTIPO DAS VARIÁVEIS GLOBAIS=================

    char usuarioLogado[10];     FILE *file;
    int numeroDeUsuarios = 0;   CALCULO calculo;
    int numeroDeProdutos = 0;   USUARIOS usuarios[TOTAL_USUARIOS];

//======================PROTÓTIPO DAS FUNÇÕES======================

    void login();
    void cabecalho();
    void getArquivoUsuario();
    void setArquivoUsuario();
    void ordenaBolha(struct _CATALOGO *p);
    void ordenaSequencial(struct _CATALOGO *p);
    void inicio(struct _CATALOGO *catalogo);
    void menuPrincipal(struct _CATALOGO *catalogo);
    void menuRelatorio(struct _CATALOGO *catalogo);
    void adicionarUsuario(struct _CATALOGO *catalogo);
    void setArquivoGeral(struct _CATALOGO* catalogo);
    void setArquivoInterno(struct _CATALOGO *catalogo);
    void voltarMenuPrincipal(struct _CATALOGO *catalogo);
    void voltarMenuRelatorio(struct _CATALOGO *catalogo);
    void buscarRelatorioGeral(struct _CATALOGO *catalogo);
    void verUsuariosCadastrados(struct _CATALOGO *catalogo);
    void buscarPorMarcas(struct _CATALOGO *catalogo, char m);
    void buscarProduto(struct _CATALOGO *catalogo, int *codigo);
    void setArquivoPorMarca(struct _CATALOGO *catalogo, char m);
    struct _CATALOGO *getArquivo(struct _CATALOGO *catalogo);
    struct _CATALOGO *adicinarProduto(struct _CATALOGO *catalogo);
    struct _CATALOGO *aloca_memoria(struct _CATALOGO *catalogo);
    CALCULO funcaoQuantidade(struct _CATALOGO *catalogo);

//=========================FUNÇÃO PRINCIPAL========================

int main()
{
    struct _CATALOGO *catalogo;

        catalogo = getArquivo(catalogo);
        inicio(catalogo);
        menuPrincipal(catalogo);

    return 0;
}

//=============DESENVOLVIMENTO DAS FUNÇÕES AUXILIARES==============

/*
 *  Função aloca_memoria: Quando chamada pela primeira vez, executa o
 *  comando else, alocando espaço na memória para um cadastro de produto.
 *  Quando chamada posteriomente, realoca memória para mais cadastros.
 *
 *  Paramentro: Recebe um ponteiro de struct _CATALOGO
 *
 *  Retorno: Retorna um ponteiro para a região de memória alocada.
 */
struct _CATALOGO *aloca_memoria(struct _CATALOGO *catalogo)
{
        if(numeroDeProdutos > 0)
        {
            catalogo = (struct _CATALOGO *) realloc(catalogo, (numeroDeProdutos+1) * sizeof(struct _CATALOGO));
            if(!catalogo){
                printf("*** ERRO AO REALOCAR MEMORIA ***\n");
                exit(2);
            }

        }else
        {
            catalogo = (struct _CATALOGO *) malloc( sizeof( struct _CATALOGO ) );
            if(!catalogo){
                printf("*** ERRO AO ALOCAR MEMORIA ***\n");
                exit(1);
            }
        }

    return (catalogo);
}

/*
 *  Função funcaoQuantidade: Calcula a quantidade de cada aparelho
 *  cadastrado.
 *
 *  Paramentro: Recebe um ponteiro de struct _CATALOGO
 *
 *  Retorno: Retorna uma struct _CALCULO com a quantidade de cada
 *  aparelho cadastrado.
 */
CALCULO funcaoQuantidade(struct _CATALOGO *catalogo)
{
    CALCULO quantidade;

    quantidade.s8 = 0;          quantidade.iphone6 = 0;
    quantidade.s9 = 0;          quantidade.iphone9 = 0;
    quantidade.s10 = 0;         quantidade.iphoneX = 0;
    quantidade.samsung = 0;     quantidade.apple = 0;

        for(int j = 0; j < numeroDeProdutos; j++)
        {
            if( strcmp(catalogo[j].marca, "SAMSUNG") == 0)
            {
                if(catalogo[j].codigoProduto == cod_S8)
                {
                    quantidade.s8 += catalogo[j].quantidadeEstoque;
                }
                else   if(catalogo[j].codigoProduto == cod_S9)
                        {
                            quantidade.s9 += catalogo[j].quantidadeEstoque;
                        }
                        else
                        {
                            quantidade.s10 += catalogo[j].quantidadeEstoque;
                        }

                quantidade.samsung += catalogo[j].quantidadeEstoque;
            }
            else
            {
                if(catalogo[j].codigoProduto == cod_Iphone6)
                {
                    quantidade.iphone6 += catalogo[j].quantidadeEstoque;
                }
                else   if(catalogo[j].codigoProduto == cod_Iphone9)
                        {
                            quantidade.iphone9 += catalogo[j].quantidadeEstoque;
                        }
                        else
                        {
                            quantidade.iphoneX += catalogo[j].quantidadeEstoque;
                        }

                quantidade.apple += catalogo[j].quantidadeEstoque;
            }
        }

    return quantidade;
}

/*
 *  Função buscarProduto: Testa se o código digitado pelo usuário
 *  é valido, após isso imprime na tela os produtos correspondentes
 *  ao código digitado.
 *
 *  Paramentros: Recebe um ponteiro de struct _CATALOGO, e um ponteiro int.
 *
 *  Retorno: Não retorna nada.
 */
void buscarProduto(struct _CATALOGO *catalogo, int *codigo)
{
    int posicao;
    int qtd = 0;
    int controle = 0;

        if( *codigo != cod_S8 && *codigo != cod_S9 && *codigo != cod_S10 &&
            *codigo != cod_Iphone6 && *codigo != cod_Iphone9 && *codigo != cod_IphoneX)
        {
            printf("\n\n *** CODIGO INSERIDO INVALIDO ***\n");
            voltarMenuPrincipal(catalogo);
        }
        else
        {
            for(int j = 0; j < numeroDeProdutos; j++)
            {
                if(catalogo[j].codigoProduto == *codigo)
                {
                    printf("\n- Marca: %s\n",               catalogo[j].marca);
                    printf("  Codigo: %i\n",                catalogo[j].codigoProduto);
                    printf("  Nome do produto: %s\n",       catalogo[j].nomeProduto);
                    printf("  Quantidade em estoque: %i\n", catalogo[j].quantidadeEstoque);
                    printf("  Descricao do produto: %s\n\n",catalogo[j].descricao);

                    qtd += catalogo[j].quantidadeEstoque;

                    posicao = j;

                    controle = 1;
                }
            }
            if(controle)
            {
                if( *codigo == cod_Iphone6 || *codigo == cod_Iphone9 || *codigo == cod_IphoneX )
                {
                    printf("=================================\n");
                    printf(" TOTAL DE APARELHOS %s: %d\n", catalogo[posicao].nomeProduto, qtd);
                    printf("=================================\n");
                }
                else
                {
                    printf("===========================\n");
                    printf(" TOTAL DE APARELHOS %s: %d\n", catalogo[posicao].nomeProduto, qtd);
                    printf("===========================\n");
                }
            }
            else
            {
                printf("\n *** PRODUTO NAO CADASTRADO ***\n");
            }
        }
        voltarMenuPrincipal(catalogo);
}

/*
 *  Função getArquivo: Aloca memória para o vetor de struct, lê o arquivo
 *  ArquivoInterno.txt e grava no vetor, realocando memória quantas vezes
 *  forem necessário.
 *
 *  Paramentro: Recebe um ponteiro de struct _CATALOGO.
 *
 *  Retorno: Retorna um ponteiro para o vetor já carregado.
 */
struct _CATALOGO *getArquivo(struct _CATALOGO *catalogo)
{
    catalogo = aloca_memoria(catalogo);

        file = fopen("simulaBancoDeDados_Produtos.txt", "a+");
        if(!file)
        {
            printf("\n *** ERRO AO ABRIR ARQUIVO ***\n\n");
            exit(1);
        }

        int k = 0;                          char c;
        int giraNum;                        char num[6];
        int giraFrase = 0;                  char frase[20];
        char descricao[100];

        c = getc(file);
        frase[giraFrase++] = c;

        while( !feof(file) )
        {
            if( strncmp(frase, "Codigo do produto: ", strlen("Codigo do produto: ") ) == 0 )
            {
                giraNum = 0;
                do {
                    c = getc(file);
                    num[giraNum++] = c;

                }while(c != '\n');

                num[giraNum-1] = '\0';
                sscanf(num, "%d", &catalogo[numeroDeProdutos].codigoProduto);
                giraFrase = 0;
            }
            if( strncmp(frase, "Nome do produto: ", strlen("Nome do produto: ") ) == 0 )
            {
                k = 0;
                while(c != '\n')
                {
                    c = getc(file);
                    catalogo[numeroDeProdutos].nomeProduto[k++] = c;
                }
                catalogo[numeroDeProdutos].nomeProduto[k-1] = '\0';
                giraFrase = 0;
            }
            if( strncmp(frase, "Marca: ", strlen("Marca: ") ) == 0 )
            {
                k = 0;
                for(  ; c != '\n';  ) {
                    c = getc(file);
                    catalogo[numeroDeProdutos].marca[k++] = c;
                }
                catalogo[numeroDeProdutos].marca[k-1] = '\0';
                giraFrase = 0;
            }
            if( strncmp(frase, "Quantidade em estoque: ", strlen("Quantidade em estoque: ") ) == 0 )
            {
                giraNum = 0;
                while(c != '\n')
                {
                    c = getc(file);
                    num[giraNum++] = c;
                }
                num[giraNum-1] = '\0';
                sscanf(num, "%d", &catalogo[numeroDeProdutos].quantidadeEstoque);
                giraFrase = 0;
            }
            if( strncmp(frase, "Descricao do produto: ", strlen("Descricao do produto: ") ) == 0 )
            {
                k = 0;
                while(c != '\n')
                {
                    c = getc(file);
                    descricao[k++] = c;
                }
                descricao[k-1] = '\0';

                catalogo[numeroDeProdutos].descricao = (char *) malloc( strlen(descricao) * sizeof(char ) );
                strcpy(catalogo[numeroDeProdutos].descricao, descricao);

                giraFrase = 0;
            }
            if(strncmp(frase, "Cadastrado por: ", strlen("Cadastrado por: ") ) == 0)
            {
                k = 0;
                while(c != '\n')
                {
                    c = getc(file);
                    catalogo[numeroDeProdutos].usuario[k++] = c;
                }
                catalogo[numeroDeProdutos].usuario[k-1] = '\0';
                giraFrase = 0;

                numeroDeProdutos++;

                c = getc(file);
                frase[giraFrase++] = c;

                catalogo = aloca_memoria(catalogo);
            }
            c = getc(file);
            frase[giraFrase++] = c;
        }
        fclose(file);

    return(catalogo);
}

/*
 *  Função setArquivoInterno: Grava cada elemento do vetor de struct no arquivo
 *  em tempo de execução, ou seja, quando um produto é adicionado ao vetor,
 *  tbm é gravado em um arquivo interno ao sistema. Esse é o arquivo que será
 *  lido pela função getArquivo().
 *
 *  Paramentro: Recebe um ponteiro de struct _CATALOGO.
 *
 *  Retorno: Não retorna nada.
 */
void setArquivoInterno(struct _CATALOGO *catalogo)
{
        file = fopen("simulaBancoDeDados_Produtos.txt", "a+");
        if( file == NULL)
        {
            printf("\n *** ERRO AO ABRIR ARQUIVO INTERNO ***\n\n");
            exit(1);
        }

        fprintf(file, "%s%i\n", "Codigo do produto: ",      catalogo->codigoProduto);
        fprintf(file, "%s%s\n", "Nome do produto: ",        catalogo->nomeProduto);
        fprintf(file, "%s%s\n", "Marca: ",                  catalogo->marca);
        fprintf(file, "%s%i\n", "Quantidade em estoque: ",  catalogo->quantidadeEstoque);
        fprintf(file, "%s%s\n", "Descricao do produto: ",   catalogo->descricao);
        fprintf(file, "%s%s\n", "Cadastrado por: ",         catalogo->usuario);

        fclose(file);
}

/*
 *  Função setArquivoGeral: Grava todo os elementos do vetor de struct
 *  em arquivo para o usuário.
 *
 *  Paramentro: Recebe um ponteiro de struct _CATALOGO.
 *
 *  Retorno: Não retorna nada.
 */
void setArquivoGeral(struct _CATALOGO *catalogo)
{
    char c;
    char nomeArquivo[15];
    int k = 0;

        printf(" \n ESCREVA O NOME PARA O ARQUIVO: ");
        while( ( c = getc(stdin) ) != '\n')
        {
            nomeArquivo[k++] = c;
        }
        nomeArquivo[k] = '\0';

        strcat(nomeArquivo, ".txt");

        file = fopen(nomeArquivo, "a+");
        if( file == NULL )
        {
            printf("\n *** ERRO AO ABRIR ARQUIVO %s ***\n\n", nomeArquivo);
            exit(1);
        }
        for(int j = 0; j < numeroDeProdutos; j++)
        {
            fprintf(file, "%s%i\n",   "Codigo do produto: ",      catalogo[j].codigoProduto);
            fprintf(file, "%s%s\n",   "Nome do produto: ",        catalogo[j].nomeProduto);
            fprintf(file, "%s%s\n",   "Marca: ",                  catalogo[j].marca);
            fprintf(file, "%s%i\n",   "Quantidade em estoque: ",  catalogo[j].quantidadeEstoque);
            fprintf(file, "%s%s\n",   "Descricao do produto: ",   catalogo[j].descricao);
            fprintf(file, "%s%s\n\n", "Cadastrado por: ",         catalogo[j].usuario);
        }

        calculo = funcaoQuantidade(catalogo);
        fprintf(file, "\n====================================\n" );
        fprintf(file, "%s%d\n" ," Quantidade de produtos Apple "  , calculo.apple);
        fprintf(file, "%s%d\n" ," Quantidade de produtos Samsung ", calculo.samsung);
        fprintf(file, "%s%d\n" ,"    Total de unidades "         , (calculo.samsung + calculo.apple) );
        fprintf(file, "====================================\n" );

        fclose(file);

        printf("\n *** ARQUIVO '%s' GRAVADO COM SUCESSO ***\n\n", nomeArquivo);

        voltarMenuRelatorio(catalogo);
}

/*
 *  Função setArquivoPorMarca: Grava todo os elementos da marca escolhida
 *  pelo usuário em arquivo txt.
 *
 *  Paramentro: Recebe um ponteiro de struct _CATALOGO, e uma variável
 *  tipo char com a marca escolhida pelo usuário.
 *
 *  Retorno: Não retorna nada.
 */
void setArquivoPorMarca(struct _CATALOGO *catalogo, char m)
{
    char c;
    char marca[10];
    char nomeArquivo[20];
    int k = 0;

            printf(" \n ESCREVA O NOME PARA O ARQUIVO: ");
            while( ( c = getc(stdin) ) != '\n')
            {
                nomeArquivo[k++] = c;
            }
            nomeArquivo[k] = '\0';

            strcat(nomeArquivo, ".txt");

            file = fopen(nomeArquivo, "w");
            if( file == NULL )
            {
                printf("\n *** ERRO AO ABRIR ARQUIVO %s ***\n\n", nomeArquivo);
                exit(1);
            }
            if(m == '1'){
                strcpy(marca, "SAMSUNG");
            }
            else{
                strcpy(marca, "APPLE");
            }

            int controle = 0;
            for(int j = 0; j < numeroDeProdutos; j++)
            {
                if( strcmp(catalogo[j].marca, marca) == 0)
                {
                    fprintf(file, "%s%i\n",   "Codigo do produto: ",    catalogo[j].codigoProduto);
                    fprintf(file, "%s%s\n",   "Nome do produto: ",      catalogo[j].nomeProduto);
                    fprintf(file, "%s%s\n",   "Marca: ",                catalogo[j].marca);
                    fprintf(file, "%s%i\n",   "Quantidade em estoque: ",catalogo[j].quantidadeEstoque);
                    fprintf(file, "%s%s\n",   "Descricao do produto: ", catalogo[j].descricao);
                    fprintf(file, "%s%s\n\n", "Cadastrado por: ",       catalogo[j].usuario);
                    controle = 1;
                }
            }

            calculo = funcaoQuantidade(catalogo);
            if(m == '1')
            {
                fprintf(file, "\n====================================\n" );
                fprintf(file, " %s%d\n" ,"Quantidade de Samsung S8: ",      calculo.s8);
                fprintf(file, " %s%d\n" ,"Quantidade de Samsung S9: ",      calculo.s9);
                fprintf(file, " %s%d\n" ,"Quantidade de Samsung s10: ",     calculo.s10);
                fprintf(file, " %s%d\n" ,"Quantidade de produtos Samsung: ",calculo.samsung);
                fprintf(file, "====================================\n" );
            }
            else
            {
                fprintf(file, "\n==================================\n" );
                fprintf(file, " %s%d\n" ,"Quantidade de Iphone 6: ",      calculo.iphone6);
                fprintf(file, " %s%d\n" ,"Quantidade de Iphone 9: ",      calculo.iphone9);
                fprintf(file, " %s%d\n" ,"Quantidade de Iphone X: ",      calculo.iphoneX);
                fprintf(file, " %s%d\n" ,"Quantidade de produtos Apple: ",calculo.apple);
                fprintf(file, "==================================\n" );
            }

            fclose(file);

            if(controle == 0){
                printf("\n *** NENHUM PRODUTO DA MARCA %s ENCONTRADO ***\n\n", marca);
            }else{
                printf("\n *** ARQUIVO '%s' GRAVADO COM SUCESSO ***\n\n", nomeArquivo);
            }

            voltarMenuRelatorio(catalogo);
}


/*
 *  Função ordenaBolha: Ordena em ordem crescente o vetor de struct
 *  utilizando o método bubble sort.
 *
 *  Paramentro: Recebe um vetor de struct _CATALOGO
 *
 *  Retorno: Não retorna nada.
 */
void ordenaBolha(struct _CATALOGO *p)
{
    int controle;
    struct _CATALOGO temp;
        do
        {
            controle = 0;
            for(int j = 0; j < (numeroDeProdutos-1); j++)
            {
                if(p[j].quantidadeEstoque > p[j+1].quantidadeEstoque)
                {
                    temp = p[j+1];
                    p[j+1] = p[j];
                    p[j] = temp;
                    controle = 1;
                }
            }
        }while(controle);
}

/*
 *  Função ordenaSequencial: Ordena em ordem decrescente o vetor de struct
 *  utilizando o método sequencial.
 *
 *  Paramentro: Recebe um vetor de struct _CATALOGO
 *
 *  Retorno: Não retorna nada.
 */
void ordenaSequencial(struct _CATALOGO *p)
{
    struct _CATALOGO temp;
        for(int i = 0; i < (numeroDeProdutos - 1); i++)
        {
            for(int j = (i+1); j < numeroDeProdutos; j++)
            {
                if (p[i].quantidadeEstoque < p[j].quantidadeEstoque)
                {
                    temp = p[i];
                    p[i] = p[j];
                    p[j] = temp;
                }
            }
        }
}
/*
 *  Função menuRelatorio: Exibi um menu ao usuário com opções
 *  para gerar relatório geral e por marca.
 *
 *  Paramentro: Recebe um ponteiro de struct _CATALOGO.
 *
 *  Retorno: Não retorna nada.
 */
void menuRelatorio(struct _CATALOGO *catalogo)
{
    char marca;
    char resposta;

        printf("====================================\n" );
        printf("         RELATORIO DE PRODUTOS\n");
        printf("====================================\n" );
        printf(" 1 - EMITIR RELATORIO GERAL \n");
        printf(" 2 - EMITIR RELATORIO POR MARCAS\n");
        printf(" 9 - VOLTAR\n");
        printf("====================================\n" );
        scanf("%c", &resposta);         getchar();
        if( (resposta < '1' || resposta > '2') && resposta != '9' )
        {
            printf("\n *** OPCAO INVALIDA ***\n\n");
            menuRelatorio(catalogo);
        }
        else
        {
            if(resposta == '1')
            {
                setArquivoGeral(catalogo);
            }
            else    if(resposta == '2')
                    {
 aqui:                  printf(" ESCOLHA A MARCA QUE DESEJA EMITIR RELATORIO\n");
                        printf("================\n");
                        printf("  1 - SAMSUNG\n");
                        printf("  2 - APPLE\n");
                        printf("================\n");
                        scanf("%c", &marca);    getchar();
                        if(marca < '1' || marca > '2')
                        {
                            printf("\n *** OPCAO INVALIDA ***\n\n");
                            goto aqui;
                        }
                        setArquivoPorMarca(catalogo, marca);
                    }
                    else
                    {
                        menuPrincipal(catalogo);
                    }
        }
}

/*
 *  Função buscarPorMarcas: Busca no vetor de struct a marca escolhi pelo
 *  usuário e imprimi na tela.
 *
 *  Paramentro: Recebe um ponteiro de struct _CATALOGO, e uma variável
 *  tipo char com a marca escolhida pelo usuário.
 *
 *  Retorno: Não retorna nada.
 */
void buscarPorMarcas(struct _CATALOGO *catalogo, char m)
{
    char marca[10];
    int controle = 0;

        if(m == '1'){
            strcpy(marca, "SAMSUNG");
        }
        else{
            strcpy(marca, "APPLE");
        }
        for(int j = 0; j < numeroDeProdutos; j++)
        {
            if( strcmp(catalogo[j].marca, marca) == 0 )
            {
                printf("\nCodigo do produto: %i\n",     catalogo[j].codigoProduto);
                printf("Nome do produto: %s\n",         catalogo[j].nomeProduto);
                printf("Marca: %s\n",                   catalogo[j].marca);
                printf("Quantidade em estoque: %i\n",   catalogo[j].quantidadeEstoque);
                printf("Descricao do produto: %s\n",    catalogo[j].descricao);
                printf("Cadastrado por: %s\n",          catalogo[j].usuario);
                controle = 1;
            }
        }

        calculo = funcaoQuantidade(catalogo);
        if(m == '1'){
            printf("\n====================================\n" );
            printf(" %s%d\n" ,"Quantidade de Samsung S8: ",      calculo.s8);
            printf(" %s%d\n" ,"Quantidade de Samsung S9: ",      calculo.s9);
            printf(" %s%d\n" ,"Quantidade de Samsung s10: ",     calculo.s10);
            printf(" %s%d\n" ,"Quantidade de produtos Samsung: ",calculo.samsung);
            printf("====================================\n" );
        }else{
            printf("\n===================================\n" );
            printf(" %s%d\n" ,"Quantidade de Iphone 6: ",      calculo.iphone6);
            printf(" %s%d\n" ,"Quantidade de Iphone 9: ",      calculo.iphone9);
            printf(" %s%d\n" ,"Quantidade de Iphone X: ",      calculo.iphoneX);
            printf(" %s%d\n" ,"Quantidade de produtos Apple: ",calculo.apple);
            printf("===================================\n" );
        }

        if(controle == 0){
            printf("\n\nNENHUM PRODUTO DA MARCA %s ENCONTRADO\n\n", marca);
        }
        voltarMenuPrincipal(catalogo);
}

/*
 *  Função adicionarUsuario: Cadastra um novo usuário para o programa,
 *  gerando login e senha.
 *
 *  Paramentro: Recebe um ponteiro de struct _CATALOGO, pois essa função
 *  pode chamar a função voltarMenuPrincipal() que pede um ponteiro de
 *  struct _CATALOGO.
 *
 *  Retorno: Não retorna nada.
 */
void adicionarUsuario(struct _CATALOGO *catalogo)
{
    char nomeUsuario[10];
    char senhaUsuario[10];

        printf("====================================\n" );
        printf("         CADASTRO DE USUARIO\n");
        printf("====================================\n" );
        printf("Insira nome de usuario: ");
        scanf("%s", nomeUsuario);               getchar();

        for(int i = 0; i < numeroDeUsuarios; i++)
        {
            if( strcmp (usuarios[i].nick, nomeUsuario) == 0)
            {
                printf("\n *** NOME DE USUARIO JA CADASTRADO *** \n\n");
                adicionarUsuario(catalogo);
            }
        }

        strcpy(usuarios[numeroDeUsuarios].nick, nomeUsuario);
        printf("Escolha sua senha: ");
        scanf("%s", senhaUsuario);              getchar();
        strcpy(usuarios[numeroDeUsuarios++].password, senhaUsuario);

        setArquivoUsuario(usuarios);

        printf("\n *** USUARIO CADASTRADO COM SUCESSO ***\n\n");

        if(numeroDeUsuarios == 1){
            login();
        }else{
            voltarMenuPrincipal(catalogo);
        }
}

/*
 *  Função inicio: Verifica no arquivo de usuários se existe usuário
 *  cadastrado, caso não exista nenhum usuário cadastrado, chama a função
 *  adicionarUsuario().
 *
 *  Paramentro: Recebe um ponteiro de struct _CATALOGO.
 *
 *  Retorno: Não retorna nada.
 */
void inicio(struct _CATALOGO *catalogo)
{
    getArquivoUsuario();
        if(numeroDeUsuarios == 0)
        {
            cabecalho();
            printf("\n     NENHUM USUARIO CADASTRADO\n");
            printf("    PARA COMEÇAR, CRIE UM LOGIN\n\n");
            printf("\n Pressione qualquer tecla para continuar \n"); getchar();
            adicionarUsuario(catalogo);
        }
        else
        {
            login();
        }
}

/*
 *  Função login: Pede ao usuário que entre com seu login e senha, e
 *  valida os dados inseridos verificando no vetor no usuários.
 *
 *  Paramentro: Não recebe nada.
 *
 *  Retorno: Não retorna nada.
 */
void login()
{
    char usuarioDigitado[10];
    char senhaDigitada[5];
    int controle = 0;

        printf("====================================\n" );
        printf("         ACESSO AO SISTEMA\n");
        printf("====================================\n" );
        printf("     Usuario: ");
        scanf("%s", usuarioDigitado);       getchar();
        printf("     Senha: ");
        scanf("%s", senhaDigitada);         getchar();
        printf("====================================\n" );
        for(int i = 0; i < numeroDeUsuarios; i++)
        {
            if( strcmp(usuarios[i].nick, usuarioDigitado) == 0 &&
                strcmp(usuarios[i].password, senhaDigitada) == 0)
            {
                strcpy(usuarioLogado, usuarios[i].nick);
                cabecalho();
                controle = 1;
                break;
            }
        }

        if(controle == 0)
        {
            printf("\n *** USUARIO OU SENHA INVALIDO ***\n\n");
            login();
        }
}

/*
 *  Função voltarMenuPrincipal: Imprime na tela a opção do usuário
 *  voltar ao menu principal.
 *
 *  Paramentro: Recebe um ponteiro de struct _CATALOGO.
 *
 *  Retorno: Não retorna nada.
 */
void voltarMenuPrincipal(struct _CATALOGO *catalogo)
{
    char resp;
        printf("\n=============\n");
        printf(" 9 - VOLTAR\n");
        printf("=============\n");
        scanf("%c", &resp); getchar();
        if(resp == '9'){
            menuPrincipal(catalogo);
        }else{
            printf("\n *** OPCAO INVALIDA ***\n\n");
            voltarMenuPrincipal(catalogo);
        }
}

/*
 *  Função voltarMenuRelatorio: Imprime na tela a opção do usuário
 *  voltar ao menu de relatórios.
 *
 *  Paramentro: Recebe um ponteiro de struct _CATALOGO.
 *
 *  Retorno: Não retorna nada.
 */
void voltarMenuRelatorio(struct _CATALOGO *catalogo)
{
    char resp;
        printf("\n=============\n");
        printf(" 9 - VOLTAR\n");
        printf("=============\n");
        scanf("%c", &resp); getchar();
        if(resp == '9'){
            menuRelatorio(catalogo);
        }else{
            printf("\n *** OPCAO INVALIDA ***\n\n");
            voltarMenuRelatorio(catalogo);
        }
}

/*
 *  Função setArquivoUsuario: Grava de forma binária no arquivousuario.txt
 *  o vetor de usuários.
 *
 *  Paramentro: Não recebe nada.
 *
 *  Retorno: Não retorna nada.
 */
void setArquivoUsuario()
{
        file = fopen("simulaBancoDeDados_usuario.txt", "w+b");
        if(!file)
        {
            printf("\n ERRO AO ABRIR ARQUIVO USUARIO\n\n");
            return;
        }
        fwrite(&numeroDeUsuarios, sizeof(int), 1, file);
        fwrite(&usuarios, sizeof(USUARIOS), numeroDeUsuarios, file);

        fclose(file);
}

/*
 *  Função getArquivoUsuario: Lê o conteúdo no arquivo usuario.txt
 *  e grava no vetor de usuário.
 *
 *  Paramentro: Não recebe nada.
 *
 *  Retorno: Não retorna nada.
 */
void getArquivoUsuario()
{
        file = fopen("simulaBancoDeDados_usuario.txt", "a+b");
        if(!file)
        {
            printf("\n ERRO AO ABRIR ARQUIVO USUARIO\n\n");
            return;
        }
        fread(&numeroDeUsuarios, sizeof(int), 1, file);
        numeroDeUsuarios = fread(&usuarios, sizeof(USUARIOS), numeroDeUsuarios, file);

        fclose(file);
}

/*
 *  Função verUsuariosCadastrados: Imprime na tela a lista com todos
 *  os usuários cadastrados no sistema.
 *
 *  Paramentro: Recebe um ponteiro de struct _CATALOGO.
 *
 *  Retorno: Não retorna nada.
 */
void verUsuariosCadastrados(struct _CATALOGO *catalogo)
{
        printf("====================================\n" );
        printf("        USUARIOS CADASTRADOS \n");
        printf("====================================\n" );
        for(int i = 0; i < numeroDeUsuarios; i++)
        {
            printf("  - %s\n", usuarios[i].nick);
        }
        printf("\n");
        voltarMenuPrincipal(catalogo);
}

/*
 *  Função cabecalho: Imprime na tela uma mensagem de boas-vindas.
 *
 *  Paramentro: Não recebe nada.
 *
 *  Retorno: Não retorna nada.
 */
void cabecalho()
{
        printf("====================================\n" );
        printf("         BEM VINDO AO SISTEMA\n");
        printf("         XPT TELECOMUNICACOES\n");
        printf("====================================\n" );
}

/*
 *  Função menuPrincipal: Imprime na tela o menu principal
 *  do programa e chama as outras funções.
 *
 *  Paramentro: Recebe um ponteiro de struct _CATALOGO.
 *
 *  Retorno: Não retorna nada.
 */
void menuPrincipal(struct _CATALOGO *catalogo)
{
    char resp;
        printf("====================================\n" );
        printf("          MENU PRINCIPAL\n");
        printf("====================================\n" );
        printf("  1 - BUSCAR PRODUTO\n");
        printf("  2 - ADICIONAR PRODUTO\n");
        printf("  3 - ADICIONAR USUARIO\n");
        printf("  4 - VER USUARIOS CADASTRADOS\n");
        printf("  5 - EMITIR RELATORIOS\n");
        printf("  6 - DESLOGAR\n");
        printf("  9 - FECHAR\n");
        printf("====================================\n" );
        scanf("%c", &resp); getchar();
        if( (resp < '1' || resp > '6') && resp != '9')
        {
            printf("\n *** OPCAO INVALIDA ***\n\n");
            menuPrincipal(catalogo);
        }
        else
        {
            if(resp == '1')
            {
busca:          printf("\n====================================\n" );
                printf(" 1 - BUSCAR POR CODIGO\n");
                printf(" 2 - BUSCAR POR MARCA\n");
                printf(" 3 - BUSCAR TODOS OS PRODUTOS\n");
                printf(" 4 - BUSCAR POR ORDEM CRESCENTE DE QUANTIDADES\n");
                printf(" 5 - BUSCAR POR ORDEM DECRESCENTE DE QUANTIDADES\n");
                printf("====================================\n" );
                char c;
                c = getchar();      getchar();
                if(c < '1' || c > '5')
                {
                    printf("\n *** OPCAO INVALIDA ***\n\n");
                    goto busca;
                }
                else    if(c == '1')
                        {
                            int cod;
                            printf(" INFORME O CODIGO DO PRODUTO: ");
                            scanf("%d", &cod);      getchar();
                            buscarProduto(catalogo, &cod);
                        }
                        else    if(c == '2')
                                {
                                    char marca;
 aqui:                              printf(" ESCOLHA A MARCA QUE DESEJA BUSCAR\n");
                                    printf("================\n");
                                    printf("  1 - SAMSUNG\n");
                                    printf("  2 - APPLE\n");
                                    printf("================\n");
                                    scanf("%c", &marca);    getchar();
                                    if(marca < '1' || marca > '2')
                                    {
                                        printf("\n *** OPCAO INVALIDA ***\n\n");
                                        goto aqui;
                                    }
                                    buscarPorMarcas(catalogo, marca);
                                }
                                else    if(c == '3')
                                        {
                                            buscarRelatorioGeral(catalogo);
                                        }
                                        else    if(c == '4')
                                                {
                                                    struct _CATALOGO *p;
                                                    p = (struct _CATALOGO *) malloc( (numeroDeProdutos) * sizeof(struct _CATALOGO) );
                                                    for(int i = 0; i < numeroDeProdutos; i++) {
                                                        p[i] = catalogo[i];
                                                    }
                                                    ordenaBolha(p);
                                                    buscarRelatorioGeral(p);
                                                    free(p);
                                                }
                                                else
                                                {
                                                    struct _CATALOGO *pointer;
                                                    pointer = (struct _CATALOGO *) malloc( (numeroDeProdutos) * sizeof(struct _CATALOGO) );
                                                    for(int i = 0; i < numeroDeProdutos; i++) {
                                                        pointer[i] = catalogo[i];
                                                    }
                                                    ordenaSequencial(pointer);
                                                    buscarRelatorioGeral(pointer);
                                                    free(pointer);
                                                }
            }
            else    if(resp == '2')
                    {
                        catalogo = adicinarProduto(catalogo);
                        menuPrincipal(catalogo);
                    }
                    else    if(resp == '3')
                            {
                                adicionarUsuario(catalogo);
                                menuPrincipal(catalogo);
                            }
                            else   if(resp == '4')
                                    {
                                        verUsuariosCadastrados(catalogo);
                                    }
                                    else   if(resp == '5')
                                            {
                                                menuRelatorio(catalogo);
                                            }
                                            else   if(resp == '6')
                                                    {
                                                        login();
                                                        menuPrincipal(catalogo);
                                                    }
                                                    else
                                                    {
                                                        for(int i = (numeroDeProdutos - 1); i >= 0; i--) {
                                                            free(catalogo[i].descricao);
                                                        }
                                                        free(catalogo);
                                                        exit(1);
                                                    }
        }
}

/*
 *  Função adicinarProduto: Adiciona novos produtos ao vetor de struct.
 *  Quando chama a função aloca_memoria() realoca memória em tempo de execução,
 *  aumentando a "capacidade" do vetor de struct.
 *
 *  Paramentro: Recebe um ponteiro de struct _CATALOGO.
 *
 *  Retorno: Retorna o ponteiro com todos os produtos catalogados.
 */
struct _CATALOGO *adicinarProduto(struct _CATALOGO *catalogo)
{
    char descricao[100];
    int i = numeroDeProdutos;
        catalogo = aloca_memoria(catalogo);

            printf(" Nome do produto: \n");
            printf(" 1 - S8\t\t2 - S9\t\t3 - S10\n");
            printf(" 4 - IPHONE 6\t5 - IPHONE 9\t6 - IPHONE X\n");

            char C;
            C = getchar();           getchar();
            if(C < '1' || C > '6')
            {
                printf("\n *** OPCAO INVALIDA ***\n\n");
                adicinarProduto(catalogo);
            }
            else
            {
                if(C == '1')
                {
                    strcpy(catalogo[i].nomeProduto, "S8");
                    catalogo[i].codigoProduto = cod_S8;
                }
                else    if(C == '2')
                        {
                            strcpy(catalogo[i].nomeProduto, "S9");
                            catalogo[i].codigoProduto = cod_S9;
                        }
                        else    if(C == '3')
                                {
                                    strcpy(catalogo[i].nomeProduto, "S10");
                                    catalogo[i].codigoProduto = cod_S10;
                                }
                                else    if(C == '4')
                                        {
                                            strcpy(catalogo[i].nomeProduto, "IPHONE 6");
                                            catalogo[i].codigoProduto = cod_Iphone6;
                                        }
                                        else    if(C == '5')
                                                {
                                                    strcpy(catalogo[i].nomeProduto, "IPHONE 9");
                                                    catalogo[i].codigoProduto = cod_Iphone9;
                                                }
                                                else
                                                {
                                                    strcpy(catalogo[i].nomeProduto, "IPHONE X");
                                                    catalogo[i].codigoProduto = cod_IphoneX;
                                                }
            }

            if(C <= '3'){
                strcpy(catalogo[i].marca, "SAMSUNG");
            }
            else{
                strcpy(catalogo[i].marca, "APPLE");
            }

            printf(" Quantidade em estoque: ");
            scanf("%d", &catalogo[i].quantidadeEstoque);
            getchar();

            printf(" Insira uma descricao para o produto: ");
            fgets(descricao, 100-1, stdin);
            descricao[strlen(descricao)-1] = '\0';

            catalogo[i].descricao = (char *) malloc( strlen(descricao) * sizeof(char ) );
            strcpy(catalogo[i].descricao, descricao);

            for(int j = 0; catalogo[i].descricao[j] != '\0'; j++) {
                catalogo[i].descricao[j] = toupper(catalogo[i].descricao[j]);
            }

            strcpy(catalogo[i].usuario, usuarioLogado);

            setArquivoInterno(&catalogo[numeroDeProdutos++]);

            printf("\n\n *** PRODUTO CADASTRADO COM SUCESSO ***\n\n");

    return (catalogo);
}

/*
 *  Função buscarRelatorioGeral: Testa se o usuário logado é o usuário com login 'fsj'.
 *  Se for imprime na tela todos os produtos catalogados. Chamando a função funcaoQuantidade(),
 *  imprime um resumo da quantidade de aparelhos. Se não for, exibi uma mensagem ao usuário.
 *
 *  Paramentro: Recebe um ponteiro de struct _CATALOGO.
 *
 *  Retorno: Não retorna nada.
 */
void buscarRelatorioGeral(struct _CATALOGO *catalogo)
{
        if(strcmp(usuarioLogado, "fsj") == 0 )
        {
            if(numeroDeProdutos == 0)
            {
                printf("\n *** NAO HA PRODUTOS CATALOGADOS ***\n\n");
                return;
            }
            else
            {
                for(int j = 0; j < numeroDeProdutos; j++)
                {
                    printf("\nCodigo do produto: %i\n",     catalogo[j].codigoProduto);
                    printf("Nome do produto: %s\n",         catalogo[j].nomeProduto);
                    printf("Marca: %s\n",                   catalogo[j].marca);
                    printf("Quantidade em estoque: %i\n",   catalogo[j].quantidadeEstoque);
                    printf("Descricao do produto: %s\n",    catalogo[j].descricao);
                    printf("Cadastrado por: %s\n",          catalogo[j].usuario);
                }

                calculo = funcaoQuantidade(catalogo);
                printf("\n==================================");
                printf("\n Numeros de produtos Samsung %d\n",   calculo.samsung);
                printf("\n Numeros de produtos Apple %d\n",     calculo.apple);
                printf("\n    Total de unidades %d  \n",        (calculo.samsung + calculo.apple) );
                printf("==================================\n");
            }
            voltarMenuPrincipal(catalogo);
        }
        else
        {
            printf("\n *** Usuario '%s' nao tem acesso ao relatorio geral ***\n\n", usuarioLogado);
            voltarMenuPrincipal(catalogo);
        }
}
