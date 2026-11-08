#ifndef CONFIGURACAO_H
#define CONFIGURACAO_H

#include <vector>
#include <memory>

#include "../navios/Navio.h"

enum class TipoNavio
{
    PortaAvioes,
    Encouracado,
    Cruzador,
    Destroyer,
    Submarino
};

class ConfiguracaoFrota{
private:
    std::vector<TipoNavio> tipos;

public:
    ConfiguracaoFrota();

    const std::vector<TipoNavio>& getTipos() const;

    std::unique_ptr<Navio> criarNavio(TipoNavio tipo) const;
};

#endif