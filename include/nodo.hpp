#ifndef NODO_HPP 
#define NODO_HPP

#include <iostream>
#include <set>
#include "./arista.hpp"

class Nodo
{
    private:
        std::string nombre;
        std::set<arista> aristas;

    public:
        std::string &getNombre()
        {
            return this->nombre;
        }

        std::set<arista> &getAristas()
        {
            return this->aristas;
        }

        void setNombre(std::string nombre)
        {
            this->nombre = nombre;
        }

        void setArista(std::string destino, std::string peso, std::string heuristica)
        {
            this->aristas.emplace(destino, peso, heuristica);
        }

        std::set<arista> &getArista()
        {
            return this->aristas;
        }
};
#endif
