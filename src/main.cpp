#include "../include/grafo.hpp"
#include "../include/algoritmos/bfs.hpp"

int main()
{
    Grafo grafo("./grafo.txt");
    u_int8_t opcion;
    std::string inicio, objetivo;
    std::vector<std::string> camino;

    do
    {
        do
        {
            std::cout << R"(Ingrese una opcion
            a) BFS
            b) Costo uniforme
            c) DFS
            d) DFS limitado
            e) DFS iterativo
            f) Greedy Search
            g) A*
            h) Mostrar conexiones
            i) Salir
            Opcion: )";

            std::flush(std::cout);
            std::cin >> opcion;

            if(opcion < 'a' || opcion >'i')
                std::cout << "\nIngrese una opcion correcta\n" << std::endl;

        } while (opcion < 'a' || opcion >'i');
        
        if (opcion != 'h' && opcion != 'i')
        {
            std::cout << "Estado inicial: ";
            std::cin >> inicio;
            std::cout << "\nEstado objetivo: ";
            std::cin >> objetivo;
        }

        std::cout << "\n" << std::endl;

        switch (opcion)
        {
        case 'a':
            camino = bfs(grafo.getMapa(), inicio, objetivo);
            break;

        case 'b':
            break;

        case 'h':
            std::cout << std::endl;
            grafo.verGrafo();
            std::cout << std::endl;
            break;
        }
        
        if (opcion != 'h' && opcion != 'i')
        {

            if (camino.size() == 0)
                std::cout << "No se encontro una solucion" << std::endl;
            else
            {
                bool primero = true;
                for (u_int8_t i = 0; i < camino.size(); i++)
                {
                    if (!primero && i != camino.size())
                        std::cout << " -> ";
                    
                    std::cout << camino[i];
                    primero = false;
                }
            } 
        }

        std::cout << "\n" << std::endl;

    } while (opcion != 'i');
    
    
    return EXIT_SUCCESS;
}

