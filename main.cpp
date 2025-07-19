#include "biblioteca.h"

int main() {
    setCor(COR_VERDE);
    cout << "***********************************\n";
    cout << "* BEM-VINDO AO JOGO DO TIGRINHO  *\n";
    cout << "***********************************\n\n";
    resetCor();

    Jogador* jogador = new Jogador();
    inicializarJogo(jogador);

    int opcao;
    do {
        system("cls");

        setCor(COR_AZUL);
        cout << "\n----- MENU -----\n";
        resetCor();
        cout << "1. Jogar\n";
        cout << "2. Ver dinheiro\n";
        cout << "3. Ver estatisticas\n";
        cout << "4. Sair\n";
        setCor(COR_AMARELA);
        cout << "Escolha uma opcao: ";
        resetCor();
        cin >> opcao;

        // correçao de problema com cin.get() [limpa o buffer do teclado]
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcao) {
            case 1:

                mostrarDinheiro(jogador);
                setCor(COR_AMARELA);
                cout << "Quanto voce quer apostar? R$";
                resetCor();
                int aposta;
                cin >> aposta;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                jogar(jogador, aposta);
                salvarDados(jogador);
                break;

            case 2:
                mostrarDinheiro(jogador);
                cout << "Pressione Enter para continuar...";
                cin.get();
                break;

            case 3: {
                mostrarEstatisticas(jogador);
                cout << "Pressione Enter para continuar...";
                cin.get();
                break;
            }

            case 4:
                setCor(COR_VERDE);
                cout << "Obrigado por jogar!\n";
                resetCor();
                mostrarEstatisticas(jogador);
                salvarDados(jogador);
                break;

            default:
                setCor(COR_VERMELHA);
                cout << "Opcao invalida! Escolha uma opcao de 1 a 4.\n";
                resetCor();
                cout << "Pressione Enter para continuar...";
                cin.get();
        }

    } while (opcao != 4);

    finalizarJogo(jogador);
    delete jogador;

    return 0;
}
