#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Datos.cpp"

using namespace std;

//Algoritmo de ordenamiento por fusion(Merge) Division & Fusion.

void merge(vector<datos> &lista, int low, int m, int high){
  vector<datos> temp;
  
  int i, j;
  i = low;
  j = m+1;
  
  while ( i <= m && j <= high){

    if (lista[i] <= lista[j]){
      temp.push_back(lista[i]);
      i++;
    } else {
      temp.push_back(lista[j]);
      j++;
    }
  }

  while (i <= m){
      temp.push_back(lista[i]);
      i++;
  }
  while (j <= high){
      temp.push_back(lista[j]);
      j++;
  }
  for(int i = low; i<= high; i++)
    lista[i] = temp[i-low];
}

//Algoritmo de ordenamiento por fusion(Merge) 
//Complejidad temporal O(n log n)
void ordenaMerge(vector<datos>& lista, int low, int high){
  if (low<high) {
    int m = (low + high) / 2;
    ordenaMerge(lista, low, m);
    ordenaMerge(lista, m+1, high);
    merge(lista, low, m, high);
  }
}

/*Siento que es posible usar polimorfismo y sobrecarga para reutilizar el codigo que tenemos para la clase datos.
sin tener que volver a escribir todo esto o usar otro metodo.*/
time_t getFecha(string fecha){ 
  int dia, horas, minutos, segundos;
  string mes;
  vector<string> meses = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
  struct tm dateStruct;
  mes = fecha.substr(0,fecha.find(" "));
  dia = stoi(fecha.substr(3,fecha.find(" ")));
  horas = stoi(fecha.substr(6,fecha.find(":")));
  minutos = stoi(fecha.substr(10,fecha.find(":")));
  segundos = stoi(fecha.substr(13,fecha.find(":")));

  dateStruct.tm_sec = segundos;
  dateStruct.tm_min = minutos;
  dateStruct.tm_hour = horas;
  dateStruct.tm_mday = dia;
  for (int i=0; i<meses.size(); i++){
      if (meses[i]==mes)
       dateStruct.tm_mon = i;
  }
  dateStruct.tm_year = 2021 - 1900;
  return mktime(&dateStruct);

}
 
//funcion de busqueda binaria recursiva.
int binarySearch(vector<datos>& lista, int left, int right, datos key){
  int m;
  if (left > right){
    return -1;
  }
  m = left + (right-1)/2;
  if (key == lista[m]){
    return m;
  } else if(key < lista[m]){
    return binarySearch(lista, left, m-1, key);
  } else {
    return binarySearch(lista, m+1, right, key);
  }

}

int main(){
    vector<datos> info;
    string input, fecha, mes;
    ifstream archivoIn("bitacora.txt");
    int dia, horas, minutos, segundos;
    time_t date;
    while(getline(archivoIn,input)){
      info.push_back(datos(input));
    }
    archivoIn.close();
    info[0].imprimir();
    ordenaMerge(info,0,info.size()-1);

    /*for (int i=0; i<info.size();i++){
      info[i].imprimir();
      cout<<endl;
    } */
    
    //pedimos al usuario fechas para delimitar la busqueda
    cout<<"Introduce la fecha inicial de la busqueda con el formato de la bitacora:"<<endl;
    getline(cin,fecha); 
    date = getFecha(fecha);

    cout<<"Introduce la fecha limite de la busqueda con el formato de la bitacora:"<<endl;
    getline(cin,fecha); 
    date = getFecha(fecha);

    //obtenemos la posicion de inicio y de fin de los datos a depsplegar con busqueda binaria
    int posInicial, posFinal;
    posInicial = binarySearch(info, 0, info.size()-1, date);

    return 0;
}