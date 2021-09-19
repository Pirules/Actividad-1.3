#include "Datos.h"

using namespace std;

datos::datos(){
    this->mes="Jun";
    this->dia=1;
    this->horas=00;
    this->minutos=00;
    this->segundos=00;
    this->ip="111.11.1.11:111";
    this->razon="Esta es la razon";
}

datos::datos(string linea){
    /*Utilizamos substr para subdividir la linea que recibimos del archivo
       y asi guardar nuestaras variables.*/ 
    this->mes = linea.substr(0,linea.find(" "));
    this->dia = stoi(linea.substr(3,linea.find(" ")));
    this->horas = stoi(linea.substr(6,linea.find(":")));
    this->minutos = stoi(linea.substr(10,linea.find(":")));
    this->segundos = stoi(linea.substr(13,linea.find(":")));
    this->ip = linea.substr(16,linea.find("."));
    this->razon = linea.substr(34);
    
    //Guardamos tiempos en dataStruct
    dateStruct.tm_sec = segundos;
    dateStruct.tm_min = minutos;
    dateStruct.tm_hour = horas;
    dateStruct.tm_mday = dia;
    for (int i=0; i<meses.size(); i++){
        if (meses[i]==mes)
         dateStruct.tm_mon = i;
    }
    dateStruct.tm_year = 2021 - 1900;
    this->date = mktime(&dateStruct);
}

void datos::imprimir(){
    cout<<mes<<" ";
    cout<<dia<<" ";
    cout<<horas<<":";
    cout<<minutos<<":";
    cout<<segundos<<" ";
    cout<<ip;
    cout<<razon<<" ";
    cout<<date<<" ";
}

int datos::getDate(){
    return this->date;
}

bool datos::operator==(const datos &other) {
  return this->date == other.date;
}

bool datos::operator!=(const datos &other) {
  return this->date != other.date;
}

bool datos::operator>(const datos &other) {
  return this->date > other.date;
}

bool datos::operator<(const datos &other) {
  return this->date < other.date;
}

bool datos::operator<=(const datos &other) {
  return this->date <= other.date;
}