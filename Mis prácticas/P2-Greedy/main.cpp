/* 
 * File:   main.cpp
 * Author: fran
 *
 * Created on 17 de mayo de 2016, 8:49
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// e -> vector con los elementos (peso, beneficio)
// n -> número de objetos disponibles
// M -> capacidad de la mochila
// s -> vector solución

////////////////////////////////////////////////////////////////////////////////
// struct para guardar los datos de cada elemento
//
struct Element {
    
    int id;     // identificado
    double w;   // peso
    double p;   // beneficio
    
};

////////////////////////////////////////////////////////////////////////////////
// struct para ordenar los elementos del vector. Se ordena por beneficio/peso
//
struct Compare {
    
  bool operator() (Element e1, Element e2) {
      return e1.p/e1.w > e2.p/e2.w;
  }
  
} comparator;

////////////////////////////////////////////////////////////////////////////////
// Pide los datos del problema
//
void loadData(int &n, double &M, vector<Element> &e);

////////////////////////////////////////////////////////////////////////////////
// Rellena el vector solución en base a un vector de elementos
//
void backpack(vector<double> &s, vector<Element> e, int n, double M);

////////////////////////////////////////////////////////////////////////////////
// Calcula el resultado del algoritmo
//
double getProfit(vector<double> &s, vector<Element> e, int n);

////////////////////////////////////////////////////////////////////////////////
// Muestra que elementos se coge y su proporción
//
void showRes(vector<double> &s, vector<Element> e, int n);

////////////////////////////////////////////////////////////////////////////////
// main
//
int main(int argc, char** argv) {
    
    // Vectores con los pesos y el beneficio
    vector<Element> e;
    
    // Numero de elementos
    int n;
    
    // Capacidad de la mochila
    double M;
    
    // Vector solución
    vector<double> s;
    
    // Resultado total
    double total;
    
    loadData(n, M, e);
    
    // Se ordena el vector siguiendo el criterio de benefio/peso mayor primero
    sort(e.begin(), e.end(), comparator);
    
    // Se llama al algoritmo greedy y s tendrá la solución
    backpack(s, e, n, M);
    
    total = getProfit(s, e, n);
    
    cout << endl;
    
    cout << "\nEl beneficio total es: " << total << endl;
    
    showRes(s, e, n);

    return 0;
    
}

void loadData(int &n, double &M, vector<Element> &e){
    
    double aux1, aux2;
    
    // Se pide la capacidad
    cout << "\nIntroduce la capacidad de la mochila: ";
    
    cin >> M;
    
    // Se pide el número de elementos
    cout << "\nIntroduce el número de elementos a introducir: ";
    
    cin >> n;
    
    cout << endl;
    
    // Se piden todos los pesos y sus beneficios
    for(unsigned int i=0; i<n; i++){
        
        cout << "\nIntroduce el peso y beneficio del elemento " << i+1 << ": ";
        cin >> aux1 >> aux2;
        
        Element element;
        element.id = i+1;
        element.w = aux1;
        element.p = aux2;
        
        e.push_back(element);
        
    }
    
    cout << endl;
    
}

void backpack(vector<double> &s, vector<Element> e, int n, double M){
    
    // Se inicializa el vector solución a 0
    for(unsigned int i=0; i<n; i++){
        s.push_back(0);
    }
    
    // Se inicializa el peso actual de la mochila
    double weight = 0;
    
    // Contador para no sobrepasar el tamaño del vector
    unsigned int i = 0;
    
    // Se recorrerán todos los elementos del vector hasta que la mochila
    // esté completa
    while(weight < M){
        
        // Se guarda el mejor elemento restante
        double bestW = e[i].w;
        
        // Si el peso actual + peso del objeto es menor o igual a la capacidad
        // de la mochila se introduce al completo
        if(weight + bestW <= M){
            s[i] = 1;
            // Se debe actualizar el peso actual
            weight += bestW;
            
        // Si no se puede coger al completo, se introduce la parte 
        //correspondiente
        } else{
            
            // Se guarda el % de peso que se coge del último elemento
            s[i] = (M - weight) / bestW;
            
            // El peso actual es el total de la capacidad
            weight = M;
            
        }
        
        i++;
        
    }
    
}

double getProfit(vector<double> &s, vector<Element> e, int n){
    
    double total = 0;
    
    for(unsigned int i=0; i<n; i++){
        
        if(s[i] != 0){
            
            total += s[i]*e[i].p;
            
        }
        
    }
    
    return total;
    
}

void showRes(vector<double> &s, vector<Element> e, int n){
    
    cout << "\nSe coge el elemento número:\n";
    
    for(unsigned int i=0; i<n; i++){
        
        if(s[i] != 0){
            
            cout << "   " << e[i].id << " y el " << s[i]*100 << "%.\n";
            
        }
        
    }
    
    cout << endl;
    
}