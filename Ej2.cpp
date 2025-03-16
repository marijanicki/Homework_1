#include <iostream>
#include <fstream>

using namespace std;

enum class ETIQUETAS : uint8_t {ERROR,DEBUG, INFO, WARNING,CRITICAL, iNVALID};
void logmessage(string msg, ETIQUETAS severidad){

    ofstream outFile("Registro_funcionamiento.txt", ios::app);
    if(outFile.is_open()){
        outFile <<"[" << static_cast<int>(severidad) << "] <" <<msg <<">\n";
    }
}

void logmessage(string msg, string file, int error_line){
    ofstream outFile("Registro_funcionamiento.txt", ios::app);
    if(outFile.is_open()){
        outFile <<"[ERROR] <" << msg <<"> Archivo:" << file << ". Linea del error:"<<error_line<<"\n";
    }
}

void logmessage(string access_msg, string username){
    ofstream outFile("Registro_funcionamiento.txt", ios::app);
    if(outFile.is_open()){
        outFile <<"[SEGURIDAD]" <<access_msg <<">\n";
    }
}
ETIQUETAS make_enum_element(string severidad){
    try{
        if(severidad == "ERROR" || severidad == "error"){
            return ETIQUETAS::ERROR;
        }
        if(severidad == "DEBUG" || severidad == "ERROR"){
            return ETIQUETAS::DEBUG;
        }
        if(severidad == "INFO" || severidad == "ERROR"){
            return ETIQUETAS::INFO;
        }if(severidad == "WARNING" || severidad == "ERROR"){
            return ETIQUETAS::WARNING;
        }if(severidad == "CRITICAL" || severidad == "critical"){
            return ETIQUETAS::CRITICAL;
        }
        else{
            throw runtime_error("Caso invalido! Etiqueta de severidad no existente");
        }
    }
    catch(const runtime_error& e){
        cout << "Runtime error:" << e.what() <<endl;
        return ETIQUETAS::iNVALID;
    }
    
}

int main(){
    string severidad;
    string msg;
    bool valid = true;
    ETIQUETAS enum_severidad;
    while(valid){
        
        cout << "Ingrese la etiqueta de severidad:" <<" ";
        cin >> severidad;
        enum_severidad = make_enum_element(severidad);
    }
    cout << "Ingrese el mensaje:" <<" ";
    cin >> msg;
    logmessage(msg, enum_severidad);

    try{
        string a;
        string b;
        cin >> a;
        cin >> b;
        if(a == b){
            throw "Numeros distintos";
        }
    }catch(const char* e){
        logmessage(e, ETIQUETAS::ERROR);
    }

}