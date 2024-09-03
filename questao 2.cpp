#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct No {
    char valor;
    No* prox;

    No(char _valor) {
        valor = _valor;
        prox = nullptr;  // Corre��o: usar nullptr ao inv�s de NULL
    }
};

struct Pilha {
    No* topo;
    int n;

    Pilha() {
        topo = nullptr;  // Corre��o: usar nullptr
        n = 0;
    }

    void inserir(char valor) {
        No* novo = new No(valor);
        novo->prox = topo;
        topo = novo;
        n++;
    }

    void remover() {
        if (n == 0) return;
        No* aux = topo;
        topo = topo->prox;
        delete aux;
        n--;
    }

    char topoPilha() {
        if (topo == nullptr) return 0;  // Corre��o: usar nullptr
        return topo->valor;
    }

    bool vazio() {
        return n == 0;
    }
};

int main() {
    Pilha p;
    char linha[101];
    int numLinha = 0;
    int linhaErro = 0;  // Para armazenar a linha onde o erro foi detectado
    bool esperaChave = false;  // Para verificar se uma chave de abertura { era esperada

    while (true) {
        if (fgets(linha, 101, stdin) == nullptr) break;
        if (strncmp(linha, "***END***", 9) == 0) break;  // Corre��o: ajuste do valor para compara��o do tamanho correto
        numLinha++;

        // Verificar se a linha cont�m uma fun��o ou constru��o que requer chaves
        if (strstr(linha, "if") || strstr(linha, "else") || strstr(linha, "for") || strstr(linha, "while") || strstr(linha, "int main")) {
            esperaChave = true;  // Espera uma chave de abertura na pr�xima linha ou na mesma
        }

        for (int i = 0; i < strlen(linha); i++) {
            if (linha[i] == '(' || linha[i] == '{') {
                p.inserir(linha[i]);
                if (linha[i] == '{') esperaChave = false;  // Se uma chave de abertura foi encontrada, n�o precisa mais esperar
            } else if (linha[i] == ')') {
                if (p.vazio() || p.topoPilha() != '(') {
                    linhaErro = numLinha;
                }
                if (!p.vazio()) p.remover();
            } else if (linha[i] == '}') {
                if (p.vazio() || p.topoPilha() != '{') {
                    linhaErro = numLinha;
                }
                if (!p.vazio()) p.remover();
            }
        }

        // Se uma chave de abertura era esperada mas n�o foi encontrada na linha atual
        if (esperaChave && linhaErro == 0 && p.vazio()) {
            linhaErro = numLinha;  // Detecta que deveria haver uma chave, mas n�o houve
        }
    }

    // Verifica��o final ap�s a leitura de todas as linhas
    if (linhaErro > 0) {
        printf("%d\n", linhaErro);  // Imprime a linha do erro se houver
    } else if (!p.vazio()) {
        printf("%d\n", numLinha);  // Imprime a �ltima linha se h� par�nteses/chaves abertos
    } else {
        printf("OK\n");  // Imprime "OK" se n�o houver erros
    }

    return 0;
}
