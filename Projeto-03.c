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

#define MAX_C 100 + 2 // MAX_C é número máximo de caracteres que cada variável char pode ler.>

struct localizacao { // variaveis do endereço.
  char estado[MAX_C];
  char rua[MAX_C];
  char bairro[MAX_C];
  char cidade[MAX_C];
  char cep[11];
};

struct dados { // variaveis dos dados do cadastro.
  int id;
  char nome_completo[MAX_C];
  char email[MAX_C];
  char genero[MAX_C];
  double altura;
  bool vacina;
  struct localizacao end;
};

struct noLista { // variaveis da lista simples encadeada.
  struct noLista * prox;
  struct dados pessoa;
};
// declaração das funções 
struct noLista * verID(struct noLista * lista); // Função que verifica o ID.
struct noLista * editar(struct noLista * edit); // Função que edita um usuário
bool verificaVacina(bool vacina); // Função que verifica se a vacina é válida
char * verificaEmail(char * emailValidado); // Função que verifica se o email é valido
char * verificaGenero(char * generoValidado); // Função que verifica se o gênero é válido..
void cadastraUsuario(struct noLista ** lista, struct noLista * novoNo); // Função que cadastra um usuário.
void listaCadastro(struct noLista * imprimir); // Função que mostra uma lista com todos os usuários cadastrados.
void excluir(struct noLista ** lista, struct noLista * deletar); // Função que exclui um usuário.
void backupRestaurar(struct noLista * lista, struct noLista ** backup, struct noLista * novoNo); // Função que faz o backup de todos os cadastros e restaura.
double verificaAltura(double altura); // Função que verifica se a altura é válida

int main(void) {
  struct noLista * novoNo;
  struct noLista * lista = NULL;
  struct noLista * backup = NULL;
  struct noLista * deletar;
  struct noLista * edit;
  int menu;
  int bkp = 0;

  do {
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
    scanf("%d", & menu);
    system("cls");
    switch (menu) {
    case 1: // Cadastro de usuário.
      cadastraUsuario( & lista, novoNo);
      break;
    case 2: // Edição de usuário.
      edit = verID(lista);
      if (edit != NULL)
        edit = editar(edit);
      break;
    case 3: // Exclusão de usuário.
      deletar = verID(lista);
      if (deletar != NULL) {
        excluir( & lista, deletar);
      }
      break;
    case 4: // Lista de usuários cadastrados.
      listaCadastro(lista);
      break;
    case 5: // Backup dos cadastros.
      while (backup != NULL) {
        deletar = backup;
        backup = backup -> prox;
        free(deletar);
      }
      backupRestaurar(lista, & backup, novoNo);
      bkp++;
      break;
    case 6: // Restauração dos cadastros
      if (bkp > 0) {
        while (lista != NULL) {
          deletar = lista;
          lista = lista -> prox;
          free(deletar);
        }
        backupRestaurar(backup, & lista, novoNo);
      } else {
        printf("O backup não existe.\n");
        system("pause");
      }
      break;
    default:
      printf("Opção inválida.\n");
      system("pause");
      break;
    }
  } while (menu != 7);

  return 0;
}
void excluir(struct noLista ** lista, struct noLista * excluir) {
  struct noLista * ptr = * lista;
  if ( * lista == excluir) {
    * lista = excluir -> prox;
  } else {
    while (ptr -> prox != excluir) {
      ptr = ptr -> prox;
    }
    ptr -> prox = excluir -> prox;
  }
  free(excluir);
  system("pause");
  system("cls");
}

