// Projeto 03 - Lista Simplesmente Encadeada
// Aluno: Ricardo Alves de Lima Júnior | Matrícula: UC20102577
// Aluno: Luiz Gustavo da Costa Gonçalves | Matrícula: UC20201242

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_C 100 + 2 // MAX_C é número máximo de caracteres que cada variável char pode ler.

typedef struct
{
    char rua[MAX_C];
    char bairro[MAX_C];
    char estado[MAX_C];
    char cidade[MAX_C];
    char cep[11];
} localizacao;

struct dados
{
    int id;
    char nome_completo[MAX_C];
    char email[MAX_C];
    char genero[MAX_C];
    localizacao endereco;
    double altura;
    bool vacina;
    struct dados *prox;
};

typedef struct dados *Lista;

void inicio(Lista *ptr);          // Função que inicia a lista como NULL.
void inserir(Lista *ptr);         // Função que insere um nó na lista.
void cadastraUsuario(Lista *ptr); // Função que cadastra um usuário.
// void editarUsuario(Lista *ptr);                    // Função que edita um usuário.
// void excluiUsuario(Lista *ptr);                    // Função que exclui um usuário.
void listaCadastro(Lista ptr); // Função que mostra uma lista com todos os usuários cadastrados.
// void backupCadastro(Lista *ptr, Lista *backup);    // Função que faz o backup de todos os cadastros.
// void restaurarCadastro(Lista *ptr, Lista *backup); // Função que restaura os cadastros a partir do backup.

// Funções de verificação:

void verificaNome(Lista *ptr);   // Função que verifica se o nome não é nulo.
void verificaEmail(Lista *ptr);  // Função que verifica se o email é valido.
void verificaGenero(Lista *ptr); // Função que verifica se o gênero é válido.
void verificaAltura(Lista *ptr); // Função que verifica se a altura é válida.
void verificaVacina(Lista *ptr); // Função que verifica se a vacina é válida.
// bool verificaID(Lista *ptr, int tmp); // Função que verifica se o ID existe.

// Outras funções:
// void preencheId(Lista *ptr, int tmp);       // Função que radomiza os IDs.
// int pegaPosicaoID(Lista *ptr);              // Função que pega a posição do ID no vetor de IDs.

