#ifndef GRAFO_HPP 
#define GRAFO_HPP

#include <iostream>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <vector>
#include "./nodo.hpp"

class Grafo
{
    private:
        std::unordered_map<std::string, Nodo> mapa;

    public:        
        Grafo(std::string archivo_txt)
        {
            std::ifstream archivo(archivo_txt);
            std::string linea, subcadena, subsubcadena, valor;
            std::size_t posicion, inicio = 0, subinicio;
            u_int8_t comas;
            std::vector<std::string> colaVecinos, colaPesos, colaHeuristicas;

            while (getline(archivo, linea)) 
            {
                inicio = 0;
                comas = 0;
                Nodo nodo;

                while ((posicion = linea.find(',', inicio)) != std::string::npos)
                {
                    subinicio = 1;
                    subcadena = linea.substr(inicio, posicion - inicio);
                    
                    switch (comas)
                    {
                    case 0:
                        nodo.setNombre(subcadena);
                        break;
                    
                    case 1:
                        leerLinea(colaVecinos, subcadena, subinicio);
                        break;

                    case 2:
                        leerLinea(colaPesos, subcadena, subinicio);
                    }

                    inicio = posicion + 1;                    
                    comas++;
                }
                subcadena = linea.substr(inicio);
                subinicio = 1;

                leerLinea(colaHeuristicas, subcadena, subinicio);
                
                if (colaVecinos.size() != colaPesos.size() || colaPesos.size() != colaHeuristicas.size())
                    throw std::runtime_error("No hay la misma cantidad de vecinos, pesos y heuristicas...");

                while (!colaVecinos.empty())
                {
                    try
                    {
                        nodo.setArista(colaVecinos[0], colaPesos[0], colaHeuristicas[0]);
                        colaVecinos.erase(colaVecinos.begin());
                        colaPesos.erase(colaPesos.begin());
                        colaHeuristicas.erase(colaHeuristicas.begin());
                    }
                    catch(const std::exception &e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                    
                }

                mapa[nodo.getNombre()] = nodo;
            }
        }

        void addNode(Nodo nodo)
        {
            mapa[nodo.getNombre()] = nodo;
        }

        void connectNode(std::string nodo1, std::string nodo2, std::string peso, std::string heuristica)
        {
            mapa[nodo1].setArista(nodo2, peso, heuristica);
            mapa[nodo2].setArista(nodo1, peso, heuristica);
        }

        void verGrafo()
        {
            for (auto& [clave, nodo] : mapa)
            {
                std::cout << "Nodo: " << nodo.getNombre() << " -> {";

                auto& aristas = nodo.getAristas();
                bool primero = true;

                for (auto& arista : aristas)
                {
                    if (!primero) 
                        std::cout << ", ";
                    
                    std::cout << "(" << arista.destino << ", " << arista.peso << ", " << arista.heuristica << ")";
                    
                    primero = false;
                }
                std::cout << "}" << std::endl;
            }
        }

        std::unordered_map<std::string, Nodo> &getMapa()
        {
            return this->mapa;
        }

        void leerLinea (std::vector<std::string> &cola, std::string &subcadena, std::size_t &subinicio)
        {
            size_t subposicion;
            std::string subsubcadena;

            while ((subposicion = subcadena.find(' ', subinicio)) != std::string::npos)
            {
                subsubcadena = subcadena.substr(subinicio, subposicion - subinicio);
                cola.push_back(subsubcadena);
                subinicio = subposicion + 1;
            }
            subsubcadena = subcadena.substr(subinicio);
            cola.push_back(subsubcadena);
        }
};
#endif