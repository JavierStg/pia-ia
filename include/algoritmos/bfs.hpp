#ifndef BFS_HPP
#define BFS_HPP

#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include "../nodo.hpp"
#include <queue>

std::vector<std::string> bfs(std::unordered_map<std::string, Nodo> mapa, std::string inicio, std::string objetivo)
{
    std::queue<std::string> cola;
    std::unordered_set<std::string> visitados;
    std::vector<std::string> orden_visita;
    std::string nodoActual;
    float costo = 0;

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
            if (visitados.find(arista.destino) == visitados.end())
            {
                visitados.insert(arista.destino);
                cola.push(arista.destino);
                costo += std::stof(arista.peso);
            }
        }
    }
    
    return {};
}

#endif