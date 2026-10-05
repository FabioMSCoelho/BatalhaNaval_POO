#include "Navio.h"

Navio::Navio(std::string nome, int tamanho)
{
    this->nome = nome;
    this->tamanho = tamanho;
    this->partesAtingidas = 0;
}

std::string Navio::getNome() const
{
    return nome;
}

int Navio::getTamanho() const
{
    return tamanho;
}

int Navio::getPartesAtingidas() const{
    return partesAtingidas;
}

void Navio::registrarAcerto(){
    if(partesAtingidas < tamanho){
        partesAtingidas++;
    }
}
bool Navio::estaAfundado() const{
    return partesAtingidas >= tamanho;
}

