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

void InterfaceTerminal::exibirTituloCentralizado(
    const std::string& titulo,
    bool negrito )
{
    constexpr int larguraTabuleiro = 42;

    int espacos = (
        larguraTabuleiro - static_cast<int>(titulo.size())
    ) / 2;

    if (espacos < 0)
        espacos = 0;

    std::cout << std::string(espacos, ' ');

    if (negrito)
        std::cout << Cores::Negrito;

    std::cout << titulo << Cores::Reset << "\n";
}


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


bool InterfaceTerminal::trocarJogador()
{
    std::string entrada;

    limparTela();

    std::cout << "Passe o computador para o seu oponente\n";

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

            exibirTituloCentralizado( "POSICIONAMENTO DO JOGADOR "
            + std::to_string(numeroJogador), true);

            exibirTituloCentralizado(
            "Posicionando: " + navio->getNome() +
            " (tamanho: " + std::to_string(navio->getTamanho()) + ")");

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
                break;
            }

            std::cout << "Posicionamento invalido! "
            << "Tente novamente. \n";

            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
    }

    limparTela();

    exibirTituloCentralizado( "POSICIONAMENTO DO JOGADOR "
                + std::to_string(numeroJogador), true);
    std::cout << "\n\n";

    jogador.getFrota().exibir();

    std::cout << "\nEnviando embarcaçoes...\n";
    std::this_thread::sleep_for(
    std::chrono::seconds(3));

    if (!trocarJogador())
        return false;

    return true;
}

void InterfaceTerminal::exibirTelaTurno(Jogador& jogador, int turno){
    limparTela();

    exibirTituloCentralizado("TURNO DO JOGADOR " + std::to_string(turno),true);
    std::cout << "\n";

    exibirTituloCentralizado("Sua frota:");

    std::cout << "\n";
    jogador.getFrota().exibir();
    std::cout << "\n";

    exibirTituloCentralizado("Seu radar:");
    std::cout << "\n";

    jogador.getRadar().exibir();
    std::cout << "\n";

}

