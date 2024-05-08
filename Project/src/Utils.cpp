#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Eigen/Eigen"


using namespace std;
using namespace Eigen;

namespace LibreriaFratture {
bool ImportaCoordinate(const string &filename, FrattureMesh& mesh ){


    ifstream file(filename);
    if(!file.is_open())
    {
        return false;
    }


    //cout<<"apertura corretta del file"<<endl;

    // Ignora la prima riga
    string first_line;
    getline(file, first_line);



    //Lettura del numero di fratture
    // string line;

    // getline(file, line);
    // NumberFractures = stoi(line); // Converti la stringa in un intero

    unsigned int NumberFractures;
    file >> NumberFractures ;

    cout<<"il numero di fratture: "<< NumberFractures << endl;





    // Ciclo per leggere i dati di ogni frattura
    for (unsigned int i = 0; i < NumberFractures +1; ++i) {
        // Ignora la riga con scritto "# FractureId; Numvertices"
        string line_fractureid;
        getline(file, line_fractureid);

        // Leggi FractureId e NumVertices
        unsigned int FractureId, NumVertices;
        char separatore;
        istringstream ss_fractureid(line_fractureid);
        ss_fractureid >> FractureId >> separatore >> NumVertices;

        //cout<<" per la frattura con id : " << FractureId << " e numero di vertici " << NumVertices << " le coordinate sono " << endl;
        // guarda bene il cout sopra che qualcosa non torna



        // Ignora la riga con scritto "# Vertices"
        string line_vertices;
        getline(file, line_vertices);






        cout << "matrice " << FractureId << endl;
        MatrixXd coordinate_vertices(3, NumVertices);

        // Leggi i vertici
        for (unsigned int j = 0; j < NumVertices; ++j) {
            string line;
            getline(file, line);
            // Se la riga inizia con '#', passa alla prossima iterazione del ciclo
            if (line[0] == '#') {
                continue;
            }
            istringstream converter(line);
            string token;

            //vector<double> coordinate(NumVertices);
            for (unsigned int k = 0; k < NumVertices; ++k) {
                //string token;
                if (getline(converter, token, ';')) {

                    //coordinate[k] = stod(token);
                    //cout << "Vertice " << j+1 << ", coordinata " << k+1 << ": " << coordinate[k] << endl;
                    coordinate_vertices(j,k) = stod(token);
                    //cout << coordinate_vertices(j,k) << endl;

                }
            }
        }

        mesh.CoordinateFratture[FractureId] = coordinate_vertices;
     }

    mesh.NumeroFratture = NumberFractures;

    file.close();

    return true;
}



// bool CalcoloCentriSfere(FrattureMesh& mesh ){

//     for (const auto& pair : mesh.CoordinateFratture) {
//         const MatrixXd& coordinate_vertices = pair.second;
//         unsigned int FractureId = pair.first;
//         unsigned int NumVertices = coordinate_vertices.cols(); // Numero di vertici del poligono
//         MatrixXd puntiSfera = MatrixXd::Zero(NumVertices,NumVertices);
//         VectorXd quadrati= VectorXd::Zero(NumVertices);
//         for(unsigned int i = 0; i < NumVertices; i++){

//             double sommaPotenze = 0;
//             // cout<<coordinate_vertices(0,i)<<endl;
//             // cout<<coordinate_vertices(1,i)<<endl;
//             // cout<<coordinate_vertices(2,i)<<endl;
//             sommaPotenze = pow(coordinate_vertices(0,i),2)+pow(coordinate_vertices(1,i),2)+pow(coordinate_vertices(2,i),2);
//             //cout<<sommaPotenze<<endl;
//             quadrati(i)= - sommaPotenze;


//             //quadrati.col(i) << - sommaPotenze;

//             puntiSfera.col(i) << coordinate_vertices(0,i), coordinate_vertices(1,i), coordinate_vertices(2,i), 1;
//         }
//         //cout<<quadrati<<endl;
//         VectorXd xPALU = puntiSfera.fullPivLu().solve(quadrati);

//         mesh.CoordinateCentro[FractureId] = xPALU;
//     }

//     return true;
// }

bool EquazioneDelPiano(FrattureMesh& mesh){
    VectorXd parametri_piano;
    for (const auto& pair : mesh.CoordinateFratture) {
        const MatrixXd& coordinate_vertices = pair.second;
        // Trova due vettori direttori non paralleli contenuti nel piano
        Vector3d AB = coordinate_vertices.col(1) - coordinate_vertices.col(0); // Considera la colonna 1 come il vertice B e la colonna 0 come il vertice A
        Vector3d AC = coordinate_vertices.col(2) - coordinate_vertices.col(0); // Considera la colonna 2 come il vertice C e la colonna 0 come il vertice A

        // Calcola il vettore normale al piano utilizzando il prodotto vettoriale
        Vector3d normale = AB.cross(AC);

        // Calcola il termine costante dell'equazione del piano
        double D_term = -coordinate_vertices.col(0).dot(normale);
        parametri_piano(0)=normale(0);
        parametri_piano(1)=normale(1);
        parametri_piano(2)=normale(2);
        parametri_piano(3)=D_term;


        // Stampa l'equazione del piano
        std::cout << "Per la frattura " << pair.first << ", l'equazione del piano : " << normale.transpose() << " * (x, y, z) + " << D_term << " = 0" << std::endl;
    }
    return true;
}


}



















