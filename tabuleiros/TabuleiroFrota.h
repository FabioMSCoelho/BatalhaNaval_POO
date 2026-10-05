#ifndef TABULEIROFROTA_H
#define TABULEIROFROTA_H

#include "Tabuleiro.h"

class TabuleiroFrota : public Tabuleiro
{
public:
    TabuleiroFrota();

    bool posicionarNavio(
        const Coordenada& inicio,
        int tamanho,
        bool horizontal
    );

    bool receberAtaque(const Coordenada& coordenada);
};

#endif