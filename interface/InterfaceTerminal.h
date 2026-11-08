#ifndef INTERFACE_TERMINAL_H
#define INTERFACE_TERMINAL_H

#include <memory>
#include <string>

#include "../jogadores/Jogador.h"
#include "../partida/Partida.h"
#include "../navios/Navio.h"
#include "../configuracao/ConfiguracaoFrota.h"

class InterfaceTerminal{
private:
    Jogador& jogador1;
    Jogador& jogador2;
    Partida& partida;
    ConfiguracaoFrota configuracao;

    static void limparTela();

    bool trocarJogador(int proximoJogador);

    static bool lerInteiro(
        const std::string& mensagem,
        int& valor
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
