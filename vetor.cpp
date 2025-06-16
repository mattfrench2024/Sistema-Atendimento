#include <iostream>
using namespace std;

const int MAX = 100;

struct FilaVetor {
    int dados[MAX];
    int inicio, fim, tamanho;

    FilaVetor() {
        inicio = fim = tamanho = 0;
    }

    void enfileirar(int valor) {
        if (tamanho < MAX) {
            dados[fim] = valor;
            fim = (fim + 1) % MAX;
            tamanho++;
        } else {
            cout << "Fila cheia!\n";
        }
    }

    int desenfileirar() {
        if (tamanho == 0) return -1;
        int valor = dados[inicio];
        inicio = (inicio + 1) % MAX;
        tamanho--;
        return valor;
    }

    bool vazia() {
        return tamanho == 0;
    }

    int tamanhoFila() {
        return tamanho;
    }
};

int main() {
    FilaVetor senhasGeradas;
    FilaVetor senhasAtendidas;
    int opcao;
    int senhaAtual = 1;

    do {
        cout << "\n--- MENU DE ATENDIMENTO (VETORES) ---\n";
        cout << "Senhas aguardando atendimento: " << senhasGeradas.tamanhoFila() << "\n";
        cout << "0. Sair\n1. Gerar senha\n2. Realizar atendimento\nEscolha: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                cout << "Senha gerada: " << senhaAtual << endl;
                senhasGeradas.enfileirar(senhaAtual++);
                break;
            case 2:
                if (!senhasGeradas.vazia()) {
                    int atendida = senhasGeradas.desenfileirar();
                    cout << "Atendendo senha: " << atendida << endl;
                    senhasAtendidas.enfileirar(atendida);
                } else {
                    cout << "Nenhuma senha para atender.\n";
                }
                break;
            case 0:
                if (!senhasGeradas.vazia()) {
                    cout << "Ainda há senhas a serem atendidas.\n";
                    opcao = -1;
                }
                break;
            default:
                cout << "Opção inválida!\n";
        }

    } while (opcao != 0);

    cout << "\nTotal de senhas atendidas: " << senhasAtendidas.tamanhoFila() << endl;
    return 0;
}
