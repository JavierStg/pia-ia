#ifndef COSTOUNIFORME_HPP
#define COSTOUNIFORME_HPP

#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include "../nodo.hpp"

std::vector<std::string> costoUniforme(std::unordered_map<std::string, Nodo> &mapa, std::string inicio, std::string objetivo)
{
    std::vector<std::pair<float, std::string>> cola;
    std::unordered_set<std::string> visitados;
    std::string nodoActual;
    std::unordered_map<std::string, std::pair<std::string, float>> padre;
    std::unordered_map<std::string, float> costo_acumulado;

    float menor, costo;
    size_t posicion;

    cola.push_back({0.0f, inicio});
    costo_acumulado[inicio] = 0;

    while (!cola.empty())
    {
        menor = 9999999999;
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

        if (visitados.count(nodoActual)) 
            continue;

        visitados.insert(nodoActual);

        if (nodoActual == objetivo)
        {
            std::vector<std::string> camino;
            std::string actual = objetivo;

            costo = costo_acumulado[objetivo];

            while (actual != inicio)
            {
                camino.push_back(actual);
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
            float peso = std::stof(arista.peso);
            float nuevo_costo = costo_acumulado[nodoActual] + peso;

            if (costo_acumulado.find(arista.destino) == costo_acumulado.end()
                || nuevo_costo < costo_acumulado[arista.destino])
            {
                costo_acumulado[arista.destino] = nuevo_costo;

                cola.push_back({nuevo_costo, arista.destino});

                padre[arista.destino] = {nodoActual, peso};
            }
        }
    }
    
    return {};
}

#endif