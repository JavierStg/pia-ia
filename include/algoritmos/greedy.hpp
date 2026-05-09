#ifndef GREEDY_HPP
#define GREEDY_HPP

#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>
#include "../nodo.hpp"

std::vector<std::string> greedy(std::unordered_map<std::string, Nodo> &mapa, std::string inicio, std::string objetivo)
{
    std::vector<std::pair<float, std::string>> cola; //peso, nodo
    std::unordered_set<std::string> visitados, frontera;
    std::string nodoActual;
    std::unordered_map<std::string, std::pair<std::string, float>> padre; //nodo, padre, peso
    float costo = 0, menor;
    size_t posicion;

    cola.push_back({0.0f, inicio});
    frontera.insert(inicio);
    padre[inicio] = {"", 0};

    while (!cola.empty())
    {
        menor = __FLT_MAX__;

        posicion = 0;

        for (size_t i = 0; i < cola.size(); i++)
        {
            if (cola[i].first < menor)
            {
                menor = cola[i].first;
                posicion = i;
            }
        }

        nodoActual = cola[posicion].second;
        cola.erase(cola.begin() + posicion);
        frontera.erase(nodoActual);

        visitados.insert(nodoActual);


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
            if ((visitados.find(arista.destino) == visitados.end()) && frontera.find(arista.destino) == frontera.end())
            {
                frontera.insert(arista.destino);
                cola.push_back({std::stof(arista.heuristica), arista.destino});
                padre[arista.destino] = {nodoActual, std::stof(arista.peso)};
            }
        }
    }
    
    return {};
}

#endif