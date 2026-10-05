#ifndef ENCOURACADO_H
#define ENCOURACADO_H

#include "Navio.h"

class Encouracado : public Navio
{
public:
    Encouracado();

    char getSimbolo() const override;   
};

#endif