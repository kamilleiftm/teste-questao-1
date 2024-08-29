#include<stdio.h>

struct No {
    int valor;
    No* prox;

    No() {
        valor = 0;
        prox = NULL;
    }

    No(int _valor) {
        valor = _valor;
        prox = NULL;
    }
};

struct Pilha {
    No* topo;
    int n;

    Pilha() {
        topo = NULL;
        n = 0;
    }

    void inserir(int valor) {
        No* novo = new No(valor);
        if (topo == NULL) {
            topo = novo;
        } else {
            novo->prox = topo;
            topo = novo;
        }
        n++;
    }

    void remover() {
        if (n == 0) return;
        No* aux = topo;
        topo = topo->prox;
        delete(aux);
        n--;
    }

    int topoPilha() {
        if (topo == NULL) return 0;
        return topo->valor;
    }

    bool temElementos() {
        return n > 0;
    }

    void limpar() {
        while (temElementos()) {
            remover();
        }
    }
};

int main() {
    int qtdNumeros;

    printf("Quantos números você deseja converter? ");
    scanf("%d", &qtdNumeros);

    int numeros[qtdNumeros];  // Array para armazenar os números

    // Recebe todos os números
    for (int i = 0; i < qtdNumeros; i++) {
        printf("Digite o número %d: ", i + 1);
        scanf("%d", &numeros[i]);
    }

    Pilha p;

    // Processa cada número e imprime sua representação binária
    for (int i = 0; i < qtdNumeros; i++) {
        int num = numeros[i];

        // Converte o número atual para binário e empilha os restos
        while (num > 0) {
            int resto = num % 2;
            p.inserir(resto);  // Insere o resto (0 ou 1) na pilha
            num = num / 2;     // Divide o número por 2
        }

        // Desempilha e imprime os dígitos binários
        printf("Número %d em binário: ", numeros[i]);
        if (!p.temElementos()) {
            printf("0");
        }
        while (p.temElementos()) {
            printf("%d", p.topoPilha());
            p.remover();
        }
        printf("\n");

        // Limpa a pilha para o próximo número
        p.limpar();
    }

    printf("Conversão finalizada.\n");
    return 0;
}
