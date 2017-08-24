/* 
 * File:   main.cpp
 * Author: fran
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

////////////////////////////////////////////////////////////////////////////////
// struct para guardar los datos de cada elemento
//
struct Element {
    
    int id;  // identificado
    int w;   // peso
    int p;   // beneficio
    
};

////////////////////////////////////////////////////////////////////////////////
// Inicialización de la matriz resultado
//
void init(vector<vector<int> > &results, vector<Element> &e, vector<int> &x, 
        int &M, int &n);

////////////////////////////////////////////////////////////////////////////////
// Rellena la matriz con los subproblemas
//
void fillBackpack(vector<vector<int> > &V, vector<Element> e, int n, int M);

////////////////////////////////////////////////////////////////////////////////
// Rellena el vector solución
//
void fillSolution(const vector<vector<int> > &V, const vector<Element> &e,
        vector<int> &x, int n, int M);

////////////////////////////////////////////////////////////////////////////////
// main
//
int main(int argc, char** argv) {
    
    // Matriz con los resultados de los subproblemas
    vector<vector<int> > V;
    
    // Capacidad de la mochila
    int M;
    
    // Número de elementos
    int n;
    
    // Vector con los pesos y su beneficio
    vector<Element> e;
    
    // Vector con la solución
    vector<int> x;
    
    // Se piden los datos y se inicializa la matriz con los resultados
    init(V, e, x, M, n);
    
    fillBackpack(V, e, n, M);
    
    // Ver la matriz rellena
    /*for(unsigned int i=0; i<=n; i++){
        
        cout << endl;
    
        for(unsigned int j=0; j<=M; j++){
                        
            cout << V[i][j] << " ";
             
        }
            
    }*/
    
    fillSolution(V, e, x, n, M);
    
    cout << endl << "El beneficio máximo es " << V[n][M] << endl << endl;
    
    cout << "Los elementos que se deben coger son el número: ";
    
    for(int i=0; i<n; i++){
        
        if(x[i] == 1){
            
            cout << i+1;
            
            if(i!=n-1){
                cout << ", ";
            }
            
        }
        
    }
    
    cout << endl;

    return 0;
    
}

void init(vector<vector<int> > &V, vector<Element> &e, vector<int> &x, 
        int &M, int &n){
    
    int aux1, aux2;
    
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
    
    // Se inicializa la matriz NxM con 0
    for(unsigned int i=0; i<=n; i++){
        
        vector<int> row;
        
        for(unsigned int j=0; j<=M; j++){
            
            row.push_back(0);
            
        }
        
        V.push_back(row);
        
    }
    
    // Se inicializa a 0 el vector solución
    for(int i=0;i<n; i++){
        x.push_back(0);
    }
    
}

void fillBackpack(vector<vector<int> > &V, vector<Element> e, int n, int M){
    
    for(int i=1; i<=n; i++){
    
        for(int j=1; j<=M; j++){
                        
            // El bucle for empieza en n, pero el vector de elementos
            // tiene tamaño n-1, por esto se le resta 1 a la posición del vector
            if(j-e[i-1].w < 0){                
                V[i][j] = V[i-1][j];
            } else{
                V[i][j] = max(V[i-1][j], e[i-1].p + V[i-1][j-e[i-1].w]);
            }
             
        }
            
    }
        
}

void fillSolution(const vector<vector<int> > &V, const vector<Element> &e, 
        vector<int> &x, int n, int M){
    
    // Se recoge el peso máximo de la mochila
    int j = M;
        
    // Se recorre la matriz para comprobar los resultados
    for(int i = n; i>=1; i--){
        
        if(V[i][j] != V[i-1][j]){
         
            // El bucle for empieza en n, pero el vector solución y de elementos
            // tiene tamaño n-1, por esto se le resta 1 a la posición del vector
            x[i-1] = 1;
            j = j-e[i-1].w;
            
        }
        
    }
    
}