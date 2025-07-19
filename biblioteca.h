#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <windows.h>
#include <limits>

using namespace std;

#define COR_VERDE 10
#define COR_VERMELHA 12
#define COR_AMARELA 14
#define COR_BRANCA 15
#define COR_AZUL 9

struct Jogador {
    int* dinheiro;
    string* simbolos;
    int num_simbolos;
    int* vitorias;
    int* derrotas;
    int* valor_ganho;
    int* valor_perdido;
    int* vitorias_consecutivas;
};

void setCor(int cor);
void resetCor();

void inicializarJogo(Jogador* jogador, int dinheiro_inicial = 100);
void finalizarJogo(Jogador* jogador);
void mostrarDinheiro(Jogador* jogador);
void mostrarEstatisticas(Jogador* jogador);
int sortearSimbolo(Jogador* jogador);
bool jogar(Jogador* jogador, int aposta);
void salvarDados(Jogador* jogador);
void carregarDados(Jogador* jogador);