int main()
{
    srand((int)time(0)); // Função que dá a semente para o cálculo da função rand().

    Lista pessoas;
    Lista backup;
    int quantidade_usuario;
    int menu;

    inicio(&pessoas);

    do
    {
        system("cls");
        printf("-----------------\n");
        printf("MENU:\n");
        printf("1 - CADASTRO\n");
        printf("2 - EDITAR CADASTRO\n");
        printf("3 - EXCLUIR CADASTRO\n");
        printf("4 - LISTA DE CADASTROS\n");
        printf("5 - BACKUP DE CADASTROS\n");
        printf("6 - RESTAURAÇÃO (Backup necessário)\n");
        printf("7 - SAIR\n");
        printf("Escolha: ");
        scanf("%d", &menu);
        system("cls");
        getchar();

        // codigo.usuario = pegaPosicaoID(&pessoas);

        switch (menu)
        {
        case 1: // Cadastro de usuário.
            inserir(&pessoas);
            quantidade_usuario++;
            break;
        case 2: // Edição de usuário.
            // editarUsuario(pessoas);
            break;
        case 3: // Exclusão de usuário.
            // excluiUsuario(pessoas);
            quantidade_usuario--;
            break;
        case 4: // Lista de usuários cadastrados.
            listaCadastro(pessoas);
            break;
        case 5: // Backup dos cadastros.
            // backupCadastro(pessoas, backup);
            break;
        case 6: // Restauração dos cadastros.
            // restaurarCadastro(pessoas, backup);
            break;
        default:
            printf("Opção inválida.\n");
            system("pause");
            break;
        }
    } while (menu != 7);
    return 0;
}
void inicio(Lista *ptr)
{
    *ptr = NULL;
}
void inserir(Lista *ptr)
{
    if (*ptr == NULL)
    {
        *ptr = (Lista)malloc(sizeof(Lista));
        if (*ptr == NULL)
            return;
        cadastraUsuario(&(*ptr));
        (*ptr)->prox = NULL;
    }
    else
        inserir(&(*ptr)->prox);
}
void cadastraUsuario(Lista *ptr)
{
    // preencheId(&(*ptr).usuario);
    // printf("O seu ID é \"%d\".\n\n", (*ptr)->id);

    printf("Informe o seu nome completo: ");
    fgets((*ptr)->nome_completo, MAX_C, stdin);
    verificaNome(&(*ptr));
    printf("Nome cadastrado com sucesso!\n\n");

    printf("Informe o seu email: ");
    fgets((*ptr)->email, MAX_C, stdin);
    verificaEmail(&(*ptr));
    printf("Email cadastrado com sucesso!\n\n");

    printf("Informe o seu gênero. [\"Feminino\", \"Masculino\" ou \"Não Declarar\"]: ");
    fgets((*ptr)->genero, MAX_C, stdin);
    verificaGenero(&(*ptr));
    printf("Gênero cadastrado com sucesso!\n\n");

    printf("Informe o endereço [CEP]: ");
    scanf("%[^\n]", (*ptr)->endereco.cep);
    getchar();
    printf("Informe o endereço [ESTADO]: ");
    scanf("%[^\n]", (*ptr)->endereco.estado);
    getchar();
    printf("Informe o endereço [CIDADE]: ");
    scanf("%[^\n]", (*ptr)->endereco.cidade);
    getchar();
    printf("Informe o endereço [BAIRRO]: ");
    scanf("%[^\n]", (*ptr)->endereco.bairro);
    getchar();
    printf("Informe o endereço [RUA]: ");
    scanf("%[^\n]", (*ptr)->endereco.rua);
    getchar();
    printf("Endereço cadastrado com sucesso!\n\n");

    printf("Informe a sua altura: ");
    scanf("%lf", &(*ptr)->altura);
    getchar();
    verificaAltura(&(*ptr));
    printf("Altura cadastrada com sucesso.\n\n");

    printf("Você se vacinou? Escreva \"Sim\" ou \"Não\": ");
    verificaVacina(&(*ptr));
    printf("Vacina cadastrada com sucesso!\n\n");

    system("pause");
}
void listaCadastro(Lista ptr)
{
    if (ptr == NULL)
        return; /* Não existem elementos */
    else
    {
        printf("ID: %d \n", ptr->id);
        printf("1 - Nome completo: %s", ptr->nome_completo);
        printf("2 - Email: %s", ptr->email);
        printf("3 - Gênero: %s", ptr->genero);
        printf("4 - Endereço: %s, ", ptr->endereco.cep);
        printf("%s ", ptr->endereco.rua);
        printf("%s, ", ptr->endereco.bairro);
        printf("%s - ", ptr->endereco.cidade);
        printf("%s\n", ptr->endereco.estado);
        printf("5 - Altura: %.2lf metros\n", ptr->altura);
        ((ptr->vacina == true) ? (printf("6 - Vacinado(a): Sim\n")) : (printf("6 - Vacinado(a): Não\n")));
        listaCadastro(ptr->prox); /* Lista os outros */
    }
}
void verificaNome(Lista *ptr)
{
    if (strcmp((*ptr)->nome_completo, "\n") == 0)
        do
        {
            system("cls");
            printf("O nome não pode ser nulo.\n");
            printf("Informe o seu nome completo: ");
            fgets((*ptr)->nome_completo, MAX_C, stdin);
        } while (strcmp((*ptr)->nome_completo, "\n") == 0);
}
void verificaEmail(Lista *ptr)
{
    if (strchr((*ptr)->email, '@') == NULL)
        do
        {
            system("cls");
            printf("O email deve conter um \"@\".\n");
            printf("Informe o seu email: ");
            fgets((*ptr)->email, MAX_C, stdin);
        } while (strchr((*ptr)->email, '@') == NULL);
}
void verificaGenero(Lista *ptr)
{
    for (int i = 0; i < strlen((*ptr)->genero); i++)
        (*ptr)->genero[i] = tolower((*ptr)->genero[i]);
    if (strcmp((*ptr)->genero, "masculino\n") == 0)
        strcpy((*ptr)->genero, "Masculino\n");
    else if (strcmp((*ptr)->genero, "feminino\n") == 0)
        strcpy((*ptr)->genero, "Feminino\n");
    else if (strcmp((*ptr)->genero, "não declarar\n") == 0 || strcmp((*ptr)->genero, "nÃo declarar\n") == 0)
        strcpy((*ptr)->genero, "Não declarado\n");
    else
    {
        system("cls");
        printf("O gênero deve ser Feminino, Masculino ou Não Declarar.\n");
        printf("Informe o seu gênero: ");
        fgets((*ptr)->genero, MAX_C, stdin);
        verificaGenero(&(*ptr));
    }
}
void verificaAltura(Lista *ptr)
{
    if (((*ptr)->altura) < 1 || (*ptr)->altura > 2)
        do
        {
            system("cls");
            printf("A altura deve ser entre 1 e 2 metros.\n");
            printf("Informe a sua altura: ");
            scanf("%lf", &(*ptr)->altura);
        } while ((*ptr)->altura < 1 || (*ptr)->altura > 2);
}
void verificaVacina(Lista *ptr)
{
    char aux[4 + 2];
    fgets(aux, 4 + 2, stdin);
    for (int i = 0; i < strlen(aux); i++)
        aux[i] = tolower(aux[i]);
    if (strcmp(aux, "sim\n") == 0)
        (*ptr)->vacina = true;
    else if (strcmp(aux, "não\n") == 0 || strcmp(aux, "nÃo\n") == 0)
        (*ptr)->vacina = false;
    else
    {
        if (strchr(aux, '\n') == NULL)
            while (getchar() != '\n')
                ;
        system("cls");
        printf("Você deve escrever apenas \"Sim\" ou \"Não\".\n");
        printf("Você se vacinou? ");
        verificaVacina(&(*ptr));
    }
}
/*bool verificaID(Lista *ptr, int tmp)
{
    //
}
void preencheId(Lista *ptr, int tmp)
{
    int numero_randomico;
    do
    {
        numero_randomico = (1 + rand());
    } while (verificaID(&(*ptr), numero_randomico) == true);
    (*ptr)->id = numero_randomico;
}
int pegaPosicaoID(Lista *ptr)
{
    int i = 0;
    while (*ptr != NULL)
        i++;
    return i;
}
*/
