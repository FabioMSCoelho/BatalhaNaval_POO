#ifndef TABULEIRORADAR_H
#define TABULEIRORADAR_H

#include "Tabuleiro.h"

class TabuleiroRadar: public Tabuleiro
{
public:
    TabuleiroRadar();

    bool jaFoiAtacada(const Coordenada& coordenada) const;
    void registrarAcerto(const Coordenada & coordenada);
    void registrarErro(const Coordenada& coordenada);
};

#endif