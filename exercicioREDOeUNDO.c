#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// estrutura do nó 
struct Node {
    char texto[100]; 
    struct Node* next;
};

// estrutura da pilha
struct Pilha {
    struct Node* top;
};

// inicializa uma pilha
struct Pilha* criarPilha() {
    struct Pilha* p = (struct Pilha*)malloc(sizeof(struct Pilha));
    p->top = NULL;
    return p;
}

// verificar se a pilha está vazia
int pilhaVazia(struct Pilha* p) {
    return p->top == NULL;
}

// empilha a string

void push(struct Pilha* p, const char* str) {

    struct Node* novoNo = (struct Node*)malloc(sizeof(struct Node));

    strcpy(novoNo->texto, str);

    novoNo->next = p->top;
    p->top = novoNo;
}

// desempilha e retorna str do topo
char* pop(struct Pilha* p) 
{
    if (pilhaVazia(p)) 
    {
        return NULL;
    }
    struct Node* temp = p->top;
    char* strRetorno = (char*)malloc(100 * sizeof(char));
    
    strcpy(strRetorno, temp->texto); 
    
    p->top = p->top->next;
    free(temp);
    return strRetorno;
}

// esvazia a pilha
void esvaziarPilha(struct Pilha* p) 
{
    while (!pilhaVazia(p)) 
    {
        char* str = pop(p);
        free(str);
    }
}

//recursiva que irá imprimir da base ate o topo
void imprimirRec(struct Node* no) 
{
    if (no == NULL) 
        return;

    imprimirRec(no->next);
    printf("%s ", no->texto); 
}

// imprime o texto (pilhaUNDO da base -> topo)
void imprimirTexto(struct Pilha* p) {
    if (pilhaVazia(p)) {
        printf("(texto vazio)");
    } 
    else {
        imprimirRec(p->top);
    }
    printf("\n");
}

// insere nova palavra
void inserirPalavra(struct Pilha* pilhaUNDO, struct Pilha* pilhaREDO) {
    char palavra[100];
    printf("Digite a palavra: ");
    scanf("%s", palavra);
    push(pilhaUNDO, palavra);
    esvaziarPilha(pilhaREDO);
    printf("Palavra '%s' adicionada!\n", palavra);
}

// desfaz última ação (UNDO)
void desfazer(struct Pilha* pilhaUNDO, struct Pilha* pilhaREDO) {
    if (pilhaVazia(pilhaUNDO)) {
        printf("Não há nada para desfazer!\n");
        return;
    }
    char* str = pop(pilhaUNDO);
    push(pilhaREDO, str);
    printf("Ação desfeita: '%s'\n", str);
    free(str);
}

// refaz última ação desfeita (REDO)
void refazer(struct Pilha* pilhaUNDO, struct Pilha* pilhaREDO) {
    if (pilhaVazia(pilhaREDO)) {
        printf("Não há nada para refazer!\n");
        return;
    }
    char* str = pop(pilhaREDO);
    push(pilhaUNDO, str);
    printf("Ação refeita: '%s'\n", str);
    free(str);
}

// libera memória das pilhas
void liberarPilha(struct Pilha* p) 
{
    esvaziarPilha(p);
    free(p);
}

int main() {
    
    struct Pilha* pilhaUNDO = criarPilha();
    struct Pilha* pilhaREDO = criarPilha();
    
    int opcao; 
    
    printf("EDITOR DE TEXTO COM UNDO/REDO\n");
    

    while (opcao != 5) {
        printf("\n--------------------------------\n");
        printf("\tDigite a opção desejada:\n");
        printf("\t1 - digitar nova palavra da frase\n"); // Era 0
        printf("\t2 - desfazer (Undo)\n");               // Era 1
        printf("\t3 - refazer (Redo)\n");               // Era 2
        printf("\t4 - imprimir a frase\n");             // Era 3
        printf("\t5 - sair\n");                         // Era 4
        printf("\n--------------------------------\n");
        printf("\topção: ");
        scanf("%d", &opcao);
        printf("\n--------------------------------\n");
        switch (opcao) {
            case 1: 
                inserirPalavra(pilhaUNDO, pilhaREDO);
                break;
            case 2: 
                desfazer(pilhaUNDO, pilhaREDO);
                break;
            case 3: 
                refazer(pilhaUNDO, pilhaREDO);
                break;
            case 4: 
                imprimirTexto(pilhaUNDO);
                break;
            case 5: 
                printf("encerrando programa...\n");
                break;
            default:
                printf("opção inválida.\n");
        }
    }

    liberarPilha(pilhaUNDO);
    liberarPilha(pilhaREDO);

    return 0;
}