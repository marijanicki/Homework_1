#include "Ej1.h"

#include <iostream>
#include <vector>
using namespace std;

vector<vector<int> > make_mtx(int n){
    vector<vector<int> > mtx(n, vector<int> (n));
    int m = 1;
    for(int i = 0; i < n; i++){
        for(int j = 0; j<n; j++){
            mtx[i][j] = m;
            m++; 
        }
    }
    return mtx;
}
int main(){
    int n; 
    cout << "Ingrese la dimensión de la matriz cuadrada: ";
    cin >> n;
    vector<vector<int> > new_mtx = make_mtx(n);

    for(int m = (n*n)-1; m>=0; m--){
        int i = m/n;
        int j = m%n;
        cout <<"M"<<n<<"["<<i<<"]"<<"["<<j<<"]="<< new_mtx[i][j]<<endl;
    }

    return 0;
}