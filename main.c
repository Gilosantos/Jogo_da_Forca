#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>

const char Info[] = "Info.txt";
int jogoDupla = 0;
char Jogador1[30], Jogador2[30];
int pj1 = 0, pj2 = 0, sp1 = 1, sp2 = 0;

void apresentaJogo();
int menuInicial();
void infoJogo();
int menuSozinho();
void jogarSo(int menuSo);
void TelaDeJogo(char palavra[], int qtdLetras, char dica[]);
void voceErrou(char palavra[], int erros);
bool letrasPassadas(char letrasArriscadas[], int chuteLetra);
void voceAcertou(char palavra[], int erros);
void jogarDupla();
void montaBoneco(int erros);

int main()
{
    setlocale(LC_ALL,"Portuguese");

    int op, c, menuSo;

    do{
        apresentaJogo();
        op = menuInicial();

            switch(op)
            {
                case 1:
                    printf("\n\nSaindo do Jogo em...\n");
                        for (c = 3; c >= 1; c--){
                        printf("  %d\r", c);
                        Sleep(1000);}
                break;

                case 2:
                    jogarSo(menuSo = menuSozinho());
                break;

                case 3:
                    jogarDupla();
                break;

                case 4:
                    infoJogo();
                break;
            }
        system("cls");
    }while(op != 1);

    return 0;
}

void apresentaJogo()
{
    system("cls");
    printf("======================================================================================================================\n");
    printf("\n                                         J O G O   D A   F O R C A\n");
    printf("\n======================================================================================================================\n");
}

int menuInicial()
{
    int op;
    do{
    printf("\nEscolha uma das opções abaixo\n\n");
    printf("[1]- Sair do jogo\n");
    printf("[2]- Jogar \"SOZINHO\"\n");
    printf("[3]- Jogar \"EM DUPLA\"\n");
    printf("[4]- Ver informações sobre o jogo\n");
    printf("Sua opção: ");
    scanf("%d", &op);
        if((op < 1)||(op > 4)){
            printf("\nOpção INVÁLIDA!\7");
            Sleep(3000);
            apresentaJogo();
            }
    }while((op < 1)||(op > 4));
    return op;

}

void infoJogo()
{
    apresentaJogo();

    char textoInfo[51];
    FILE *info;

    info = fopen(Info, "r");

    if(info == NULL){
        printf("\nErro ao tentar abrir arquivo \"Info.txt\"\7");
        Sleep(3000);
    }
    else
    {
        while( (fgets(textoInfo, sizeof(textoInfo), info))!=NULL )
        printf("%s", textoInfo);
    }
    printf("\nDigite qualquer tecla para voltar ao menu:");
    fclose(info);
    getch();
}

int menuSozinho()
{
    int op;
    do{
    apresentaJogo();
    printf("\n\nOpção escolhida: jogar SOZINHO\n");
    printf("\nEscolha uma das áreas abaixo:\n");
    printf("[1]-História\n");
    printf("[2]-Geografia\n");
    printf("[3]-Ciências\n: ");
    scanf("%d", &op);
    if((op < 1)||(op > 3)){
        printf("Opção inválida!\7");
        Sleep(3000);
        }
    }while((op < 1)||(op > 3));
    return op;
}

void jogarSo(int menuSo)
{
    FILE *area;
    char nomeArquivo[14], carac, palavra[31], dica[51];
    int linhas = 1, sorteio, c = 0, qtdletras;

    switch(menuSo)
    {
    case 1:
        strcpy(nomeArquivo, "Historia.txt");
        strcpy(dica, "Personagem ou acontecimento historico");
        break;
    case 2:
        strcpy(nomeArquivo, "Geografia.txt");
        strcpy(dica, "Termo usado em geografia ou nome de um territorio");
        break;
    case 3:
        strcpy(nomeArquivo, "Ciencias.txt");
        strcpy(dica, "Termo cientifico ou nome de um cientista");
        break;
    }

    area = fopen(nomeArquivo, "r");

      if(area == NULL){
        printf("\nErro ao tentar abrir arquivo %s\7", nomeArquivo);
        Sleep(3000);
    }
    else
    {
        while((carac = fgetc(area))!= EOF )
            if(carac == '\n')
                linhas++;

        srand((unsigned)time(NULL) );
        sorteio = 1 + ( rand() % (linhas -1));

        fclose(area);
        area = fopen(nomeArquivo, "r");

        if(area == NULL){
            printf("\nErro ao tentar abrir arquivo %s\7", nomeArquivo);
            Sleep(3000);
            }
            else
            {
                linhas = 1;
                while(((carac = fgetc(area))!= EOF)||(linhas <= sorteio))
                {
                    if(carac == '\n')
                        linhas++;
                    else
                    {
                        if((linhas == sorteio)&&(carac != EOF))
                        {
                            palavra[c] = carac;
                            c++;
                        }
                    }

                }

            }
    }
    palavra [strlen(palavra)] = '\0';
    qtdletras = strlen(palavra);
    fclose(area);
    TelaDeJogo(palavra, qtdletras, dica);
}

