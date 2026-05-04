#ifndef COSTOUNIFORME_HPP
#define COSTOUNIFORME_HPP

#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <limits>
#include "../nodo.hpp"
#include <queue>


std::vector<std::string> costoUniforme(std::unordered_map<std::string, Nodo> &mapa, std::string inicio, std::string objetivo)
{
    std::queue<std::string> cola;
    std::unordered_set<std::string> visitados;
    std::vector<std::string> orden_visita;
    std::string nodoActual, destino;
    float costo = 0, menor = std::numeric_limits<float>::max();

    cola.push(inicio);
    visitados.insert(inicio);

    while (!cola.empty())
    {
        nodoActual = cola.front();
        cola.pop();
        orden_visita.push_back(nodoActual);

        if (nodoActual == objetivo)
        {
            std::cout << "Costo de camino: " << costo << std::endl;
            return orden_visita;
        }

        auto& aristas = mapa[nodoActual].getAristas();

        for (auto& arista : aristas)
        {
            if ((visitados.find(arista.destino) == visitados.end()) && std::stof(arista.peso) < menor)
            {
                menor = std::stof(arista.peso);
                destino = arista.destino;
            }
        }

        visitados.insert(destino);
        cola.push(destino);
        costo += menor;
    }
    
    return {};
}

#endif