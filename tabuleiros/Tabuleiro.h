#ifndef TABULEIRO_H
#define TABULEIRO_H

#include "../util/Coordenada.h"
enum class TipoCelula
{
    Agua,
    Erro,
    Acerto,
    Navio
};

class Tabuleiro{
protected:
    static const int TAMANHO = 13;

    TipoCelula celulas[TAMANHO][TAMANHO];

public:
    Tabuleiro();

    bool coordenadaValida(const Coordenada& coordenada) const;

    TipoCelula getCelula(const Coordenada& coordenada) const;

    void exibir() const;
};

#endif