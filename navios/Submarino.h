#ifndef SUBMARINO_H
#define SUBMARINO_H

#include "Navio.h"

class Submarino : public Navio
{
    public:
        Submarino();

    char getSimbolo() const override;
};

#endif