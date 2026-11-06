#ifndef PARTIDA_H
#define PARTIDA_H

#include "../jogadores/Jogador.h"

enum class ResultadoTurno
{
    Acerto,
    Erro,
    CoordenadaInvalida,
    AtaqueRepetido,
    Vitoria,
    PartidaEncerrada
};

class Partida{
private:
    Jogador& jogador1;
    Jogador& jogador2;

    int turnoAtual;
    bool encerrada;

public:
    Partida(Jogador& jogador1, Jogador& jogador2);

    ResultadoTurno executarTurno(const Coordenada& coordenada);
    bool estaEncerrada() const;
    int getTurnoAtual() const;
};

#endif