void TelaDeJogo(char palavra[], int qtdletras, char dica[])
{
    int c, espaco = 0, erros = 0, op, acerto = 0, auxAcerto = 0;
    char *letrasArriscadas = (char*)malloc((qtdletras+6)*sizeof(char));
    int chuteLetra = 0;
    char *vetoraux = (char*)malloc(qtdletras*sizeof(char));
    bool letraJaFoi = false;
    char *palavraChute = (char*)malloc(qtdletras*sizeof(char));

    for(c =0; c < qtdletras; c++)
    {
        if(palavra[c] == ' ')
        {
            vetoraux[c] = '-';
            espaco++;
        }
        else
        {
            palavra[c] = toupper(palavra[c]);
            vetoraux[c] = '_';
        }
    }
    do{
    do{
    apresentaJogo();
    printf("\n\nDica: %s", dica);
    printf("\n\n      ");
    for(c = 0; c < qtdletras; c++)
            printf("%c ", vetoraux[c]);
    montaBoneco(erros);
    printf("\n\nQuantidade de letras na palavra: %d\n", qtdletras - espaco);
    printf("\nErros: %d", erros);
    printf("\nLetras arriscadas: ");
    for(c = 0; c < chuteLetra; c++)
        printf("%c ", letrasArriscadas[c]);
    printf("\n\nArriscar Letra ou Palavra?\n");
    printf("[1]-Arriscar letra\t[2]Arriscar palavra\n: ");
    scanf("%d", &op);
    if((op < 1)||(op > 2)){
        printf("OPÇÂO INVÁLIDA\7");
        Sleep(3000);
    }
    }while((op < 1)||(op > 2));
    if(op == 1)
    {
        do{
        printf("\nDigite a letra: ");
        fflush(stdin);
        letrasArriscadas[chuteLetra] = getc(stdin);
        letrasArriscadas[chuteLetra] = toupper(letrasArriscadas[chuteLetra]);
        if(chuteLetra>0){
            letraJaFoi = letrasPassadas(letrasArriscadas, chuteLetra);
        }
        }while(letraJaFoi);
        for(c = 0; c < qtdletras; c++)
        {
            if(palavra[c]==letrasArriscadas[chuteLetra])
            {
                vetoraux[c] = palavra[c];
                acerto++;
            }
        }
        if(acerto == auxAcerto){
        erros++;
        chuteLetra++;
        printf("\7");
        }
        else{
        auxAcerto = acerto;
        chuteLetra++;
        }
        if(erros == 6)
        voceErrou(palavra, erros);
        if((qtdletras - espaco)== acerto)
        voceAcertou(palavra, erros);
        }
    else
    {
       printf("\nDigite a palavra: ");
       fflush(stdin);
       gets(palavraChute);
       for(c = 0; c < qtdletras; c++)
       {
           palavraChute[c] = toupper(palavraChute[c]);
       }
       int comp = strcmp(palavraChute, palavra);
       if(comp == 0){
        acerto = (qtdletras - espaco);
        voceAcertou(palavra, erros);
        }
       else{
        erros += 6;
        voceErrou(palavra, erros);
        }
    }
    }while((erros <=5)&&((qtdletras - espaco)!= acerto));


}

