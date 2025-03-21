#include <iostream>
#include <string>
#include <chrono>

using namespace std;

int len(char* word){
    int len = 0;
    while(word[len]){
        len++;
    }
    return len;
}

consteval int len(const char* word){
    int len = 0;
    while(word[len]){
        len++;
    }
    return len;
}

bool compare(char* word1, char* word2, int idx){
    //Caso base: son iguales
    if(idx == len(word1) && idx == len(word2)){
        return true;
    }

    //En caso de que no haya conseguido el caso base y deba seguir iterando antes debo considerar varias alternativas
    //1. Chequear no haber llegado al final de uno de los strings y del otro no
    if((idx == len(word1) && idx <len(word2)) || (idx == len(word2) && idx < len(word1))){
        return false;
    }
    //2. Revisar que no sean distintos  así se puede seguir comprobando
    if(word1[idx] != word2[idx]){
        return false;
    }
    //Si paso todas los casos de que no funciona, vuelvo a llamar a la función para verificar el siguiente caracter
    return compare(word1, word2, idx+1);
}

consteval bool compare_const(char* word1, char* word2, int idx){
    //Caso base: son iguales
    if(idx == len(word1) && idx == len(word2)){
        return true;
    }

    //En caso de que no haya conseguido el caso base y deba seguir iterando antes debo considerar varias alternativas
    //1. Chequear no haber llegado al final de uno de los strings y del otro no
    if((idx == len(word1) && idx <len(word2)) || (idx == len(word2) && idx < len(word1))){
        return false;
    }
    //2. Revisar que no sean distintos  así se puede seguir comprobando
    if(word1[idx] != word2[idx]){
        return false;
    }
    //Si paso todas los casos de que no funciona, vuelvo a llamar a la función para verificar el siguiente caracter
    return compare(word1, word2, idx+1);
}

int main(){
    auto startTime = chrono::high_resolution_clock::now();
    //miProcesoAMedir();
    
    char word1[] = "Las olas del mar rompen suavemente en la orilla mientras la brisa acaricia la piel";
    char word2[] = "El sol se oculta lentamente detrás de las montañas, pintando el cielo con tonos anaranjados.";
    //cout<<len("Las olas del mar rompen suavemente en la orilla mientras la brisa acaricia la piel")<<endl;
    cout <<compare(word1, word2, 0)<<endl;
    auto endTime = chrono::high_resolution_clock::now();
    auto elapsedTime = chrono::duration_cast<std::chrono::nanoseconds>(
    endTime - startTime);
    cout << "A miProcesoAMedir le tomó: " << elapsedTime.count() << "nanosegundos" <<endl;
    
    compare_const("Las olas del mar rompen suavemente en la orilla mientras la brisa acaricia la piel", "El sol se oculta lentamente detrás de las montañas, pintando el cielo con tonos anaranjados.",0);
    
}