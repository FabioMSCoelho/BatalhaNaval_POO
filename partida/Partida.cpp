#include "Partida.h"
#include <iostream>

Partida::Partida(Jogador& jogador1, Jogador& jogador2)
: jogador1(jogador1), jogador2(jogador2), turnoAtual(1), encerrada(false){}

bool Partida::estaencerrada() const{
    return encerrada;
}

void Partida::executarTurno(const Coordenada& coordenada){
    if(encerrada)
    {
        std::cout << "partida encerrada!\n";
        return;
    }

    Jogador& atacante = (turnoAtual == 1)
        ? jogador1
        : jogador2;

    Jogador& defensor = (turnoAtual == 1)
        ? jogador2
        : jogador1;

    if(!atacante.getRadar().coordenadaValida(coordenada)){
        std::cout << "coordenada invalida!\n";
        return;
    }

    if(atacante.getRadar().jaFoiAtacada(coordenada)){
        std::cout << "coordenada já atacada!\n";
        return;
    }

    bool acertou = atacante.atacar(defensor, coordenada);

    std::cout << "Jogador " << turnoAtual
              << " atacou (" << coordenada.linha
              << ", " << coordenada.coluna << "): "
              << (acertou ? "Acerto" : "Erro")
              << std::endl;

    if(defensor.todosNaviosAfundados()){
        encerrada = true;

        std::cout << "Jogador "
                  << turnoAtual
                  << " venceu!\n";

        return;
    }

    turnoAtual = (turnoAtual == 1) ? 2 : 1;

}
