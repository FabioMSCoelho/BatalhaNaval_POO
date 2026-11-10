#include "InterfaceTerminal.h"
#include "../util/Cores.h"

#include <iostream>
#include <limits>
#include <utility>
#include <thread>
#include <chrono>

#include "../navios/Cruzador.h"
#include "../navios/Destroyer.h"
#include "../navios/Submarino.h"
#include "../navios/Encouracado.h"
#include "../navios/PortaAvioes.h"

InterfaceTerminal::InterfaceTerminal(Jogador& jogador1, Jogador& jogador2, Partida& partida)
:jogador1(jogador1), jogador2(jogador2), partida(partida){}

void InterfaceTerminal::limparTela()
{
    std::cout << "\033[2J\033[3J\033[H" << std::flush;
}

void InterfaceTerminal::mostrarErroTemporario(
    const std::string& mensagem
)
{
    // Volta para a linha anterior e apaga seu conteudo
    std::cout << "\033[1A\r\033[2K";

    // Mostra a mensagem em vermelho
    std::cout << Cores::Vermelho
              << mensagem
              << Cores::Reset
              << std::flush;

    // Aguarda para permitir a leitura
    std::this_thread::sleep_for(
        std::chrono::seconds(2)
    );

    // Apaga somente a mensagem de erro
    std::cout << "\r\033[2K" << std::flush;
}


bool InterfaceTerminal::trocarJogador(int proximoJogador)
{
    std::string entrada;

    // std::this_thread::sleep_for(std::chrono::seconds(3));

    limparTela();

    std::cout << "\nPasse o computador para o Jogador "
              << proximoJogador << ".\n";

    std::cout << "Pressione ENTER quando estiver pronto...";

    if (!std::getline(std::cin, entrada))
        return false;

    // Limpa novamente antes de mostrar os tabuleiros
    limparTela();

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

        mostrarErroTemporario("Digite um numero inteiro!");
    }
}

bool InterfaceTerminal::lerCoordenada(
    const Tabuleiro& tabuleiro,
    Coordenada& coordenada,
    const std::string& contexto
){
    int linha,coluna;

    while(true){
        if (!lerInteiro("Linha " + contexto + ": ", linha))
            return false;

        if(tabuleiro.coordenadaValida({linha,0})){
            break;
        }

        mostrarErroTemporario("Linha invalida! Tente novamente.");
    }

    while(true){
        if (!lerInteiro("Coluna " + contexto + ": ", coluna))
            return false;

        if(tabuleiro.coordenadaValida({linha,coluna})){
            break;
        }

        mostrarErroTemporario("Coluna invalida! Tente novamente.");
    }

    // Armazena os valores validados
    coordenada = {linha, coluna};

    return true;
}

bool InterfaceTerminal::posicionarFrota(Jogador& jogador, int numeroJogador){
    for(TipoNavio tipo : configuracao.getTipos()){

        while(true){

            auto navio = configuracao.criarNavio(tipo);

            if (!navio)
            {
                std::cout << "Erro ao criar navio!\n";
                return false;
            }

            limparTela();

            std::cout << "\n ===== POSICIONAMENTO DO JOGADOR " << numeroJogador << " =====\n";
            std::cout << "\nPosicionando: "
            << navio -> getNome()
            << " (tamanho: "
            << navio->getTamanho()
            << ")\n";

            std::cout << "\n";
            jogador.getFrota().exibir();
            std::cout << "\n";

            Coordenada inicio{};

            if (!lerCoordenada(
                jogador.getFrota(),
                inicio,
                "inicial"
            ))
            {
                return false;
            }

            int orientacao = 1;

            if(navio->getTamanho() > 1){
                std::cout << "\nOrientacao:\n";
                std::cout << "1 - Horizontal\n";
                std::cout << "2 - Vertical\n\n";

                while(true){
                    if(!lerInteiro("Escolha: ", orientacao))
                        return false;

                    if(orientacao != 1 && orientacao != 2){
                        mostrarErroTemporario(
                        "Orientacao invalida!");

                        continue;
                    }
                    break;
                }
            }

            bool horizontal = (orientacao == 1);

            bool posicionou = jogador.adicionarNavio(
                std::move(navio),
                inicio,
                horizontal
            );

            if (posicionou)
            {
                std::cout << "\nNavio posicionado!\n";

                std::this_thread::sleep_for(std::chrono::seconds(2));

                break;
            }

            std::cout << "Posicionamento invalido! "
            << "Tente novamente. \n";

            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
    }
        limparTela();

        std::cout << "\nFrota completa!\n\n";

        jogador.getFrota().exibir();

        std::cout << "\nPressione ENTER para continuar...";

        std::string entrada;
        if (!std::getline(std::cin, entrada))
            return false;

    return true;
}

void InterfaceTerminal::iniciar(){

    if(!posicionarFrota(jogador1, 1))
        return;

    limparTela();

    if(!posicionarFrota(jogador2, 2))
        return;

    while(!partida.estaEncerrada()){

        limparTela();

        int turno = partida.getTurnoAtual();

        Jogador& jogadorAtual = (turno == 1)
            ? jogador1
            : jogador2;

        std::cout << "\n===== TURNO DO JOGADOR " << turno << "=====\n";

        std::cout << "\nSua frota:\n\n";
        jogadorAtual.getFrota().exibir();

        std::cout << "\nseu radar:\n\n";
        jogadorAtual.getRadar().exibir();
        std::cout << "\n";

        Coordenada tiro{};

        if (!lerCoordenada(
            jogadorAtual.getRadar(),
            tiro,
            "do ataque"
        ))
        {
            return;
        }

        ResultadoTurnoDetalhado resultado =
            partida.executarTurno(tiro);

        switch (resultado.tipo)
        {
            case ResultadoTurno::Acerto:
            std::cout << Cores::Vermelho
                << "Jogador " << turno
                << " acertou!"
                << Cores::Reset << '\n';
            break;

            case ResultadoTurno::Erro:
            std::cout << Cores::Amarelo
                << "Jogador " << turno
                << " errou!"
                << Cores::Reset << '\n';
            break;

            case ResultadoTurno::CoordenadaInvalida:
                std::cout << "Coordenada invalida!\n";
                break;

            case ResultadoTurno::AtaqueRepetido:
                std::cout << "Coordenada ja atacada!\n";
                break;

            case ResultadoTurno::Vitoria:
            std::cout << Cores::Verde
                << "Jogador " << turno
                << " acertou e venceu!"
                << Cores::Reset << '\n';
            break;

            case ResultadoTurno::PartidaEncerrada:
                std::cout << "Partida ja encerrada!\n";
                break;
        }

        if (!resultado.nomeNavioAfundado.empty())
        {
            std::cout << Cores::Vermelho
                    << Cores::Negrito
                    << "NAVIO AFUNDADO: "
                    << resultado.nomeNavioAfundado
                    << Cores::Reset
                    << '\n';
        }

        std::this_thread::sleep_for(std::chrono::seconds(3));

        if(!partida.estaEncerrada() && resultado.tipo == ResultadoTurno::Erro)
        {
            if(!trocarJogador(partida.getTurnoAtual()))
            return;
        }
    }
}
