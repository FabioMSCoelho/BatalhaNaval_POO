#ifndef PORTAAVIOES_H
#define PORTAAVIOES_H

#include "Navio.h"

class PortaAvioes : public Navio
{
public:
    PortaAvioes();

    char getSimbolo() const override;
};

#endif