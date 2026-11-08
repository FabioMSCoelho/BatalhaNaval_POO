#ifndef TABULEIROFROTA_H
#define TABULEIROFROTA_H

#include "Tabuleiro.h"
#include "../navios/Navio.h"

class TabuleiroFrota : public Tabuleiro
{
private:
    Navio* navios[TAMANHO][TAMANHO];

public:
    TabuleiroFrota();

    bool posicionarNavio(
        Navio& navio,
        const Coordenada& inicio,
        bool horizontal
    );

    bool receberAtaque(const Coordenada& coordenada);

    const Navio* getNavioNaPosicao(
        const Coordenada& coordenada
    ) const;
};

#endif