#include "Tabuleiro.h"
#include <iostream>
#include <iomanip>

Tabuleiro::Tabuleiro()
{
    for (int i = 0; i < TAMANHO; i++)
    {
        for (int j = 0; j < TAMANHO; j++)
        {
            celulas[i][j] = TipoCelula::Agua;
        }        
    }    
}

bool Tabuleiro::coordenadaValida(const Coordenada& coordenada) const
{
    return coordenada.coluna >= 0 
        && coordenada.linha >= 0 
        && coordenada.coluna < TAMANHO 
        && coordenada.linha < TAMANHO;
}

TipoCelula Tabuleiro::getCelula(const Coordenada& coordenada) const
{
    // if(coordenadaValida(coordenada) == true){
        return celulas[coordenada.linha][coordenada.coluna];
    // }
}

void Tabuleiro::exibir() const
{
    std::cout << "  ";
    for (int coluna = 0; coluna < TAMANHO; coluna++)
    {
        std::cout << std::setw(3) << coluna + 1;
    }
    std::cout << std::endl;

    for (int i = 0; i < TAMANHO; i++)
    {
        std::cout << std::setw(2) << i + 1;
        for (int j = 0; j < TAMANHO; j++)
        {
            if(celulas[i][j] == TipoCelula::Agua)
            {
                std::cout << std::setw(3) << "~";
            }
            else if (celulas[i][j] == TipoCelula::Navio){
                std::cout << std::setw(3) << "N";
            }
            else if(celulas[i][j] == TipoCelula::Acerto)
            {
                std::cout << std::setw(3) << "X";
            }
            else if (celulas[i][j] == TipoCelula::Erro){
                std::cout << std::setw(3) << "*";
            }
        } 
        std::cout << std::endl;       
    }    
}
