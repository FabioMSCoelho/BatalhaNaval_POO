#include "TabuleiroFrota.h"

TabuleiroFrota::TabuleiroFrota()
{
}

bool TabuleiroFrota::posicionarNavio(
    const Coordenada& inicio,
    int tamanho,
    bool horizontal
)
{
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
    }

    return true;
}

bool TabuleiroFrota::receberAtaque(const Coordenada& coordenada){
    if(!coordenadaValida(coordenada)){
        return false;
    }
    if(getCelula(coordenada) == TipoCelula::Navio){
        celulas[coordenada.linha][coordenada.coluna] = TipoCelula::Acerto;
        return true;
    }
    celulas[coordenada.linha][coordenada.coluna] = TipoCelula::Erro;
        return false;
}