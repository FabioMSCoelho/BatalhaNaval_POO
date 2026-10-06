#include <iostream>
#include "navios/Navio.h"
#include "navios/PortaAvioes.h"
#include "navios/Encouracado.h"
#include "navios/Cruzador.h"
#include "navios/Destroyer.h"
#include "navios/Submarino.h"
#include "tabuleiros/Tabuleiro.h"
#include "tabuleiros/TabuleiroFrota.h"
#include "tabuleiros/TabuleiroRadar.h"
#include "jogadores/Jogador.h"
#include <vector>

int main()
{   
    PortaAvioes portaavioes;
    Encouracado encouracado;
    Cruzador cruzador;
    Destroyer destroyer;
    Submarino submarino;

    Tabuleiro tabuleiro; 
    TabuleiroFrota frota;

    Coordenada inicio{3, 3};

    Jogador jogador1("fabio");
    Jogador jogador2("Giovana");

    std::cout << jogador1.getNome() << std::endl;
    std::cout << jogador2.getNome() << std::endl;


    bool conseguiu = frota.posicionarNavio(inicio, 3, true);

    std::cout << conseguiu << std::endl;

    inicio = {3, 12};

    conseguiu = frota.posicionarNavio(inicio, 3, true);

    std::cout << conseguiu << std::endl;

    frota.exibir();
    
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