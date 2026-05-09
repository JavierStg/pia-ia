#ifndef ASTAR_HPP
#define ASTAR_HPP

#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>
#include "../nodo.hpp"

std::vector<std::string> aStar(std::unordered_map<std::string, Nodo> &mapa, std::string inicio, std::string objetivo)
{
    std::vector<std::pair<std::pair<float, float>, std::string>> cola; // peso, heuristica, nodo
    std::unordered_set<std::string> frontera;
    std::string nodoActual;
    std::unordered_map<std::string, std::pair<std::string, float>> padre; //nodo, padre, peso
    std::unordered_map<std::string, float> g; //costo acumulado de un nodo

    float costo = 0, menor;
    size_t posicion;
    

    cola.push_back({{0.0f, 0.0f}, inicio});
    frontera.insert(inicio);
    padre[inicio] = {"", 0};
    g[inicio] = 0;


    while (!cola.empty())
    {
        menor = 9999999999;
        posicion = 0;

        for (size_t i = 0; i < cola.size(); i++)
        {
            if (cola[i].first.first + cola[i].first.second< menor)
            {
                menor = cola[i].first.first + cola[i].first.second;
                posicion = i;
            }
        }

        nodoActual = cola[posicion].second;
        cola.erase(cola.begin() + posicion);
        frontera.erase(nodoActual);

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
            float gAcumulado = g[nodoActual] + std::stof(arista.peso);

            if (g.find(arista.destino) == g.end() || gAcumulado < g[arista.destino])
            {
                g[arista.destino] = gAcumulado;

                frontera.insert(arista.destino);
                cola.push_back({{gAcumulado, std::stof(arista.heuristica)}, arista.destino});
                padre[arista.destino] = {nodoActual, std::stof(arista.peso)};
            }
        }
    }
    
    return {};
}

#endif