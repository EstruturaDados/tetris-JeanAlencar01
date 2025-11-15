#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.

typedef struct {
    char nome;
    int id;
} Peca;

typedef struct {
    Peca pecas[5];
    int inicio, fim, tamanho;
} Fila;

typedef struct {
    Peca pecas[3];
    int topo;
} Pilha;

typedef struct {
    Peca pecas[100];
    int topo;
} Historico;

void inicializarHistorico(Historico* historico) {
    historico->topo = -1;
}

void pushHistorico(Historico* historico, Peca peca) {
    historico->topo++;
    historico->pecas[historico->topo] = peca;
}

Peca popHistorico(Historico* historico) {
    Peca peca;
    if (historico->topo >= 0) {
        peca = historico->pecas[historico->topo];
        historico->topo--;
        return peca;
    } else {
        printf("Histórico vazio!\n");
        return peca;
    }
}

void trocarPecas(Fila* fila, Pilha* pilha) {
    if (fila->tamanho > 0 && pilha->topo >= 0) {
        Peca pecaFila = fila->pecas[fila->inicio];
        Peca pecaPilha = pilha->pecas[pilha->topo];
        fila->pecas[fila->inicio] = pecaPilha;
        pilha->pecas[pilha->topo] = pecaFila;
    } else {
        printf("Não é possível trocar peças!\n");
    }
}

void desfazerJogada(Fila* fila, Historico* historico) {
    if (historico->topo >= 0) {
        Peca peca = popHistorico(historico);
        inserirPeca(fila, peca);
    } else {
        printf("Nenhuma jogada para desfazer!\n");
    }
}

void inverterFila(Fila* fila) {
    int i = fila->inicio;
    int j = fila->fim;
    while (i != j) {
        Peca temp = fila->pecas[i];
        fila->pecas[i] = fila->pecas[j];
        fila->pecas[j] = temp;
        i = (i + 1) % 5;
        if (i == 0) {
            i = 4;
        }
        if (j == 0) {
            j = 4;
        } else {
            j--;
        }
    }
}

Peca gerarPeca(int id) {
    Peca p;
    char nomes[] = {'I', 'O', 'T', 'L', 'J', 'S', 'Z'};
    p.nome = nomes[rand() % 7];
    p.id = id;
    return p;
}

void inicializarPilha(Pilha* pilha) {
    pilha->topo = -1;
}

int pilhaVazia(Pilha* pilha) {
    return pilha->topo == -1;
}

int pilhaCheia(Pilha* pilha) {
    return pilha->topo == 2;
}

void push(Pilha* pilha, Peca peca) {
    if (!pilhaCheia(pilha)) {
        pilha->topo++;
        pilha->pecas[pilha->topo] = peca;
    } else {
        printf("Pilha cheia!\n");
    }
}

Peca pop(Pilha* pilha) {
    Peca peca;
    if (!pilhaVazia(pilha)) {
        peca = pilha->pecas[pilha->topo];
        pilha->topo--;
        return peca;
    } else {
        printf("Pilha vazia!\n");
        return peca; 
    }
}

void exibirPilha(Pilha* pilha) {
    printf("Pilha atual:\n");
    for (int i = pilha->topo; i >= 0; i--) {
        printf("Peca %d: %c\n", pilha->pecas[i].id, pilha->pecas[i].nome);
    }
}



void inicializarFila(Fila* fila) {
    fila->inicio = 0;
    fila->fim = 0;
    fila->tamanho = 0;
    for (int i = 0; i < 5; i++) {
        fila->pecas[i] = gerarPeca(i);
        fila->tamanho++;
    }
    fila->fim = fila->tamanho - 1;
}

void exibirFila(Fila* fila) {
    printf("Fila atual:\n");
    for (int i = fila->inicio; i != (fila->fim + 1) % 5; i = (i + 1) % 5) {
        printf("Peca %d: %c\n", fila->pecas[i].id, fila->pecas[i].nome);
    }
}

void jogarPeca(Fila* fila) {
    if (fila->tamanho > 0) {
        printf("Peca %d jogada: %c\n", fila->pecas[fila->inicio].id, fila->pecas[fila->inicio].nome);
        fila->inicio = (fila->inicio + 1) % 5;
        fila->tamanho--;
        fila->pecas[fila->fim].id = fila->pecas[(fila->fim + 1) % 5].id + 1;
        fila->pecas[fila->fim] = gerarPeca(fila->pecas[fila->fim].id);
    } else {
        printf("Fila vazia!\n");
    }
}

void inserirPeca(Fila* fila) {
    if (fila->tamanho < 5) {
        fila->pecas[fila->fim].id = fila->pecas[(fila->fim + 1) % 5].id + 1;
        fila->pecas[fila->fim] = gerarPeca(fila->pecas[fila->fim].id);
        fila->fim = (fila->fim + 1) % 5;
        fila->tamanho++;
    } else {
        printf("Fila cheia!\n");
    }
}

