#include <iostream>
using namespace std;

// ===== ESTRUTURA DE FILA =====
struct No {
    int senha;
    No* prox;
};

struct Fila {
    No* inicio;
    No* fim;
    int tamanho;

    Fila() {
        inicio = fim = nullptr;
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

    void listar() {
        No* atual = inicio;
        while (atual) {
            cout << atual->senha << " ";
            atual = atual->prox;
        }
        cout << endl;
    }
};

// ===== ESTRUTURA DE GUICHÊS EM LISTA =====
struct Guiche {
    int id;
    Fila senhasAtendidas;
    Guiche* prox;
};

struct ListaGuiches {
    Guiche* inicio;

    ListaGuiches() {
        inicio = nullptr;
    }

    void adicionarGuiche(int id) {
        Guiche* novo = new Guiche{id, Fila(), nullptr};
        novo->prox = inicio;
        inicio = novo;
        cout << "Guichê " << id << " aberto.\n";
    }

    Guiche* buscarGuiche(int id) {
        Guiche* atual = inicio;
        while (atual) {
            if (atual->id == id) return atual;
            atual = atual->prox;
        }
        return nullptr;
    }

    int contarGuiches() {
        int count = 0;
        Guiche* atual = inicio;
        while (atual) {
            count++;
            atual = atual->prox;
        }
        return count;
    }
};

// ===== MAIN =====
int main() {
    Fila senhasGeradas;
    ListaGuiches guiches;
    int opcao;
    int senhaAtual = 1;

    do {
        cout << "\n--- MENU DE ATENDIMENTO (PONTEIROS) ---\n";
        cout << "Senhas aguardando atendimento: " << senhasGeradas.tamanhoFila() << endl;
        cout << "Guichês abertos: " << guiches.contarGuiches() << endl;
        cout << "0. Sair\n1. Gerar senha\n2. Abrir guichê\n3. Realizar atendimento\n4. Listar senhas atendidas\nEscolha: ";
        cin >> opcao;

        switch (opcao) {
            case 1: // Gerar senha
                cout << "Senha gerada: " << senhaAtual << endl;
                senhasGeradas.enfileirar(senhaAtual++);
                break;

            case 2: { // Abrir guichê
                int idGuiche;
                cout << "Digite o ID do guichê a ser aberto: ";
                cin >> idGuiche;
                if (guiches.buscarGuiche(idGuiche)) {
                    cout << "Guichê já está aberto!\n";
                } else {
                    guiches.adicionarGuiche(idGuiche);
                }
                break;
            }

            case 3: { // Realizar atendimento
                int idGuiche;
                cout << "ID do guichê para atendimento: ";
                cin >> idGuiche;
                Guiche* g = guiches.buscarGuiche(idGuiche);
                if (!g) {
                    cout << "Guichê não encontrado.\n";
                } else if (senhasGeradas.vazia()) {
                    cout << "Nenhuma senha para atender.\n";
                } else {
                    int senha = senhasGeradas.desenfileirar();
                    g->senhasAtendidas.enfileirar(senha);
                    cout << "Guichê " << idGuiche << " atendeu a senha: " << senha << endl;
                }
                break;
            }

            case 4: { // Listar senhas atendidas
                int idGuiche;
                cout << "ID do guichê: ";
                cin >> idGuiche;
                Guiche* g = guiches.buscarGuiche(idGuiche);
                if (!g) {
                    cout << "Guichê não encontrado.\n";
                } else {
                    cout << "Senhas atendidas pelo guichê " << idGuiche << ": ";
                    g->senhasAtendidas.listar();
                }
                break;
            }

            case 0: // Sair
                if (!senhasGeradas.vazia()) {
                    cout << "Ainda há senhas a serem atendidas.\n";
                    opcao = -1; // Força o loop continuar
                } else {
                    int total = 0;
                    Guiche* atual = guiches.inicio;
                    while (atual) {
                        total += atual->senhasAtendidas.tamanhoFila();
                        atual = atual->prox;
                    }
                    cout << "\nTotal de senhas atendidas: " << total << endl;
                }
                break;

            default:
                cout << "Opção inválida!\n";
        }

    } while (opcao != 0);

    return 0;
}