void InterfaceTerminal::iniciar(){

    if(!exibirMenuInicial())
        return;

    if(!posicionarFrota(jogador1, 1))
        return;

    if(!posicionarFrota(jogador2, 2))
        return;

    while(!partida.estaEncerrada()){

        int turno = partida.getTurnoAtual();

        Jogador& jogadorAtual = (turno == 1)
        ? jogador1
        : jogador2;

        exibirTelaTurno(jogadorAtual, turno);

        Coordenada tiro{};

        if (!lerCoordenada(
            jogadorAtual.getRadar(),
            tiro,
            "do ataque"
        ))
        {
            return;
        }

        ResultadoTurnoDetalhado resultado = partida.executarTurno(tiro);

        exibirTelaTurno(jogadorAtual, turno);

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

        // Verifica se a partida terminou com uma vitoria
        if (resultado.tipo == ResultadoTurno::Vitoria)
        {
            exibirTelaVitoria(turno);
            return;
        }

        // Troca de jogador somente apos um erro
        if (!partida.estaEncerrada() &&
            resultado.tipo == ResultadoTurno::Erro)
        {
            if (!trocarJogador())
                return;
        }
    }
}

    void InterfaceTerminal::exibirLogoMenu(){
        struct LinhaLogo{
            const char* ciano;
            const char* vermelho;
        };

        const LinhaLogo logo[] = {
        {R"(      __________         __    __  .__         )", R"(  _________.__    .__        )"},
        {R"(      \______   \_____ _/  |__/  |_|  |   ____ )", R"( /   _____/|  |__ |__|_____  )"},
        {R"(       |    |  _/\__  \\   __\   __\  | _/ __ \)", R"( \_____  \ |  |  \|  \  __ \ )"},
        {R"(       |    |   \ / __ \|  |  |  | |  |_\  ___/)", R"( /        \|   Y  \  |  |_| >)"},
        {R"(       |______  /(____  /__|  |__| |____/\___ \)", R"(/_______  /|___|  /__|   __/)"},
        {R"(              \/      \/                     \/)", R"(        \/      \/   |__|   )"}
    };

        for (const auto& linha : logo){
            std::cout << Cores::Ciano
                  << linha.ciano
                  << Cores::Vermelho
                  << linha.vermelho
                  << Cores::Reset
                  << '\n';
        }
    }

    void InterfaceTerminal::exibirNavioMenu(){
        const char* navio[] = {
            R"(                                       |__)",
            R"(     [1] Comecar novo jogo             |\/)",
            R"(     [2] Instrucoes                    ---)",
            R"(     [3] Configuracoes                 / | [)",
            R"(     [4] Sair                   !      | |||)",
            R"(                              _/|     _/|-++')",
            R"(                          +  +--|    |--|--|_ |-)",
            R"(                       { /|__|  |/\__|  |--- |||__/)",
            R"(                      +---------------___[}-_===_.'____                 /\)",
            R"(                  ____`-' ||___-{]_| _[}-  |     |_[___\==--            \/   _)",
            R"(    __..._____--==/___]_|__|_____________________________[___\==--____,------' .7)",
            R"(   |                                                                     BB-61/)",
            R"(    \_________________________________________________________________________|)",
            R"(   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~)"
        };

        for (const char* linha : navio)
        {
            std::cout << linha << '\n';
        }
    }

        bool InterfaceTerminal::exibirMenuInicial()
    {
        while (true)
        {
            limparTela();

            std::cout << '\n';

            exibirLogoMenu();

            std::cout << "\n\n\n";

            exibirNavioMenu();

            std::cout << "\n";

            int opcao{};

            if (!lerInteiro("   Escolha uma opcao: ", opcao))
            return false;

            switch (opcao)
            {
                case 1:
                return true;

                case 2:
                exibirInstrucoes();
                break;

                case 3:
                {
                    limparTela();

                    exibirTituloCentralizado(
                    "CONFIGURACOES", true
                    );

                    std::cout
                    << "\nA configuracao de quantidades "
                    << "sera integrada a ConfiguracaoFrota.\n\n"
                    << "Pressione ENTER para voltar...";

                    std::string entrada;

                    if (!std::getline(std::cin, entrada))
                    return false;

                    break;
                }

                case 4:
                    limparTela();
                    std::cout << "Saindo do jogo...\n";
                    return false;

                    default:
                    mostrarErroTemporario(
                    "Opcao invalida! Tente novamente."
                    );
                    break;
            }
        }
    }


void InterfaceTerminal::exibirInstrucoes()
{
    limparTela();


    exibirTituloCentralizado("               INSTRUCOES", true);

    std::cout << "\n";
    std::cout << "O objetivo do jogo e destruir todos os navios "
    << "do seu oponente.\n\n";

    std::cout << "No inicio da partida, o campo inimigo estara "
    << "totalmente oculto.\n";
    std::cout << "Voce nao sabera onde os navios do adversario "
    << "estao posicionados.\n\n";

    std::cout << "Para atacar, informe a LINHA e a COLUNA "
    << "do local desejado.\n\n";

    std::cout << "Se voce acertar um navio, a posicao sera "
    << "marcada com ";
    std::cout << Cores::Vermelho << "X"
    << Cores::Reset
    << " e voce podera jogar novamente.\n\n";

    std::cout << "Se voce errar o ataque, a posicao sera "
    << "marcada com ";
    std::cout << Cores::Amarelo << "*"
    << Cores::Reset
    << " e a vez passara para o adversario.\n\n";

    std::cout << "O jogo termina quando um jogador destruir "
    << "todos os navios do oponente.\n\n";

    std::cout << "Pressione ENTER para voltar ao menu...";

    std::string entrada;
    std::getline(std::cin, entrada);
}

void InterfaceTerminal::exibirTelaVitoria(int numeroJogador){

    limparTela();

    std::cout << "\n\n";

    exibirTituloCentralizado(
        "===== FIM DE JOGO =====", true
    );

    std::cout << "\n";

    exibirTituloCentralizado(
        "JOGADOR " + std::to_string(numeroJogador)
        + " VENCEU!", true
    );

    std::cout << "\n\n";

    exibirTituloCentralizado(
        "Todas as embarcacoes inimigas foram afundadas!"
    );

    std::cout << "\n\n";

    exibirTituloCentralizado(
        "Pressione ENTER para encerrar..."
    );

    std::string entrada;
    std::getline(std::cin, entrada);
}
