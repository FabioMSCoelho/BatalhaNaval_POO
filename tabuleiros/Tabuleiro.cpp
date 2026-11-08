#include "Tabuleiro.h"
#include <iostream>
#include <iomanip>
#include "../util/Cores.h"

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
        std::cout << std::setw(3) << coluna;
    }
    std::cout << std::endl;

    for (int i = 0; i < TAMANHO; i++)
    {
        std::cout << std::setw(2) << i;
        for (int j = 0; j < TAMANHO; j++)
        {
            char simbolo = '~';
            const char* cor = Cores::Azul;

            switch (celulas[i][j])
            {
                case TipoCelula::Agua:
                    simbolo = '~';
                    cor = Cores::Azul;
                    break;

                case TipoCelula::Navio:
                    simbolo = 'N';
                    cor = Cores::Ciano;
                    break;

                case TipoCelula::Acerto:
                    simbolo = 'X';
                    cor = Cores::Vermelho;
                    break;

                case TipoCelula::Erro:
                    simbolo = '*';
                    cor = Cores::Amarelo;
                    break;
            }

            std::cout << cor
                      << std::setw(3) << simbolo
                      << Cores::Reset;
        }
        std::cout << std::endl;       
    }    
}