int main() {
    srand(time(NULL));
     Fila fila;
    Pilha pilha;
    Historico historico;
    inicializarFila(&fila);
    inicializarPilha(&pilha);
    inicializarHistorico(&historico);
    int opcao;
    do {
    printf("Menu:\n");
    printf("1 Exibir fila\n");
    printf("2 Jogar peça\n");
    printf("3 Reservar peça\n");
    printf("4 Usar peça reservada\n");
    printf("5 Trocar peça da frente com topo da pilha\n");
    printf("6 Trocar 3 primeiros da fila com os 3 da pilha\n");
    printf("7 Inserir peça\n");
    printf("8 Inversor fila\n");
    printf("0 Sair\n");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                if (fila.tamanho > 0) {
                    Peca peca = fila.pecas[fila.inicio];
                    pushHistorico(&historico, peca);
                    jogarPeca(&fila);
                } else {
                    printf("Fila vazia!\n");
                }
                break;
            case 2:
                if (!pilhaCheia(&pilha) && fila.tamanho > 0) {
                    Peca peca = fila.pecas[fila.inicio];
                    push(&pilha, peca);
                    jogarPeca(&fila);
                } else {
                    printf("Não é possível reservar a peça!\n");
                }
                break;
            case 3:
                if (!pilhaVazia(&pilha)) {
                    Peca peca = pop(&pilha);
                    printf("Peça %d usada: %c\n", peca.id, peca.nome);
                    inserirPeca(&fila);
                } else {
                    printf("Pilha vazia!\n");
                }
                break;
            case 4:
                if (fila.tamanho > 0 && pilha.topo >= 0) {
                    Peca pecaFila = fila.pecas[fila.inicio];
                    Peca pecaPilha = pilha.pecas[pilha.topo];
                    fila.pecas[fila.inicio] = pecaPilha;
                    pilha.pecas[pilha.topo] = pecaFila;
                    printf("Peças trocadas com sucesso!\n");
    } else {
                    printf("Não é possível trocar peças!\n");
    }
    break;
            case 5:
                if (pilha.topo == 2 && fila.tamanho >= 3) {
                    Peca temp[3];
                for (int i = 0; i < 3; i++) {
                    temp[i] = fila.pecas[(fila.inicio + i) % 5];
        }
                for (int i = 0; i < 3; i++) {
                    fila.pecas[(fila.inicio + i) % 5] = pilha.pecas[2 - i];
        }
                for (int i = 0; i < 3; i++) {
                    pilha.pecas[2 - i] = temp[i];
        }
        printf("Peças trocadas com sucesso!\n");
    } else {
        printf("Não é possível trocar peças!\n");
    }
    break;
            case 6:
                inverterFila(&fila);
                break;
        }
    } while (opcao != 0);
    return 0;
}
        
    // 🧩 Nível Novato: Fila de Peças Futuras
    //
    // - Crie uma struct Peca com os campos: tipo (char) e id (int).
    // - Implemente uma fila circular com capacidade para 5 peças.
    // - Crie funções como inicializarFila(), enqueue(), dequeue(), filaCheia(), filaVazia().
    // - Cada peça deve ser gerada automaticamente com um tipo aleatório e id sequencial.
    // - Exiba a fila após cada ação com uma função mostrarFila().
    // - Use um menu com opções como:
    //      1 - Jogar peça (remover da frente)
    //      0 - Sair
    // - A cada remoção, insira uma nova peça ao final da fila.



    // 🧠 Nível Aventureiro: Adição da Pilha de Reserva
    //
    // - Implemente uma pilha linear com capacidade para 3 peças.
    // - Crie funções como inicializarPilha(), push(), pop(), pilhaCheia(), pilhaVazia().
    // - Permita enviar uma peça da fila para a pilha (reserva).
    // - Crie um menu com opção:
    //      2 - Enviar peça da fila para a reserva (pilha)
    //      3 - Usar peça da reserva (remover do topo da pilha)
    // - Exiba a pilha junto com a fila após cada ação com mostrarPilha().
    // - Mantenha a fila sempre com 5 peças (repondo com gerarPeca()).


    // 🔄 Nível Mestre: Integração Estratégica entre Fila e Pilha
    //
    // - Implemente interações avançadas entre as estruturas:
    //      4 - Trocar a peça da frente da fila com o topo da pilha
    //      5 - Trocar os 3 primeiros da fila com as 3 peças da pilha
    // - Para a opção 4:
    //      Verifique se a fila não está vazia e a pilha tem ao menos 1 peça.
    //      Troque os elementos diretamente nos arrays.
    // - Para a opção 5:
    //      Verifique se a pilha tem exatamente 3 peças e a fila ao menos 3.
    //      Use a lógica de índice circular para acessar os primeiros da fila.
    // - Sempre valide as condições antes da troca e informe mensagens claras ao usuário.
    // - Use funções auxiliares, se quiser, para modularizar a lógica de troca.
    // - O menu deve ficar assim:
    //      4 - Trocar peça da frente com topo da pilha
    //      5 - Trocar 3 primeiros da fila com os 3 da pilha



    

