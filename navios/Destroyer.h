#ifndef DESTROYER_H
#define DESTROYER_H

#include "Navio.h"

class Destroyer : public Navio
{
public:
    Destroyer();

    char getSimbolo() const override;
};

#endif