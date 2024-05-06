#include <iostream>
#include "Fratture.hpp"
#include "Utils.hpp"

using namespace std;
using namespace Eigen;
using namespace LibreriaFratture;

int main()
{
    FrattureMesh mesh;

    string filepath = "DFN/FR10_data.txt";
    if(!ImportaCoordinate(filepath,
                    mesh))
    {
        return 1;
    }


    //Verifico di aver memorizzato correttamente nella struttura la mappa con la matrice
    // Stampa le coordinate di tutte le fratture
    for (const auto& pair : mesh.CoordinateFratture) {
        unsigned int FractureId = pair.first;
        const MatrixXd& coordinate_vertices = pair.second;

        cout << "FractureId: " << FractureId << endl;
        cout << "Coordinate:\n" << coordinate_vertices << endl;
    }


    return 0;
}
