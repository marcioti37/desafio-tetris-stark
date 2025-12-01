#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 50

// ------------------- STRUCTS -------------------

typedef struct {
    char nome[30];
} Peca;

typedef struct {
    Peca fila[TAM];
    int inicio;
    int fim;
    int quantidade;
} Fila;

typedef struct {
    Peca pilha[TAM];
    int topo;
} Pilha;

// ------------------- FILA -------------------

void inicializarFila(Fila* f) {
    f->inicio = 0;
    f->fim = 0;
    f->quantidade = 0;
}

int filaVazia(Fila* f) {
    return f->quantidade == 0;
}

int filaCheia(Fila* f) {
    return f->quantidade == TAM;
}

void enfileirar(Fila* f, char nome[]) {
    if (filaCheia(f)) {
        printf("Fila cheia! Nao e possivel adicionar.\n");
        return;
    }
    strcpy(f->fila[f->fim].nome, nome);
    f->fim = (f->fim + 1) % TAM;
    f->quantidade++;
}

Peca desenfileirar(Fila* f) {
    Peca removida;
    strcpy(removida.nome, "vazia");

    if (filaVazia(f)) {
        printf("Fila vazia!\n");
        return removida;
    }

    removida = f->fila[f->inicio];
    f->inicio = (f->inicio + 1) % TAM;
    f->quantidade--;
    return removida;
}

void mostrarFila(Fila* f) {
    printf("\n--- Fila de Pecas Futuras ---\n");
    if (filaVazia(f)) {
        printf("Fila vazia.\n");
        return;
    }

    int idx = f->inicio;
    for (int i = 0; i < f->quantidade; i++) {
        printf("%d - %s\n", i, f->fila[idx].nome);
        idx = (idx + 1) % TAM;
    }
}

// ------------------- PILHA -------------------

void inicializarPilha(Pilha* p) {
    p->topo = -1;
}

int pilhaVazia(Pilha* p) {
    return p->topo == -1;
}

int pilhaCheia(Pilha* p) {
    return p->topo == TAM - 1;
}

void empilhar(Pilha* p, char nome[]) {
    if (pilhaCheia(p)) {
        printf("Pilha cheia! Nao e possivel reservar.\n");
        return;
    }
    p->topo++;
    strcpy(p->pilha[p->topo].nome, nome);
}

Peca desempilhar(Pilha* p) {
    Peca removida;
    strcpy(removida.nome, "vazia");

    if (pilhaVazia(p)) {
        printf("Pilha vazia!\n");
        return removida;
    }

    removida = p->pilha[p->topo];
    p->topo--;
    return removida;
}

void mostrarPilha(Pilha* p) {
    printf("\n--- Pilha de Pecas Reservadas ---\n");
    if (pilhaVazia(p)) {
        printf("Pilha vazia.\n");
        return;
    }

    for (int i = p->topo; i >= 0; i--) {
        printf("%d - %s\n", i, p->pilha[i].nome);
    }
}

// ------------------- JOGO -------------------

void jogarPeca(Fila* f) {
    if (filaVazia(f)) {
        printf("Nao ha peca para jogar.\n");
        return;
    }
    Peca jogada = desenfileirar(f);
    printf("Voce jogou a peca: %s\n", jogada.nome);
}

void reservarPeca(Fila* f, Pilha* p) {
    if (filaVazia(f)) {
        printf("Nao ha peca para reservar.\n");
        return;
    }

    if (pilhaCheia(p)) {
        printf("Pilha cheia! Nao e possivel reservar.\n");
        return;
    }

    Peca reservada = desenfileirar(f);
    empilhar(p, reservada.nome);

    printf("Peca %s reservada com sucesso!\n", reservada.nome);
}

void recuperarPeca(Pilha* p, Fila* f) {
    if (pilhaVazia(p)) {
        printf("Nao ha peca reservada para recuperar.\n");
        return;
    }

    if (filaCheia(f)) {
        printf("Fila cheia! Nao e possivel colocar a peca de volta.\n");
        return;
    }

    Peca rec = desempilhar(p);
    enfileirar(f, rec.nome);

    printf("Peca %s recuperada para a fila!\n", rec.nome);
}

// ------------------- MAIN -------------------

int main() {

    Fila fila;
    Pilha pilha;

    inicializarFila(&fila);
    inicializarPilha(&pilha);

    int opcao;
    char nome[30];

    // Pre carregando algumas pecas iniciais
    enfileirar(&fila, "espada");
    enfileirar(&fila, "escudo");
    enfileirar(&fila, "machado");
    enfileirar(&fila, "arco");

    while (1) {
        printf("\n===== MENU =====\n");
        printf("1 - Adicionar nova peca na fila\n");
        printf("2 - Jogar peca da fila\n");
        printf("3 - Reservar peca para pilha\n");
        printf("4 - Recuperar peca da pilha para fila\n");
        printf("5 - Mostrar fila de pecas futuras\n");
        printf("6 - Mostrar pilha de pecas reservadas\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {

        case 1:
            printf("Nome da peca: ");
            scanf("%s", nome);
            enfileirar(&fila, nome);
            break;

        case 2:
            jogarPeca(&fila);
            break;

        case 3:
            reservarPeca(&fila, &pilha);
            break;

        case 4:
            recuperarPeca(&pilha, &fila);
            break;

        case 5:
            mostrarFila(&fila);
            break;

        case 6:
            mostrarPilha(&pilha);
            break;

        case 0:
            printf("Saindo...\n");
            return 0;

        default:
            printf("Opcao invalida!\n");
        }
    }

    return 0;
}
