#ifndef PARTIDA_H
#define PARTIDA_H

#include "../jogadores/Jogador.h"

class Partida{
private:
    Jogador& jogador1;
    Jogador& jogador2;

    int turnoAtual;
    bool encerrada;

public:
    Partida(Jogador& jogador1, Jogador& jogador2);

    void executarTurno(const Coordenada& coordenada);
    bool estaencerrada() const;
};

#endif