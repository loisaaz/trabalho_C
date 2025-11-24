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
    int quantidade; // max 10;
    struct Pessoa v_pessoa[10]; // vetor para pessoas que emprestaram - max 10
    int num; // contador de pessoas que realizaram empréstimos
};

// Estrutura que contém todos os dados da biblioteca
struct Biblioteca {
    struct Livro v_livros[100]; // vetor de uma estrutura do tipo livro
    int livros; // contador para quantidade de livros cadastrados
};

// Função para cadastrar livro
void cad(struct Biblioteca *b) {
    if (b->livros > 100)
    {
        printf("\n\t\tO limite de livros cadastrados foi atingido.\n");
        return;
    }

    struct Livro livro; // criando um tipo para cadastrar um livro

    // Inserir dados do livro
    printf("\n\t\tTítulo: ");
    scanf(" %[^\n]", livro.titulo);

    printf("\n\t\tAutor: ");
    scanf(" %[^\n]", livro.autor);

    printf("\n\t\tAno de publicação: ");
    scanf("%d", &livro.anopublicado);

    printf("\n\t\tID do livro: ");
    scanf("%d", &livro.id);

    // Verificar se o ID já existe
    for (int i = 0; i < b->livros; i++)
    {
        if (b->v_livros[i].id == livro.id)
        {
            printf("\t\tERRO! ID já existente para outro livro!\n");
                
            printf("\n\t\tInsira um ID não cadastrado: ");
            scanf("%d", &livro.id);
            i = -1;
        }
    }
    
    printf("\n\t\tQuantidade de exemplares: ");
    scanf("%d", &livro.quantidade); // maximo = 10
    
    if (livro.quantidade > 10 || livro.quantidade < 0)
    {
        printf("\n\t\tERRO! A quantidade deve estar entre 0 e 10.\n");
        while(livro.quantidade > 10 || livro.quantidade < 0){
            printf("\n\t\tInsira uma quantidade de válida: ");
            scanf("%d", &livro.quantidade);
        }   
    }

    // Inicializando o contador de empréstimos
    livro.num = 0;

    // Adicionando o livro à biblioteca
    b->v_livros[b->livros] = livro;
    b->livros++;

    printf("\n\t\tLivro cadastrado com sucesso!\n");
}

// Função para consulta de livros
void consultar(struct Biblioteca *b){
    int escolha;
    struct Livro livro;
    
    printf("\n\t\t1. VIZUALIZAR TODOS OS LIVROS CADASTRADOS\n\t\t2. BUSCAR LIVRO PELO ID\n\t\tOpção: ");
    scanf("%d", &escolha);

    if (escolha == 1){
        if (b->livros == 0) {
            printf("\n\t\t\tNão há livros cadastrados na biblioteca.\n");
            return;
        }

        printf("\n\t\t--- LISTA DE LIVROS ---\n");

        for(int i = 0; i < b->livros; i++)
        {
            printf("\t\tLIVRO: %s | AUTOR: %s | ANO de publicação: %d | ID: %d | EXEMPLARES: %d\n", b->v_livros[i].titulo, b->v_livros[i].autor, b->v_livros[i].anopublicado, b->v_livros[i].id, b->v_livros[i].quantidade);
        }

    }
    else if (escolha == 2){
        int idlivro;

        printf("\t\tDIGITE O ID: ");
        scanf("%d", &idlivro);
        
        for (int i = 0; i < b->livros; i++) {
            
            if(b->v_livros[i].id == idlivro){
                
                printf("\t\tLIVRO: %s | AUTOR: %s | ANO de publicação: %d | ID: %d | EXEMPLARES: %d\n", b->v_livros[i].titulo, b->v_livros[i].autor, b->v_livros[i].anopublicado, b->v_livros[i].id, b->v_livros[i].quantidade);
                return;
            }
        }
        printf("\n\t\tID não localizado.\n");
    }
    else{
        printf("\n\t\tOpção inválida!");
    }
}

