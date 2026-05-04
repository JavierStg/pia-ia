#ifndef ARISTA_HPP
#define ARISTA_HPP

#include <iostream>

typedef struct arista
{
    std::string destino;
    std::string peso;
    std::string heuristica;

    arista(std::string d, std::string p, std::string h) : destino(d), peso(p), heuristica(h){}
    
    bool operator<(const struct arista& a) const 
    {
        return destino < a.destino;
    }
} arista;
#endif