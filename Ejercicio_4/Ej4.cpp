#include "Ej4.h"
#include <iostream>
#include <chrono>

using namespace std;

/*
ELECCIÓN DE STRING VS CHAR*

Utilicé char* debido a múltiples razones: memoria, tiempo, realización de procesos
por compilacion. Al comparar la velocidad entre ambas variables el char* es
muchisimo más rápido que string. A su vez, string tiene memoria dinamica
y char* del tipo estática por esto, si tenemos en cuenta el item c de esta actividad,
si utilizaba el tipo string me iba a encontrar con el problema de que no es válido para 
realizar una evaluación en tiempo de compilación. Esto es debido a que el
calificador constexpr se utiliza recibiendo parametros constantes, como son los 
char* a diferencia de los string que no son variables fijas. Es por esto que definí 
como const char* en vez de char* los parametros de la función "compare()"" .  
*/

constexpr bool compare(const char* word1, const char* word2, int idx){
    //Caso base: son iguales
    if((word1[idx] == '\0') && (word2[idx] == '\0')){
        return true;
    }
    //En caso de que no haya conseguido el caso base y deba seguir iterando antes debo considerar varias alternativas
    //1. Chequear no haber llegado al final de uno de los strings y del otro no
    if((word1[idx] == '\0' && word2[idx] != '\0') || (word2[idx] == '\0' && word1[idx] != '\0')){
        return false;
    }
    //2. Revisar que no sean distintos  así se puede seguir comprobando
    if(word1[idx] != word2[idx]){
        return false;
    }
    //Si paso todas los casos de que no funciona, vuelvo a llamar a la función para verificar el siguiente caracter
    return compare(word1, word2, idx+1);
}

void print_result(bool result){
    if(result){
        cout<<"Ambos textos son iguales"<<endl;
    }
    else{
        cout<<"Los textos son distintos"<<endl;
    }
}


int main(){
    auto startTime = chrono::high_resolution_clock::now();
    char word1[] = "Las olas del mar rompen suavemente en la orilla mientras la brisa acaricia la piel";
    char word2[] = "El sol se oculta lentamente detrás de las montañas, pintando el cielo con tonos anaranjados.";
    print_result(compare(word1, word1, 0));
  
    auto endTime = chrono::high_resolution_clock::now();
    auto elapsedTime = chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
    cout << "A la comparación le tomó realizandolo por ejecución: " << elapsedTime.count() << "nanosegundos\n" <<endl;
    
    //Realizando la comparación en compilación
    startTime = chrono::high_resolution_clock::now();
    print_result(compare("Las olas del mar rompen suavemente en la orilla mientras la brisa acaricia la pie", "Las olas del mar rompen suavemente en la orilla mientras la brisa acaricia la pie", 0));
    //cout <<compare("Las olas del mar rompen suavemente en la orilla mientras la brisa acaricia la pie", "El sol se oculta lentamente detrás de las montañas, pintando el cielo con tonos anaranjados.", 0)<<endl;
    endTime = chrono::high_resolution_clock::now();
    elapsedTime = chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
    cout << "A la comparación le tomó realizandolo por compilación: " << elapsedTime.count() << "nanosegundos\n" <<endl;

    //Verifico que funciona también la función cuando se le pasan textos distintos.
    print_result(compare(word1, word2, 0));
}

/*CONCLUSIÓN

Al realizar la comparación en compilación a la hora de correr el código el tiempo de 
ejecución del mismo es muchisimo menor a comparación de cuando sólo se compara en 
ejecución. Esto es debido a que al realizar estos procesos previamente a que se 
corra el programa sólo es necesario ver que resultado brindo e imprimirlo. 
*/
