#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Datos.cpp"

using namespace std;

int main(){
    vector<datos> info;
    string input;
    ifstream archivoIn("bitacora.txt");
    while(getline(archivoIn,input)){
        info.push_back(datos(input));
    }
    archivoIn.close();
    info[0].imprimir();

    return 0;
}