// Função para registro de empréstimo
void emprestimo(struct Biblioteca *b)
{
    int idlivro;
    struct Pessoa p;

    printf("\t\tDIGITE O ID: ");
    scanf("%d", &idlivro);

    // Loop para procurar o livro no vetor de livros
    for (int i = 0; i < b->livros; i++)
    {
        // Verifica se encontrou o livro pelo ID
        if (b->v_livros[i].id == idlivro)
        {
            // 1. Verifica disponibilidade do exemplares
            if(b->v_livros[i].quantidade > 0)
            {
                printf("\t\tDIGITE O NOME DE QUEM VAI EMPRESTAR: ");
                scanf(" %[^\n]", p.nome);
                printf("\t\tDIGITE O CPF: ");
                scanf(" %ld", &p.cpf);

                for(int j = 0; j < b->v_livros[i].num; j++){
                    if(b->v_livros[i].v_pessoa[j].cpf == p.cpf){
                        printf("\nERRO: Esta pessoa ja possui um exemplar deste livro emprestado!\n");
                        return;
                    }
                }
                // 2. Registra o empréstimo
                int indice = b->v_livros[i].num;
                
                // Copia os dados da pessoa para dentro do vetor do livro
                b->v_livros[i].v_pessoa[indice] = p;
                
                // Atualiza contadores
                b->v_livros[i].num++; 

                // Diminui a qntd disponível dos exemplares do livro
                b->v_livros[i].quantidade--;   

                // Encerra a função pois já resolveu
                printf("\n\t\tEmpréstimo realizado com sucesso!\n");
                return; 
            }
            printf("\n\t\tSem exemplares disponíveis.\n");   
            return;  
        }
    }
    // Se o loop terminar e não tiver entrado, significa que não achou o ID
    printf("\n\t\tID não localizado.\n");
}

// Função para devolução de livros 
void devolucao(struct Biblioteca *b){
    int idlivro;
    long cpf;

    printf("\t\tDIGITE O ID DO LIVRO QUE SERÁ DEVOLVIDO: ");
    scanf("%d", &idlivro);

    // Loop para procurar o livro no vetor de livros
    for (int i = 0; i < b->livros; i++)
    {
        // Verifica se encontrou o livro pelo ID
        if (b->v_livros[i].id == idlivro){

            printf("\t\tDIGITE O CPF DE QUEM IRÁ DEVOLVER: ");
            scanf("%ld", &cpf);

            for (int j = 0; j < b->v_livros[i].num; j++){

                if(b->v_livros[i].v_pessoa[j].cpf == cpf){

                    for(int k = j; k < b->v_livros[i].num - 1; k++){
                        b->v_livros[i].v_pessoa[k] = b->v_livros[i].v_pessoa[k + 1];
                    }
                    // aumenta a qntd disponível dos exemplares do livro
                    b->v_livros[i].quantidade++;

                    // Atualiza o numero de pessoas que fizeram emprestimo
                    b->v_livros[i].num--;
                    printf("\n\t\tDevolução realizada!");
                    return;
                }
            }
            printf("\n\t\tERRO: CPF não localizado.\n");
            return;
        }     
    }
    printf("\n\t\tERRO: ID não localizado.\n");
}

//Funçao para remoção 
void remocao(struct Biblioteca *b){
    int idlivro;

    printf("\t\tDIGITE O ID DO LIVRO QUE SERÁ REMOVIDO: ");
    scanf("%d", &idlivro);

    for(int j = 0; j < b->livros; j++)
    {
        if(b->v_livros[j].id == idlivro){

            if (b->v_livros[j].num == 0){
                
                for (int i = j; i < b->livros - 1; i++){

                    b->v_livros[i] = b->v_livros[i + 1]; 
                }

                b->livros--;
                printf("\n\t\tLivro removido com sucesso!\n");
                return;
            }
            printf("\n\t\tERRO: Não é possível remover um livro que está emprestado.\n");
            return;
        }
    }
    printf("\n\t\tERRO: ID não localizado.\n");
}

int main()
{
    struct Biblioteca biblioteca; 
    // declaração da struct
    biblioteca.livros = 0; 
    // inicialização na contagem de livros na biblioteca
    
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
            case 1:
                cad(&biblioteca); 
                break;
            case 2:
                consultar(&biblioteca);
                break;

            case 3:
                emprestimo(&biblioteca);
                break;

            case 4:
                devolucao(&biblioteca);
                break;

            case 5:
                remocao(&biblioteca);
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