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











}





