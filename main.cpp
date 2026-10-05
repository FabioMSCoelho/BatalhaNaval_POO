#include <iostream>
#include "navios/Navio.h"
#include "navios/PortaAvioes.h"
#include "navios/Encouracado.h"
#include "navios/Cruzador.h"
#include "navios/Destroyer.h"
#include "navios/Submarino.h"
#include "tabuleiros/Tabuleiro.h"
#include <vector>

int main()
{   
    PortaAvioes portaavioes;
    Encouracado encouracado;
    Cruzador cruzador;
    Destroyer destroyer;
    Submarino submarino;

    Tabuleiro tabuleiro;

    tabuleiro.exibir();
    
    // std::vector<Navio*> frota;
    
    // frota.push_back(&portaavioes);
    // frota.push_back(&encouracado);
    // frota.push_back(&cruzador);
    // frota.push_back(&destroyer);
    // frota.push_back(&submarino);

    // for (Navio* navio : frota)
    // {
    //     std::cout << navio->getNome()
    //     << navio->getTamanho()
    //     << navio->getSimbolo()
    //     <<std::endl;
    // }



    return 0;
}