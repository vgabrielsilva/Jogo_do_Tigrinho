#include "biblioteca.h"

#define COR_VERDE 10
#define COR_VERMELHA 12
#define COR_AMARELA 14
#define COR_BRANCA 15
#define COR_AZUL 9


// setar as cores do terminal
void setCor(int cor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, cor);
}
void resetCor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, COR_BRANCA);
}


void inicializarJogo(Jogador* jogador, int dinheiro_inicial) {
    jogador->dinheiro = new int(dinheiro_inicial);
    jogador->vitorias = new int(0);
    jogador->derrotas = new int(0);
    jogador->valor_ganho = new int(0);
    jogador->valor_perdido = new int(0);
    jogador->vitorias_consecutivas = new int(0);

    jogador->num_simbolos = 3;
    jogador->simbolos = new string[jogador->num_simbolos];
    jogador->simbolos[0] = "| TIGRE |";
    jogador->simbolos[1] = "| CEREJA |";
    jogador->simbolos[2] = "| DIAMANTE |";

    srand(time(nullptr));

    carregarDados(jogador);
}

void finalizarJogo(Jogador* jogador) {
    delete jogador->dinheiro;
    delete jogador->vitorias;
    delete jogador->derrotas;
    delete jogador->valor_ganho;
    delete jogador->valor_perdido;
    delete jogador->vitorias_consecutivas;
    delete[] jogador->simbolos;
}

void mostrarDinheiro(Jogador* jogador) {
    setCor(COR_AMARELA);
    cout << "Seu dinheiro atual: R$" << *(jogador->dinheiro) << endl;
    resetCor();
}

void mostrarEstatisticas(Jogador* jogador) {
    setCor(COR_AZUL);
    cout << "\n--- ESTATISTICAS DO JOGADOR ---\n";
    cout << "Dinheiro atual: R$" << *(jogador->dinheiro) << endl;
    cout << "Vitorias: " << *(jogador->vitorias) << endl;
    cout << "Derrotas: " << *(jogador->derrotas) << endl;
    cout << "Total ganho: R$" << *(jogador->valor_ganho) << endl;
    cout << "Total perdido: R$" << *(jogador->valor_perdido) << endl;
    cout << "Vitorias consecutivas: " << *(jogador->vitorias_consecutivas) << endl;
    cout << "-------------------------------\n";
    resetCor();
}

int sortearSimbolo(Jogador* jogador) {
    return rand() % jogador->num_simbolos;
}

bool jogar(Jogador* jogador, int aposta) {
    if (aposta > *(jogador->dinheiro)) {
        setCor(COR_VERMELHA);
        cout << "Voce nao tem dinheiro suficiente para essa aposta! Seu dinheiro: R$" << *(jogador->dinheiro) << "\n";
        resetCor();
        cout << "Pressione Enter para continuar...";
        cin.ignore();
        cin.get();
        return false;
    }
    if (aposta <= 0) {
        setCor(COR_VERMELHA);
        cout << "Aposta invalida! A aposta deve ser um valor positivo.\n";
        resetCor();
        cout << "Pressione Enter para continuar...";
        cin.ignore();
        cin.get();
        return false;
    }

    // perda forcada
    int probabilidade_vitoria_geral_perc = 45;
    int probabilidade_diamante_perc = 30;

    bool perda_forcada = false;
    if (*(jogador->vitorias_consecutivas) >= 3 && aposta > (*(jogador->dinheiro) / 2)) {
        setCor(COR_VERMELHA);
        cout << "\n[Log] Por ter vencido 3 vezes seguidas, sua proxima aposta com o valor maior que a metade\n";
        cout << "do saldo atual (atual aposta) sera automaticamente perdida.\n";
        resetCor();
        perda_forcada = true;
        Sleep(2000);
    }

    *(jogador->dinheiro) -= aposta;
    setCor(COR_AMARELA);
    cout << "\n--- GIRANDO A ROLETA ---\n";
    resetCor();

    const int TAM_MAX_LINHA = 50;

    // animaçao
    for (int k = 0; k < 15; ++k) {
        cout << "\r" << string(TAM_MAX_LINHA, ' ');
        cout << "\rResultado: ";

        for (int i = 0; i < 3; i++) {
            cout << jogador->simbolos[rand() % jogador->num_simbolos] << " ";
        }
        cout.flush();
        Sleep(80);
    }

    int resultado[3];
    int chance_geral = rand() % 100;

    if (perda_forcada || chance_geral >= probabilidade_vitoria_geral_perc) {
        do {
            for (int i = 0; i < 3; i++) {
                resultado[i] = sortearSimbolo(jogador);
            }
        } while (resultado[0] == resultado[1] && resultado[1] == resultado[2]);
    } else {

        int simbolo_para_vitoria;
        int chance_diamante_especifica = rand() % 100;

        if (chance_diamante_especifica < probabilidade_diamante_perc) {
            simbolo_para_vitoria = 2;
        } else {
            simbolo_para_vitoria = rand() % (jogador->num_simbolos - 1);
        }

        resultado[0] = simbolo_para_vitoria;
        resultado[1] = simbolo_para_vitoria;
        resultado[2] = simbolo_para_vitoria;
    }

    cout << "\r" << string(TAM_MAX_LINHA, ' ');
    cout << "\rResultado: ";
    for (int i = 0; i < 3; i++) {
        cout << jogador->simbolos[resultado[i]] << " ";
    }
    cout << endl;

    Sleep(1000);

    if (resultado[0] == resultado[1] && resultado[1] == resultado[2] && !perda_forcada) {
        int premio;
        if (resultado[0] == 2) {
            premio = aposta * 5;
            setCor(COR_AMARELA);
            cout << "!!! JACKPOT !!! Seu premio foi multiplicado por 5. R$" << premio << "!\n";
            resetCor();
        } else {
            premio = aposta * 2;
            setCor(COR_VERDE);
            cout << "!!! PARABENS !!! Voce ganhou R$" << premio << "!\n";
            resetCor();
        }

        *(jogador->dinheiro) += premio;
        *(jogador->vitorias) += 1;
        *(jogador->valor_ganho) += premio;
        *(jogador->vitorias_consecutivas) += 1;

        cout << "Seu novo saldo: R$" << *(jogador->dinheiro) << endl;
        cout << "Pressione Enter para continuar...";
        cin.ignore();
        cin.get();
        return true;
    } else {
        *(jogador->derrotas) += 1;
        *(jogador->valor_perdido) += aposta;
        *(jogador->vitorias_consecutivas) = 0;
        setCor(COR_VERMELHA);
        if (perda_forcada) {
             cout << "Voce perdeu R$" << aposta << ".\n";
        } else {
             cout << "Os simbolos nao sao iguais. Voce perdeu R$" << aposta << ".\n";
        }
        resetCor();
        cout << "Seu novo saldo: R$" << *(jogador->dinheiro) << endl;
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
        arquivo << *(jogador->vitorias_consecutivas) << endl;
        arquivo.close();
    } else {
        setCor(COR_VERMELHA);
        cout << "Erro ao salvar os dados!\n";
        resetCor();
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
        arquivo >> *(jogador->vitorias_consecutivas);
        arquivo.close();
        setCor(COR_AMARELA);
        cout << "Dados carregados com sucesso!\n";
        resetCor();
        Sleep(1000);
    } else {
        setCor(COR_AMARELA);
        cout << "Nenhum dado salvo encontrado. Iniciando novo jogo.\n";
        resetCor();
        Sleep(1000);
    }
}
