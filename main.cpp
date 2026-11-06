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
#include "interface/InterfaceTerminal.h"
#include <memory>
#include <vector>
#include <limits>


int main() {
    Jogador jogador1("Jogador 1");
    Jogador jogador2("Jogador 2");

    Partida partida(jogador1, jogador2);

    InterfaceTerminal interface(
        jogador1,
        jogador2,
        partida
    );

    interface.iniciar();

    return 0;
}