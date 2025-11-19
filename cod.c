#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Estrutura para armazenar os dados da pessoa que emprestou
struct Pessoa { 
    char nome[90];
    long cpf;
};

// Estrutura para armazenar os dados de um livro 
struct Livro {
    char titulo[100];
    char autor[100];
    int anopublicado;
    int id;
    int quantidadedisponivel; // max 10;
    struct Pessoa v_emprestimos[10]; // vetor para pessoas que emprestaram - max 10
    int cont_emprestimos; // contador de pessoas que realizaram empréstimos
};

// Estrutura que contém todos os dados da biblioteca
struct Biblioteca {
    struct Livro v_livros[100];
    int cont_livros_cadastrados;
};

// Função para cadastrar livro
void cad(struct Biblioteca *b) {
    if (b->cont_livros_cadastrados >= 100)
    {
        printf("O limite de livros cadastrados foi atingido.\n");
        return;
    }

    struct Livro novo;

    // Inserir dados do livro
    printf("\tTítulo: ");
    scanf(" %[^\n]", novo.titulo);

    printf("\tAutor: ");
    scanf(" %[^\n]", novo.autor);

    printf("\tAno de publicação: ");
    scanf("%d", &novo.anopublicado);

    printf("\tID do livro: ");
    scanf("%d", &novo.id);

    // Verificar se o ID já existe
    for (int i = 0; i < b->cont_livros_cadastrados; i++)
    {
        if (b->v_livros[i].id == novo.id)
        {
            printf("\tERRO! ID já existente para outro livro!\n");
            return;
        }
    }
    
    printf("\tQuantidade de exemplares: ");
    scanf("%d", &novo.quantidadedisponivel); // max é 10
    
    if (novo.quantidadedisponivel > 10)
    {
        printf("\tERRO! quantidade de exemplares não pode ser maior que 10.\n");
        return;   
    }
    
    // Inicializando o contador de empréstimos
    novo.cont_emprestimos = 0;

    // Adicionando o livro à biblioteca
    b->v_livros[b->cont_livros_cadastrados] = novo;
    b->cont_livros_cadastrados++;

    printf("\tLivro cadastrado com sucesso!\n");
}

// Função para consulta de livros
void consultar(struct Biblioteca *b){
    int escolha;
    struct Livro livro;
    
    printf("\tSelecione 1 se deseja vizualizar todos os livros ou 2 para buscar um livro pelo seu ID: ");
    scanf("%d", &escolha);
    if (escolha == 1){
        printf("\n\t--- LISTA DE LIVROS ---\n");
        for(int i = 0; i < b->cont_livros_cadastrados; i++){
            printf("\tLivro %d: %s | Autor: %s | Ano de publicação: %d | ID do livro: %d\n", i+1, b->v_livros[i].titulo, b->v_livros[i].autor, b->v_livros[i].id);
            printf("===========================================================");
        }
    }
    else if (escolha == 2){
        int idlivro;
        int encontrado = 0;

        printf("\tDigite o ID do livro: ");
        scanf("%d", &idlivro);

        for (int i = 0; i < b->cont_livros_cadastrados; i++){
            if (b->v_livros[i].id == idlivro)
            {
                printf("\tLivro %d: Título: %s, Autor: %s, Ano de publicação: %d, ID do livro: %d", i+1, livro.titulo, livro.autor, livro.anopublicado, livro.id);
                return;
            }
            else{
                printf("\tCódigo não localizado na biblioteca.");
                return;
            }
        }
        
    }
}
int main()
{
    struct Biblioteca biblioteca; // declaração da struct
    biblioteca.cont_livros_cadastrados = 0; // inicialização
    
    int op = -1;
    while(op != 0)
    {
        printf("\n\tSISTEMA DE GERENCIAMENTO DE BIBLIOTECA\n\n");
        printf("\t\t1. Cadastro de livros\n");
        printf("\t\t2. Consulta de livros\n");
        printf("\t\t3. Empréstimo de livros\n");
        printf("\t\t4. Devolução de livros\n");
        printf("\t\t5. Remoção de livros\n");
        printf("\t\t6. Encerrar o programa\n");
        printf("\t\tOpção: ");
        scanf("%d", &op);
        
        switch(op)
        {
            /**/
            case 1:
                cad(biblioteca); 
                break;
            case 2:
                consultar(biblioteca);
                break;

            case 3:
                // Implementar o empréstimo de livros aqui
                break;

            case 4:
                // Implementar a devolução de livros aqui
                break;

            case 5:
                // Implementar a remoção de livros aqui
                break;

            case 6:
                printf("\tEncerrando o programa...\n");
                break;

            default:
                printf("\tOpção inválida! Tente novamente.\n");
        }
    }
    

    return 0;
}