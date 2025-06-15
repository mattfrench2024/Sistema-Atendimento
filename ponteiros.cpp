#include <iostream>
using namespace std;

struct No {
    int senha;
    No* prox;
};

struct Fila {
    No* inicio;
    No* fim;
    int tamanho;

    Fila() {
        inicio = nullptr;
        fim = nullptr;
        tamanho = 0;
    }

    void enfileirar(int senha) {
        No* novo = new No{senha, nullptr};
        if (!fim) {
            inicio = fim = novo;
        } else {
            fim->prox = novo;
            fim = novo;
        }
        tamanho++;
    }

    int desenfileirar() {
        if (!inicio) return -1;
        No* temp = inicio;
        int valor = temp->senha;
        inicio = inicio->prox;
        if (!inicio) fim = nullptr;
        delete temp;
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
    Fila senhasGeradas;
    Fila senhasAtendidas;
    int opcao;
    int senhaAtual = 1;

    do {
        cout << "\n--- MENU DE ATENDIMENTO (PONTEIROS) ---\n";
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