void voceErrou(char palavra[], int erros)
{
    apresentaJogo();
    printf("\n\nVOCÊ NÂO ACERTOU A PALAVRA");
    printf("\nA palavra era....    ");
    puts(palavra);
    printf("\n\nPressione qualquer tecla para continuar");
    if(jogoDupla == 1){
        if(sp1 == 1)
            pj1++;
        else
            pj2++;
    }
    montaBoneco(erros);
    getch();
}
bool letrasPassadas(char letrasArriscadas[], int chuteLetra)
{
    int c;
            for(c = 0; c < chuteLetra; c++)
            {
                if(letrasArriscadas[chuteLetra] == letrasArriscadas[c])
                {
                    printf("\nVocê já chutou a letra %c\7", letrasArriscadas[chuteLetra]);
                    return true;
                }
            }
            return false;
}
void voceAcertou(char palavra[], int erros)
{
    apresentaJogo();
    printf("\n\nPARABÉNS! VOCÊ ACERTOU A PALAVRA... ");
    puts(palavra);
    printf("\n\nPressione qualquer tecla para continuar");
    if(jogoDupla == 1){
        if(sp1 == 1)
            pj2++;
        else
            pj1++;
    }
    montaBoneco(erros);
    getch();

}
void jogarDupla()
{
    char palavra[30], dica[50];
    int qtdletras, qtddica, contPartidas = 0, continua;
    jogoDupla = 1;

    apresentaJogo();
    printf("JOGADOR 1 - Digite seu nome: ");
    fflush(stdin);
    gets(Jogador1);
    printf("JOGADOR 2 - Digite seu nome: ");
    fflush(stdin);
    gets(Jogador2);

    do{
    if(sp1)
      printf("\n%s, escolha uma palavra para %s tentar acertar: ", Jogador1, Jogador2);
    else
        printf("\n%s, escolha uma palavra para %s tentar acertar: ", Jogador2, Jogador1);
    fflush(stdin);
    gets(palavra);
    qtdletras = strlen(palavra);
    printf("\nEscolha uma dica para seu oponente: ");
    fflush(stdin);
    gets(dica);
    TelaDeJogo(palavra, qtdletras, dica);

    sp1 = !sp1;
    sp2 = !sp2;
    contPartidas++;
    apresentaJogo();
    printf("\n========================\n");
    printf("          PLACAR\n");
    printf("\n========================\n");
    printf("%s: %d\n", Jogador1, pj1);
    printf("--------------------------\n");
    printf("%s: %d\n", Jogador2, pj2);
    printf("--------------------------\n");
    printf("Rodadas: %d\n", contPartidas);
    printf("...........................\n");
    do{
    printf("\nContinuar?\n[1]sim\t[0]não\n: ");
    scanf("%d", &continua);
    }while((continua != 1)&&(continua != 0));
    }while(continua == 1);
}

void montaBoneco(int erros)
{
    switch (erros)
    {
    case 0:
        printf("\n\n\n                                                      ==============|");
        printf("\n                                                      ||            |");
        printf("\n                                                      ||");
        printf("\n                                                      ||");
        printf("\n                                                      ||");
        printf("\n                                                      ||");
        printf("\n                                                      ||=");
        printf("\n                                                      ||==");
        printf("\n                                                      ||====");
        printf("\n                                                      ||======");
        break;
    case 1:
        printf("\n\n\n                                                      ==============|");
        printf("\n                                                      ||            |");
        printf("\n                                                      ||            O");
        printf("\n                                                      ||");
        printf("\n                                                      ||");
        printf("\n                                                      ||");
        printf("\n                                                      ||=");
        printf("\n                                                      ||==");
        printf("\n                                                      ||====");
        printf("\n                                                      ||======");
        break;
    case 2:
        printf("\n\n\n                                                      ==============|");
        printf("\n                                                      ||            |");
        printf("\n                                                      ||            O");
        printf("\n                                                      ||            |");
        printf("\n                                                      ||            |");
        printf("\n                                                      ||");
        printf("\n                                                      ||=");
        printf("\n                                                      ||==");
        printf("\n                                                      ||====");
        printf("\n                                                      ||======");
        break;
    case 3:
        printf("\n\n\n                                                      ==============|");
        printf("\n                                                      ||            |");
        printf("\n                                                      ||            O");
        printf("\n                                                      ||            |");
        printf("\n                                                      ||            |");
        printf("\n                                                      ||           /");
        printf("\n                                                      ||=");
        printf("\n                                                      ||==");
        printf("\n                                                      ||====");
        printf("\n                                                      ||======");
        break;
    case 4:
        printf("\n\n\n                                                      ==============|");
        printf("\n                                                      ||            |");
        printf("\n                                                      ||            O");
        printf("\n                                                      ||            |");
        printf("\n                                                      ||            |");
        printf("\n                                                      ||           / \\");
        printf("\n                                                      ||=");
        printf("\n                                                      ||==");
        printf("\n                                                      ||====");
        printf("\n                                                      ||======");
        break;
    case 5:
        printf("\n\n\n                                                      ==============|");
        printf("\n                                                      ||            |");
        printf("\n                                                      ||            O");
        printf("\n                                                      ||            |\\");
        printf("\n                                                      ||            |");
        printf("\n                                                      ||           / \\");
        printf("\n                                                      ||=");
        printf("\n                                                      ||==");
        printf("\n                                                      ||====");
        printf("\n                                                      ||======");
        break;
    case 6:
        printf("\n\n\n                                                      ==============|");
        printf("\n                                                      ||            |");
        printf("\n                                                      ||            O");
        printf("\n                                                      ||           /|\\");
        printf("\n                                                      ||            |");
        printf("\n                                                      ||           / \\");
        printf("\n                                                      ||=");
        printf("\n                                                      ||==");
        printf("\n                                                      ||====");
        printf("\n                                                      ||======");
        break;
    }
}