void listaCadastro(struct noLista * imprimir) {
  struct noLista * ptr = imprimir;
  while (ptr != NULL) {
    printf("ID: %d\n", ptr -> pessoa.id);
    printf("Nome: %s\n", ptr -> pessoa.nome_completo);
    printf("Email: %s\n", ptr -> pessoa.email);
    printf("Sexo: %s\n", ptr -> pessoa.genero);
    printf("Endereço: %s,\n", ptr -> pessoa.end.cep);
    printf("%s\n", ptr -> pessoa.end.bairro);
    printf("%s\n", ptr -> pessoa.end.cidade);
    printf("%s\n", ptr -> pessoa.end.estado);
    printf("5 - Altura: %.2lf metros\n", ptr -> pessoa.altura);
    ptr = ptr -> prox;
  }
  system("pause");
  system("cls");
}
void cadastraUsuario(struct noLista ** lista, struct noLista * novoNo) {

  novoNo = malloc(sizeof(struct noLista));
  novoNo -> pessoa.id = rand() % 1000; // Função que dá a semente para o cálculo da função rand().
  printf("ID: %d\n", novoNo -> pessoa.id);
  printf("Informe o seu nome completo: ");
  fflush(stdin);
  scanf("%s", novoNo -> pessoa.nome_completo);
  printf("Informe o seu email: ");
  scanf("%s", novoNo -> pessoa.email);
  printf("Informe o seu gênero. [\"Feminino\", \"Masculino\" ou \"Não Declarar\"]: ");
  scanf("%s", novoNo -> pessoa.genero);
  printf("Informe o endereço [CEP]: ");
  fflush(stdin);
  scanf("%s", novoNo -> pessoa.end.cep);
  printf("Informe o endereço [ESTADO]: ");
  fflush(stdin);
  scanf("%s", novoNo -> pessoa.end.estado);
  printf("Informe o endereço [CIDADE]: ");
  fflush(stdin);
  scanf("%s", novoNo -> pessoa.end.cidade);
  printf("Informe o endereço [BAIRRO]: ");
  fflush(stdin);
  scanf("%s", novoNo -> pessoa.end.bairro);
  printf("Informe a sua altura: ");
  scanf("%lf", novoNo -> pessoa.altura);
  printf("Você se vacinou? Escreva \"Sim\" ou \"Não\": ");
  novoNo -> prox = * lista;
  * lista = novoNo;
  system("pause");
  system("cls");
}
void backupRestaurar(struct noLista * lista, struct noLista ** backup, struct noLista * novoNo) {
  struct noLista * ptr = lista;

  while (ptr != NULL) {
    novoNo = (struct noLista * ) malloc(sizeof(struct noLista));
    * novoNo = * ptr;
    novoNo -> prox = * backup;
    * backup = novoNo;

    ptr = ptr -> prox;
  }
  system("pause");
}
struct noLista * verID(struct noLista * lista) {
  int id;
  struct noLista * ptr = lista;
  printf("Digite o seu ID: ");
  scanf("%d", & id);
  while (ptr != NULL) {
    if (ptr -> pessoa.id == id)
      return ptr;
    ptr = ptr -> prox;
  }
  printf("O ID Não existe \n");
  system("cls");
  return NULL;
}

struct noLista * editar(struct noLista * edit) {
  int exit, contador;

  do {
    printf("ID: %d\n", edit -> pessoa.id);
    printf("1-Nome\n");
    printf("2-Email\n");
    printf("3-Sexo\n");
    printf("4-Endereço\n");
    printf("5-Altura\n");
    printf("6-Vacina\n");
    printf("Digite a opção desejada: ");
    scanf("%d", & contador);
    switch (contador) {
    case 1:
      printf("Digite o seu nome:\n");
      fflush(stdin);
      scanf("%s", edit -> pessoa.nome_completo);
      break;
    case 2:
      printf("Digite o seu email: \n");
      scanf("%s", edit -> pessoa.email);
      break;
    case 3:
      printf("Informe o seu gênero. [\"Feminino\", \"Masculino\" ou \"Não Declarar\"]: ");
      scanf("%s", edit -> pessoa.genero);
      break;
    case 4:
      printf("Informe o endereço [CEP]: ");
      fflush(stdin);
      scanf("%s", edit -> pessoa.end.cep);
      printf("Informe o endereço [ESTADO]: ");
      fflush(stdin);
      scanf("%s", edit -> pessoa.end.estado);
      printf("Informe o endereço [CIDADE]: ");
      fflush(stdin);
      scanf("%s", edit -> pessoa.end.cidade);
      printf("Informe o endereço [BAIRRO]: ");
      fflush(stdin);
     scanf("%s", edit -> pessoa.end.bairro);
      break;
    case 5:
      printf("Informe a sua altura: ");
      scanf("%lf", edit -> pessoa.altura);
      break;
    case 6:
      printf("Você se vacinou? Escreva \"Sim\" ou \"Não\": ");
      gets(edit -> pessoa.vacina);
      break;
    }
    printf("\nDeseja editar mais?\n");
    printf("1. Sim\n");
    printf("2. Não\n");
    scanf("%d", & exit);
    system("cls");
  } while (exit == 1);
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