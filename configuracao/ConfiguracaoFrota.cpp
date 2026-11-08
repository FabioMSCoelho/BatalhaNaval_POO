#include "ConfiguracaoFrota.h"

#include "../navios/Cruzador.h"
#include "../navios/Destroyer.h"
#include "../navios/Submarino.h"
#include "../navios/Encouracado.h"
#include "../navios/PortaAvioes.h"

ConfiguracaoFrota::ConfiguracaoFrota()
    : tipos{
        // TipoNavio::PortaAvioes,
        // TipoNavio::Encouracado,
        // TipoNavio::Cruzador,
        TipoNavio::Destroyer,
        TipoNavio::Submarino
    }
{}

const std::vector<TipoNavio>& ConfiguracaoFrota::getTipos() const{
    return tipos;
}

std::unique_ptr<Navio> ConfiguracaoFrota::criarNavio(TipoNavio tipo) const{
    switch (tipo)
    {
        // case TipoNavio::PortaAvioes:
        //     return std::make_unique<PortaAvioes>();

        // case TipoNavio::Encouracado:
        //     return std::make_unique<Encouracado>();

        // case TipoNavio::Cruzador:
        //     return std::make_unique<Cruzador>();

        case TipoNavio::Destroyer:
            return std::make_unique<Destroyer>();

        case TipoNavio::Submarino:
            return std::make_unique<Submarino>();

        default:
            return nullptr;
    }
}