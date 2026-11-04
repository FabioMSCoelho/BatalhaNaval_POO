#include <iostream>
#include "navios/Navio.h"
#include "navios/PortaAvioes.h"
#include "navios/Encouracado.h"
#include "navios/Cruzador.h"
#include "navios/Destroyer.h"
#include "navios/Submarino.h"
#include "tabuleiros/Tabuleiro.h"
#include "tabuleiros/TabuleiroFrota.h"
#include "tabuleiros/TabuleiroRadar.h"
#include "jogadores/Jogador.h"
#include "partida/Partida.h"
#include <vector>


int main() {
    Jogador jogador1("Jogador 1");
    Jogador jogador2("Jogador 2");

    bool navio1 = jogador1.adicionarNavio(
        std::make_unique<Submarino>(),
        {1, 1},
        true
    );

    bool navio2 = jogador2.adicionarNavio(
        std::make_unique<Submarino>(),
        {2, 3},
        true
    );

    if (!navio1 || !navio2)
    {
        std::cout << "Erro ao posicionar navios!\n";
        return 1;
    }

    Partida partida(jogador1, jogador2);

    // Jogador 1 erra
    partida.executarTurno({5, 5});

    // Jogador 2 erra
    partida.executarTurno({6, 6});

    // Jogador 1 repete um ataque
    partida.executarTurno({5, 5});

    // Jogador 1 acerta e vence
    partida.executarTurno({2, 3});

    // Tentativa de ataque depois da vitoria
    partida.executarTurno({1, 1});

    return 0;

}