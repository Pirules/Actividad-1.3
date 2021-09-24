#include <iostream>
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
 
//funcion de busqueda binaria iterativa.
int binarySearch(vector<datos>& lista, int n, time_t k) {
  int low = 0;
  int high = n - 1;
  while (low <= high) {
    int m = low + (high - low) / 2;
    if (lista[m] == k) return m;
    else if (lista[m] > k) 
      high = m - 1;
    else 
      low = m + 1;
  }
  return -1;
}

int main(){
    vector<datos> info;
    string input, fecha, mes;
    ifstream archivoIn("bitacora.txt");
    int dia, horas, minutos, segundos, posInicial, posFinal;
    time_t dateI, dateF;
    while(getline(archivoIn,input)){
      info.push_back(datos(input));
    }
    archivoIn.close();
    ordenaMerge(info,0,info.size()-1);

    
    //pedimos al usuario fechas para delimitar la busqueda
    cout<<"Introduce la fecha inicial de la busqueda con el formato de la bitacora:"<<endl;
    getline(cin,fecha); 
    dateI = getFecha(fecha);

    cout<<"Introduce la fecha limite de la busqueda con el formato de la bitacora:"<<endl;
    getline(cin,fecha); 
    dateF = getFecha(fecha);
    cout<<endl;

    //obtenemos la posicion de inicio y de fin de los datos a depsplegar con busqueda binaria
    posInicial = binarySearch(info, info.size(), dateI);
    posFinal = binarySearch(info, info.size(), dateF);

    ofstream o ("bitacora_ordenada.txt");
    for (int i=posInicial; i<=posFinal;i++){
      info[i].imprimir(o);
      cout<<endl;
    } 
    o.close();

    return 0;
}