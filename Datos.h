#ifndef DATOS_H
#define DATOS_H

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>
using namespace std;

class datos {
    private: 
    struct tm dateStruct;
    string mes, razon, ip;
    int dia, horas, minutos, segundos;
    time_t date;
    vector<string> meses = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    public: 
    datos();
    datos(string linea);
    void imprimir(ofstream &o);
    int getDate();
    //sobrecargas de operadores
    bool operator ==(const datos&);
    bool operator ==(const time_t&);
    bool operator !=(const datos&);
    bool operator >(const datos&);
    bool operator <(const datos&);
    bool operator >(const time_t&);
    bool operator <=(const datos&);
};

#endif