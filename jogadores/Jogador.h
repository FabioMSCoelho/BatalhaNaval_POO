#ifndef JOGADOR_H
#define JOGADOR_H

#include <string>
#include <vector>
#include <memory>
#include "../tabuleiros/TabuleiroFrota.h"
#include "../tabuleiros/TabuleiroRadar.h"
#include "../navios/Navio.h"

class Jogador
{
private:
    std::string nome;
    TabuleiroFrota frota;
    TabuleiroRadar radar;
    std::vector<std::unique_ptr<Navio>> navios;

public:
    Jogador(std::string nome);

    std::string getNome() const;

    TabuleiroFrota& getFrota();
    TabuleiroRadar& getRadar();

    bool atacar(Jogador& adversario, const Coordenada& coordenada);

    bool adicionarNavio(
    std::unique_ptr<Navio> navio,
    const Coordenada& inicio,
    bool horizontal
    );

    bool todosNaviosAfundados() const;
};

#endif
