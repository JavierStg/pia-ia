#ifndef BFS_HPP
#define BFS_HPP

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>
#include "../nodo.hpp"

std::vector<std::string> bfs(std::unordered_map<std::string, Nodo> &mapa, std::string inicio, std::string objetivo)
{
    std::queue<std::string> cola;
    std::unordered_set<std::string> visitados;
    std::string nodoActual;
    std::unordered_map<std::string, std::pair<std::string, float>> padre;

    cola.push(inicio);
    visitados.insert(inicio);
    float costo = 0;

    while (!cola.empty())
    {
        nodoActual = cola.front();

        cola.pop();

        if (nodoActual == objetivo)
        {
            std::vector<std::string> camino;
            std::string actual = objetivo;

            while (actual != inicio)
            {
                camino.push_back(actual);
                costo += padre[actual].second;
                actual = padre[actual].first;
            }

            camino.push_back(inicio);
            std::reverse(camino.begin(), camino.end());

            std::cout << "Costo de camino: " << costo << std::endl;
            return camino;
        }

        auto& aristas = mapa[nodoActual].getAristas();

        for (auto& arista : aristas)
        {
            if (visitados.find(arista.destino) == visitados.end())
            {
                visitados.insert(arista.destino);
                cola.push(arista.destino);
                padre[arista.destino] = {nodoActual, std::stof(arista.peso)};
            }
        }
    }
    
    return {};
}

#endif