#include "Jogador.h"

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