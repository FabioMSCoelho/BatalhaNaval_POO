#include "TabuleiroRadar.h"

TabuleiroRadar::TabuleiroRadar(){

}

bool TabuleiroRadar::jaFoiAtacada(const Coordenada& coordenada) const{
    if(!coordenadaValida(coordenada)){
        return false;
    }
    return getCelula(coordenada) != TipoCelula::Agua;
    
}

void TabuleiroRadar::registrarAcerto(const Coordenada & coordenada){
    if(coordenadaValida(coordenada)){
    celulas[coordenada.linha][coordenada.coluna] = TipoCelula::Acerto;
}
}

    void TabuleiroRadar::registrarErro(const Coordenada& coordenada){
         if(coordenadaValida(coordenada)){
    celulas[coordenada.linha][coordenada.coluna] = TipoCelula::Erro;
}
}