#ifndef DFS_HPP
#define DFS_HPP

#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include "../nodo.hpp"

std::vector<std::string> dfs(std::unordered_map<std::string, Nodo> &mapa, std::string inicio, std::string objetivo)
{
    std::stack<std::string> pila;
    std::vector<std::string> orden_visita;
    std::unordered_set<std::string> visitados;
    std::string nodoActual;

    pila.push(inicio);
    visitados.insert(inicio);
    orden_visita.push_back(inicio);
    float costo = 0;

    while (!pila.empty())
    {
        nodoActual = pila.top();

        if (nodoActual == objetivo)
        {
            std::cout << "Costo de camino: " << costo << std::endl;
            return orden_visita;
        }

        bool encontroCamino = false;
        auto& aristas = mapa[nodoActual].getAristas();

        for (auto& arista : aristas)
        {
            if (visitados.find(arista.destino) == visitados.end())
            {
                visitados.insert(arista.destino);
                orden_visita.push_back(arista.destino);
                costo += std::stof(arista.peso);
                
                pila.push(arista.destino);
                encontroCamino = true;
                break;
            }
        }

        if (!encontroCamino)
        {
            pila.pop();
        }
    }
    
    return {};
}

#endif