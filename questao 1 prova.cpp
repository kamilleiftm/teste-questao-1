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

    printf("Quantos n�meros voc� deseja converter? ");
    scanf("%d", &qtdNumeros);

    int numeros[qtdNumeros];  // Array para armazenar os n�meros

    // Recebe todos os n�meros
    for (int i = 0; i < qtdNumeros; i++) {
        printf("Digite o n�mero %d: ", i + 1);
        scanf("%d", &numeros[i]);
    }

    Pilha p;

    // Processa cada n�mero e imprime sua representa��o bin�ria
    for (int i = 0; i < qtdNumeros; i++) {
        int num = numeros[i];

        // Converte o n�mero atual para bin�rio e empilha os restos
        while (num > 0) {
            int resto = num % 2;
            p.inserir(resto);  // Insere o resto (0 ou 1) na pilha
            num = num / 2;     // Divide o n�mero por 2
        }

        // Desempilha e imprime os d�gitos bin�rios
        printf("N�mero %d em bin�rio: ", numeros[i]);
        if (!p.temElementos()) {
            printf("0");
        }
        while (p.temElementos()) {
            printf("%d", p.topoPilha());
            p.remover();
        }
        printf("\n");

        // Limpa a pilha para o pr�ximo n�mero
        p.limpar();
    }

    printf("Convers�o finalizada.\n");
    return 0;
}
