#include "TabuleiroFrota.h"

TabuleiroFrota::TabuleiroFrota()
{
    for (size_t i = 0; i < TAMANHO; i++)
    {
        for (size_t j = 0; j < TAMANHO; j++)
        {
            navios[i][j] = nullptr;
        }
    }

}

bool TabuleiroFrota::posicionarNavio(
    Navio& navio,
    const Coordenada& inicio,
    bool horizontal
    ){

    int tamanho = navio.getTamanho();
    // verifica se a coordenada inicial é válida
    if (!coordenadaValida(inicio))
    {
        return false;
    }

    // verifica se o navio cabe
    if (horizontal)
    {
        if (inicio.coluna + tamanho > TAMANHO)
        {
            return false;
        }
    }
    else
    {
        if (inicio.linha + tamanho > TAMANHO)
        {
            return false;
        }
    }

    // verifica sobreposição
    for (int i = 0; i < tamanho; i++)
    {
        int linhaAtual = horizontal
            ? inicio.linha
            : inicio.linha + i;

        int colunaAtual = horizontal
            ? inicio.coluna + i
            : inicio.coluna;

        if (celulas[linhaAtual][colunaAtual] != TipoCelula::Agua)
        {
            return false;
        }
    }

    // posiciona o navio
    for (int i = 0; i < tamanho; i++)
    {
        int linhaAtual = horizontal
            ? inicio.linha
            : inicio.linha + i;

        int colunaAtual = horizontal
            ? inicio.coluna + i
            : inicio.coluna;

            celulas[linhaAtual][colunaAtual] = TipoCelula::Navio;
            navios[linhaAtual][colunaAtual] = &navio;
    }

    return true;
}

bool TabuleiroFrota::receberAtaque(const Coordenada& coordenada){
    if(!coordenadaValida(coordenada)){
        return false;
    }

    TipoCelula estadoAtual = getCelula(coordenada);

    if(estadoAtual == TipoCelula::Navio){
        Navio* navioAtingido = navios[coordenada.linha][coordenada.coluna];
        navioAtingido->registrarAcerto();
        celulas[coordenada.linha][coordenada.coluna] = TipoCelula::Acerto;
        return true;
    }
    else if(
        estadoAtual == TipoCelula::Acerto ||
        estadoAtual == TipoCelula::Erro
    ) {
        return false;
    }
    celulas[coordenada.linha][coordenada.coluna] = TipoCelula::Erro;
        return false;
}
