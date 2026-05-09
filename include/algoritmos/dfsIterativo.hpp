#ifndef DFSITERATIVO_HPP
#define DFSITERATIVO_HPP

#include <iostream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include "../nodo.hpp"
#include <algorithm>

std::vector<std::string> dfsIterativo(std::unordered_map<std::string, Nodo> &mapa, std::string inicio, std::string objetivo)
{
    std::unordered_set<std::string> visitadosAnterior, visitadosAnterior2;

    float costo = 0;
    size_t l = 0;

    do
    {
        std::stack<std::string> pila;
        std::unordered_set<std::string> visitados;
        std::string nodoActual;
        std::unordered_map<std::string, std::pair<std::string, float>> padre; //nodo, padre, peso
        std::unordered_map<std::string, size_t> profundidad;

        pila.push(inicio);
        profundidad[inicio] = 0;
        padre[inicio] = {"", 0};
        visitadosAnterior2 = visitadosAnterior;

        while (!pila.empty())
        {
            nodoActual = pila.top();        
            pila.pop();

            if (profundidad.find(nodoActual) == profundidad.end())
                profundidad[nodoActual] = profundidad[padre[nodoActual].first] + 1;

            if (!visitados.count(nodoActual) && profundidad[nodoActual] <= l)
            {
                visitados.insert(nodoActual);

                if (nodoActual == objetivo)
                {
                    std::cout << "Profundidad: " << profundidad[nodoActual] << std::endl;
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

                
                auto &aristas = mapa[nodoActual].getAristas();

                for (auto &arista : aristas)
                {
                    if (visitados.find(arista.destino) == visitados.end())  
                    {
                        pila.push(arista.destino);
                        
                        if (padre.find(arista.destino) == padre.end())
                            padre[arista.destino] = {nodoActual, std::stof(arista.peso)};

                        if (profundidad.find(arista.destino) != profundidad.end() && 
                            profundidad[arista.destino] < profundidad[padre[nodoActual].first] + 1)
                        {
                            std::string actual = arista.destino;
                            u_int8_t profundidad2 = 0;

                            while (actual != inicio)
                            {
                                actual = padre[actual].first;
                                profundidad2++;
                            }

                            profundidad[arista.destino] = profundidad2;
                        }
                    }
                }
            }
        }
        l++;
        visitadosAnterior = visitados;

    } while (visitadosAnterior2 != visitadosAnterior); //si son iguales implica que en la iteracion anterior como en la actual no se descubrio un nuevo nodo
    
    return {};
}

#endif