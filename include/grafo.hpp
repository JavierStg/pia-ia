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
            std::size_t posicion, inicio = 0, subposicion, subinicio;
            u_int8_t comas;
            std::vector<std::string> cola;

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
                        while ((subposicion = subcadena.find(' ', subinicio)) != std::string::npos)
                        {
                            subsubcadena = subcadena.substr(subinicio, subposicion - subinicio);
                            cola.push_back(subsubcadena);
                            subinicio = subposicion + 1;
                        }
                        subsubcadena = subcadena.substr(subinicio);
                        cola.push_back(subsubcadena);
                        break;
                    }

                    inicio = posicion + 1;                    
                    comas++;
                }
                subcadena = linea.substr(inicio);
                subinicio = 1;

                while ((subposicion = subcadena.find(' ', subinicio)) != std::string::npos)
                {
                    subsubcadena = subcadena.substr(subinicio, subposicion - subinicio);
                    nodo.setArista(cola[0], subsubcadena);
                    cola.erase(cola.begin());
                    subinicio = subposicion + 1;
                }
                subsubcadena = subcadena.substr(subinicio, subposicion - subinicio);
                nodo.setArista(cola[0], subsubcadena);
                cola.erase(cola.begin());

                mapa[nodo.getNombre()] = nodo;
            }
        }

        void addNode(Nodo nodo)
        {
            mapa[nodo.getNombre()] = nodo;
        }

        void connectNode(std::string nodo1, std::string nodo2, std::string peso)
        {
            mapa[nodo1].setArista(nodo2, peso);
            mapa[nodo2].setArista(nodo1, peso);
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
                    
                    std::cout << "(" << arista.destino << ", " << arista.peso << ")";
                    
                    primero = false;
                }
                std::cout << "}" << std::endl;
            }
        }

        std::unordered_map<std::string, Nodo> &getMapa()
        {
            return this->mapa;
        }
};
#endif