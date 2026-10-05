#ifndef CRUZADOR_H
#define CRUZADOR_H

#include "Navio.h"

class Cruzador : public Navio
{
public:
    Cruzador();

    char getSimbolo() const override;
};

#endif