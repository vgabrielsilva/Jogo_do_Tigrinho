
#include "biblioteca.h"

int main() {
    cout << "BEM-VINDO AO JOGO DO TIGRINHO - ANTONIOBETS\n\n";

    Jogador* jogador = new Jogador();
    inicializarJogo(jogador);

    int opcao;
    do {
        system("cls");
        cout << "\n--- MENU ---\n";
        cout << "1. Ver saldo\n";
        cout << "2. Ver as estatisticas\n";
        cout << "3. Jogar\n";
        cout << "4. Sair\n";
        // A FAZER: opçao de reiniciar o jogo? ou de mudar quanto começa de dinheiro?
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        // A FAZER: fazer verificação de letras e números
        // adicionar cin.fail() e cin.clear().

        switch (opcao) {
            case 1:
                mostrarDinheiro(jogador);
                cout << "Pressione Enter pra continuar...";
                cin.ignore();
                cin.get();
                break;

            case 2:
                mostrarEstatisticas(jogador);
                cout << "Pressione Enter pra continuar...";
                cin.ignore();
                cin.get();
                break;

            case 3: {
                mostrarDinheiro(jogador);
                cout << "Quanto vc quer apostar? R$";
                int aposta;
                cin >> aposta;

                // A FAZER: verificar número válido das apostas.
                if (aposta > 0) {
                    jogar(jogador, aposta);
                    salvarDados(jogador);
                } else {
                    cout << "Aposta invalida!\n";
                    cout << "Pressione Enter pra continua...";
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
                cout << "Opçao invalida!\n";
                cout << "Pressione Enter pra continua...";
                cin.ignore();
                cin.get();
        }

    } while (opcao != 4);

    finalizarJogo(jogador);
    delete jogador; // A FAZER: confirmar se essa linha ta deletando certinho o Jogador

    return 0;
}
