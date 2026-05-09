#ifndef DFS_HPP
#define DFS_HPP

#include <iostream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include "../nodo.hpp"
#include <algorithm>

std::vector<std::string> dfs(std::unordered_map<std::string, Nodo> &mapa, std::string inicio, std::string objetivo)
{
    std::stack<std::string> pila;
    std::unordered_set<std::string> visitados;
    std::string nodoActual;
    std::unordered_map<std::string, std::pair<std::string, float>> padre; //nodo, padre, peso

    pila.push(inicio);
    float costo = 0;

    while (!pila.empty())
    {
        nodoActual = pila.top();        
        pila.pop();

        if (visitados.count(nodoActual) == 0)
        {
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
                if (visitados.find(arista.destino) == visitados.end())  
                {
                    pila.push(arista.destino);
                    
                    if (padre.find(arista.destino) == padre.end())
                        padre[arista.destino] = {nodoActual, std::stof(arista.peso)};
                }
            }
        }
    }
    
    return {};
}

#endif