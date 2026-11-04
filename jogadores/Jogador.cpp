#include "Jogador.h"
#include <utility>

Jogador::Jogador(std::string nome){
    this -> nome = nome;
}

std::string Jogador::getNome() const{
    return nome;
}

TabuleiroFrota& Jogador::getFrota(){
    return frota;
}

TabuleiroRadar& Jogador::getRadar(){
    return radar;
}

bool Jogador::adicionarNavio(
    std::unique_ptr<Navio> navio,
    const Coordenada& inicio,
    bool horizontal){
        if(!navio){
            return false;
        }
        if(!frota.posicionarNavio(*navio, inicio, horizontal)){
            return false;
        }
        navios.push_back(std::move(navio));
        return true;
}

bool Jogador::todosNaviosAfundados() const{
    if(navios.empty())
    {
        return false;
    }

    for(const auto& navio : navios){
        if(!navio->estaAfundado())
        {
            return false;
        }
    }

    return true;
}

bool Jogador::atacar(Jogador& adversario, const Coordenada& coordenada){
    if(!radar.coordenadaValida(coordenada))
    {
        return false;
    }
    if(radar.jaFoiAtacada(coordenada)){
        return false;
    }

    bool acertou = adversario.getFrota().receberAtaque(coordenada);
    
    if(acertou)
    {
        radar.registrarAcerto(coordenada);   
        return true; 
    }

    radar.registrarErro(coordenada);
    return false;  
}