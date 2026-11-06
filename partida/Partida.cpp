#include "Partida.h"

Partida::Partida(Jogador& jogador1, Jogador& jogador2)
: jogador1(jogador1), jogador2(jogador2), turnoAtual(1), encerrada(false){}

int Partida::getTurnoAtual() const{
    return turnoAtual;
}

bool Partida::estaEncerrada() const{
    return encerrada;
}

ResultadoTurno Partida::executarTurno(const Coordenada& coordenada){
    if(encerrada)
    {
        return ResultadoTurno::PartidaEncerrada;
    }

    Jogador& atacante = (turnoAtual == 1)
        ? jogador1
        : jogador2;

    Jogador& defensor = (turnoAtual == 1)
        ? jogador2
        : jogador1;

    if(!atacante.getRadar().coordenadaValida(coordenada)){
        return ResultadoTurno::CoordenadaInvalida;
    }

    if(atacante.getRadar().jaFoiAtacada(coordenada)){
        return ResultadoTurno::AtaqueRepetido;
    }

    bool acertou = atacante.atacar(defensor, coordenada);

    if(defensor.todosNaviosAfundados()){
        encerrada = true;
        return ResultadoTurno::Vitoria;
    }

    turnoAtual = (turnoAtual == 1) ? 2 : 1;

    return acertou
        ? ResultadoTurno::Acerto
        : ResultadoTurno::Erro;

}
