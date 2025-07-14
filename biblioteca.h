
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <windows.h>

using namespace std;

struct Jogador {
    int* dinheiro;
    string* simbolos;
    int num_simbolos;
    int* vitorias;
    int* derrotas;
    int* valor_ganho;
    int* valor_perdido;
};

void inicializarJogo(Jogador* jogador, int dinheiro_inicial = 100);
void finalizarJogo(Jogador* jogador);
void mostrarDinheiro(Jogador* jogador);
void mostrarEstatisticas(Jogador* jogador);
int sortearSimbolo(Jogador* jogador);
bool jogar(Jogador* jogador, int aposta);
void salvarDados(Jogador* jogador);
void carregarDados(Jogador* jogador);
