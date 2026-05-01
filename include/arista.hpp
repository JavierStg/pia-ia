#ifndef ARISTA_HPP
#define ARISTA_HPP

#include <iostream>

typedef struct arista
{
    std::string destino;
    std::string peso;

    arista(std::string d, std::string p) : destino(d), peso(p) {}
    
    bool operator<(const struct arista& a) const 
    {
        return destino < a.destino;
    }
} arista;
#endif