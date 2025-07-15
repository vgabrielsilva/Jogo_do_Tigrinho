
#include "biblioteca.h"

int main() {
    cout << "BEM-VINDO AO JOGO DO TIGRINHO\n\n";

    Jogador* jogador = new Jogador();
    inicializarJogo(jogador);

    int opcao;
    do {
        system("cls");

        cout << "\nMENU\n";
        cout << "1. Ver dinheiro\n";
        cout << "2. Ver estatisticas\n";
        cout << "3. Jogar\n";
        cout << "4. Sair\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                mostrarDinheiro(jogador);
                cout << "Pressione Enter para continuar...";
                cin.ignore();
                cin.get();
                break;

            case 2:
                mostrarEstatisticas(jogador);
                cout << "Pressione Enter para continuar...";
                cin.ignore();
                cin.get();
                break;

            case 3: {
                mostrarDinheiro(jogador);
                cout << "Quanto voce quer apostar? R$";
                int aposta;
                cin >> aposta;

                if (aposta > 0) {
                    jogar(jogador, aposta);
                    salvarDados(jogador);
                } else {
                    cout << "Aposta invalida!\n";
                    cout << "Pressione Enter para continuar...";
                    cin.ignore();
                    cin.get();
                }
                break;
            }

            case 4:
                cout << "Obrigado por jogar!\n";
                mostrarEstatisticas(jogador);
                salvarDados(jogador);
                break;

            default:
                cout << "Opcao invalida!\n";
                cout << "Pressione Enter para continuar...";
                cin.ignore();
                cin.get();
        }

    } while (opcao != 4);

    finalizarJogo(jogador);
    delete jogador;

    return 0;
}
