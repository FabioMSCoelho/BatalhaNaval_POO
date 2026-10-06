#ifndef JOGADOR_H
#define JOGADOR_H

#include <string>
#include "../tabuleiros/TabuleiroFrota.h"
#include "../tabuleiros/TabuleiroRadar.h"

class Jogador
{
private:
    std::string nome;
    TabuleiroFrota frota;
    TabuleiroRadar radar;

public:
    Jogador(std::string nome);

    std::string getNome() const;

    TabuleiroFrota& getFrota();
    TabuleiroRadar& getRadar();

    bool atacar(Jogador& adversario, const Coordenada& coordenada);
};

#endif
