
#include "biblioteca.h"

void inicializarJogo(Jogador* jogador, int dinheiro_inicial) {
    // A FAZER: aloca�ao dinamicamente dos dados do joagdor (precisa ver se ta tudo sendo alocado).
    jogador->dinheiro = new int(dinheiro_inicial);
    jogador->vitorias = new int(0);
    jogador->derrotas = new int(0);
    jogador->valor_ganho = new int(0);
    jogador->valor_perdido = new int(0);

    // A FAZER: [pablo vai alterar]
    jogador->num_simbolos = 3;
    jogador->simbolos = new string[jogador->num_simbolos];
    jogador->simbolos[0] = "| TIGRE |";
    jogador->simbolos[1] = "| CEREJA |";
    jogador->simbolos[2] = "| DIAMANTE |";

    srand(time(nullptr));

    // A FAZER: implementar o carrgamento dos dados, e verificar se o arquivo existe
    carregarDados(jogador);
}

void finalizarJogo(Jogador* jogador) {
    // A FAZER: liberar toda a memoria que usada
    delete jogador->dinheiro;
    delete jogador->vitorias;
    delete jogador->derrotas;
    delete jogador->valor_ganho;
    delete jogador->valor_perdido;
    delete[] jogador->simbolos;
    // A FAZER: Tem q apagar o "jogador" na main
}

void mostrarDinheiro(Jogador* jogador) {
    // A FAZER: ajustar a exibi��o do dinheiro
    cout << "Seu dinheiro: R$" << *(jogador->dinheiro) << endl;
}

void mostrarEstatisticas(Jogador* jogador) {
    cout << "\nESTATISTICAS\n";
    cout << "Dinheiro atual: R$" << *(jogador->dinheiro) << endl;
    cout << "Vitorias: " << *(jogador->vitorias) << endl;
    cout << "Derrotas: " << *(jogador->derrotas) << endl;
    cout << "Total ganho: R$" << *(jogador->valor_ganho) << endl;
    cout << "Total perdido: R$" << *(jogador->valor_perdido) << endl;
}

int sortearSimbolo(Jogador* jogador) {
    // Sugest�o: fazer com que o sorteio apare�a um simbolo mais que os outros
    return rand() % jogador->num_simbolos;
}

bool jogar(Jogador* jogador, int aposta) {
    if (aposta > *(jogador->dinheiro)) {
        cout << "Voce nao tem dinheiro suficiente!\n";
        cout << "Pressione Enter para continuar...";
        cin.ignore();
        cin.get();
        return false;
    }

    cout << "\nGIRANDO A ROLETA\n";

    int resultado[3];
    for (int i = 0; i < 3; i++) {
        resultado[i] = sortearSimbolo(jogador);
    }

    cout << "Resultado: ";
    for (int i = 0; i < 3; i++) {
        cout << jogador->simbolos[resultado[i]] << " ";
    }
    cout << endl;

    int chances = rand() % 100; // 0-99

    if (chances < 10) { // manipular a porcentagem de vit�ria
        int premio = aposta * 2;
        *(jogador->dinheiro) += premio;
        *(jogador->vitorias) += 1;
        *(jogador->valor_ganho) += premio;
        cout << "PARABENS! Voce ganhou R$" << premio << "!\n";
        // A FAZER: fazer uma "anima��o" pra vitoria
        cout << "Pressione Enter para continuar...";
        cin.ignore();
        cin.get();
        return true;
    } else {
        *(jogador->dinheiro) -= aposta;
        *(jogador->derrotas) += 1;
        *(jogador->valor_perdido) += aposta;
        cout << "Voce perdeu R$" << aposta << "!\n";
        cout << "Pressione Enter para continuar...";
        cin.ignore();
        cin.get();
        return false;
    }
}

void salvarDados(Jogador* jogador) {
    ofstream arquivo("dados.txt");
    if (arquivo.is_open()) {
        arquivo << *(jogador->dinheiro) << endl;
        arquivo << *(jogador->vitorias) << endl;
        arquivo << *(jogador->derrotas) << endl;
        arquivo << *(jogador->valor_ganho) << endl;
        arquivo << *(jogador->valor_perdido) << endl;
        arquivo.close();
    } else {
        cout << "ERRO: Nao rolou abri o arquivo pra salva os dados. Que bad!\n";
    }
}

void carregarDados(Jogador* jogador) {
    ifstream arquivo("dados.txt");
    if (arquivo.is_open()) {
        arquivo >> *(jogador->dinheiro);
        arquivo >> *(jogador->vitorias);
        arquivo >> *(jogador->derrotas);
        arquivo >> *(jogador->valor_ganho);
        arquivo >> *(jogador->valor_perdido);
        arquivo.close();
        // A FAZER: verificar se os dados carregados estao certos.
    }
}
