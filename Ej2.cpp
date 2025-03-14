#include <iostream>
#include <fstream>

using namespace std;

enum class ETIQUETAS : uint8_t {ERROR,DEBUG, INFO, WARNING,CRITICAL};
void logmessage(){
    string msg;

    ofstream outFile("Registro_funcionamiento.txt");
    if(outFile.is_open()){

    }
}

