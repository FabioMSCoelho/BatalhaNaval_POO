#ifndef NAVIO_H
#define NAVIO_H

#include <string>

class Navio
{
    private:
        std::string nome;
        int tamanho;
        int partesAtingidas;

    public:
        Navio(std::string nome, int tamanho);

        std::string getNome() const;
        int getTamanho() const;
        int getPartesAtingidas() const;

        void registrarAcerto();
        bool estaAfundado() const;
        
        virtual char getSimbolo()const = 0;
};

#endif