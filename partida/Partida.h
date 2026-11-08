#ifndef PARTIDA_H
#define PARTIDA_H

#include "../jogadores/Jogador.h"
#include <string>

enum class ResultadoTurno
{
    Acerto,
    Erro,
    CoordenadaInvalida,
    AtaqueRepetido,
    Vitoria,
    PartidaEncerrada
};

struct ResultadoTurnoDetalhado{
    ResultadoTurno tipo;
    std::string nomeNavioAfundado;
};

class Partida{
private:
    Jogador& jogador1;
    Jogador& jogador2;

    int turnoAtual;
    bool encerrada;

public:
    Partida(Jogador& jogador1, Jogador& jogador2);

    ResultadoTurnoDetalhado executarTurno(const Coordenada& coordenada);
    bool estaEncerrada() const;
    int getTurnoAtual() const;
};

#endif