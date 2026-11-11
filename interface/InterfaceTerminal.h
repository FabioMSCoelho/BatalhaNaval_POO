#ifndef INTERFACE_TERMINAL_H
#define INTERFACE_TERMINAL_H

#include <memory>
#include <string>

#include "../jogadores/Jogador.h"
#include "../partida/Partida.h"
#include "../navios/Navio.h"
#include "../configuracao/ConfiguracaoFrota.h"
#include "../tabuleiros/Tabuleiro.h"
#include "../util/Coordenada.h"

class InterfaceTerminal{
private:
    Jogador& jogador1;
    Jogador& jogador2;
    Partida& partida;
    ConfiguracaoFrota configuracao;

    static void limparTela();

    static void mostrarErroTemporario(
        const std::string& mensagem
    );

    bool trocarJogador();

    static bool lerInteiro(
        const std::string& mensagem,
        int& valor
    );

    bool lerCoordenada(
        const Tabuleiro& tabuleiro,
        Coordenada& coordenada,
        const std::string& contexto
    );

    bool posicionarFrota(
        Jogador& jogador,
        int numeroJogador
    );


public:
    InterfaceTerminal(
        Jogador& jogador1,
        Jogador& jogador2,
        Partida& partida
    );

    void iniciar();

};

#endif
