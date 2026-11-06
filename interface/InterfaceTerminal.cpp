#include "InterfaceTerminal.h"

#include <iostream>
#include <limits>
#include <utility>

#include "../navios/Cruzador.h"
#include "../navios/Destroyer.h"
#include "../navios/Submarino.h"

InterfaceTerminal::InterfaceTerminal(Jogador& jogador1, Jogador& jogador2, Partida& partida)
:jogador1(jogador1), jogador2(jogador2), partida(partida){}

bool InterfaceTerminal::trocarJogador(int proximoJogador)
{
    std::string entrada;

    std::cout << "\nPressione ENTER para encerrar "
              << "sua visualizacao...";

    if (!std::getline(std::cin, entrada))
        return false;

    // Limpa a tela do terminal
    std::cout << "\033[2J\033[H" << std::flush;

    std::cout << "\nPasse o computador para o Jogador "
              << proximoJogador << ".\n";

    std::cout << "Pressione ENTER quando estiver pronto...";

    if (!std::getline(std::cin, entrada))
        return false;

    // Limpa novamente antes de mostrar os tabuleiros
    std::cout << "\033[2J\033[H" << std::flush;

    return true;
}

bool InterfaceTerminal::lerInteiro(const std::string& mensagem, int& valor)
{
    while(true){
        std::cout << mensagem;

        if (std::cin >> valor)
        {
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n'
            );

            return true;
        }

        if(std::cin.eof())
            return false;

        std::cin.clear();
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n'
        );
        std::cout << "Digite um numero inteiro! \n";
    }
}

std::unique_ptr<Navio> InterfaceTerminal::criarNavio(int tipo)
{
    switch (tipo)
    {
        case 1:
            return std::make_unique<Cruzador>();

        case 2:
            return std::make_unique<Destroyer>();

        case 3:
            return std::make_unique<Submarino>();

        default:
            return nullptr;
    }
}

bool InterfaceTerminal::posicionarFrota(Jogador& jogador, int numeroJogador){
    std::cout << "\n ===== POSICIONAMENTO DO JOGADOR " << numeroJogador << " =====\n";

    for(int tipo = 1; tipo <= 3; tipo ++){
        while(true)
        {
            auto navio = criarNavio(tipo);

            std::cout << "\nPosicionando: "
            << navio -> getNome()
            << " (tamanho: "
            << navio->getTamanho()
            << ")\n";

            jogador.getFrota().exibir();

            int linha, coluna, orientacao;

            if (!lerInteiro("Linha inicial: ", linha))
                return false;

            if (!lerInteiro("Coluna inicial: ", coluna))
                return false;

            std::cout << "Orientacao:\n";
            std::cout << "1 - Horizontal\n";
            std::cout << "2 - Vertical\n";

            if(!lerInteiro("Escolha: ", orientacao))
                return false;

            if(orientacao != 1 && orientacao != 2){
                std::cout << "Orientacao invalida! \n";
                continue;
            }

            bool horizontal = (orientacao == 1);

            bool posicionou = jogador.adicionarNavio(
                std::move(navio),
                {linha, coluna},
                horizontal
            );

            if(posicionou)
            {
                std::cout << "Navio posicionado!\n";
                break;
            }

            std::cout << "Posicionamento invalido! "
            << "Tente novamente. \n";
        }
    }

    return true;
}

void InterfaceTerminal::iniciar(){

    if(!posicionarFrota(jogador1, 1))
        return;

    if (!trocarJogador(2))
    return;

    if(!posicionarFrota(jogador2, 2))
        return;

    if (!trocarJogador(1))
    return;

    while(!partida.estaEncerrada()){
        int turno = partida.getTurnoAtual();

        Jogador& jogadorAtual = (turno == 1)
            ? jogador1
            : jogador2;

        std::cout << "\n===== TURNO DO JOGADOR " << turno << "=====\n";

        std::cout << "\nSua frota:\n";
        jogadorAtual.getFrota().exibir();

        std::cout << "\nseu radar:\n";
        jogadorAtual.getRadar().exibir();

        int linha, coluna;

        if(!lerInteiro("\nLinha do ataque: ", linha))
        return;

        if(!lerInteiro("\nColuna do ataque: ", coluna))
        return;

        ResultadoTurno resultado =
            partida.executarTurno({linha, coluna});

        switch (resultado)
        {
            case ResultadoTurno::Acerto:
                std::cout << "Jogador " << turno
                        << " acertou!\n";
                break;

            case ResultadoTurno::Erro:
                std::cout << "Jogador " << turno
                        << " errou!\n";
                break;

            case ResultadoTurno::CoordenadaInvalida:
                std::cout << "Coordenada invalida!\n";
                break;

            case ResultadoTurno::AtaqueRepetido:
                std::cout << "Coordenada ja atacada!\n";
                break;

            case ResultadoTurno::Vitoria:
                std::cout << "Jogador " << turno
                        << " acertou e venceu!\n";
                break;

            case ResultadoTurno::PartidaEncerrada:
                std::cout << "Partida ja encerrada!\n";
                break;
        }

        if(!partida.estaEncerrada() && (resultado == ResultadoTurno::Acerto ||resultado == ResultadoTurno::Erro))
        {
            if(!trocarJogador(partida.getTurnoAtual()))
            return;
        }
    }
}
