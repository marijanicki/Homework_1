#include "Ej2.h"
#include <iostream>
#include <fstream>

using namespace std;

enum class ETIQUETAS : uint8_t {ERROR,DEBUG, INFO, WARNING,CRITICAL, iNVALID};

void logmessage(string msg, ETIQUETAS severidad){

    ofstream outFile("Registro_funcionamiento.txt", ios::app);
    if(outFile.is_open()){
        outFile <<"[" << enum_to_string(severidad) << "] <" <<msg <<">\n";
    }
}

void logmessage(string msg, string file, int error_line){
    ofstream outFile("Registro_funcionamiento.txt", ios::app);
    if(outFile.is_open()){
        outFile <<"[ERROR] <" << msg <<"> Archivo:" << file << " Linea del error:"<<error_line<<"\n";
    }
}

void logmessage(string access_msg, string username){
    ofstream outFile("Registro_funcionamiento.txt", ios::app);
    if(outFile.is_open()){
        outFile <<"[SECURITY]" <<"<"<<username <<">"<< access_msg<<"\n";
    }
}
ETIQUETAS make_enum_element(string severidad){
    try{
        if(severidad == "ERROR" || severidad == "error"){
            return ETIQUETAS::ERROR;
        }
        if(severidad == "DEBUG" || severidad == "debug"){
            return ETIQUETAS::DEBUG;
        }
        if(severidad == "INFO" || severidad == "info"){
            return ETIQUETAS::INFO;
        }if(severidad == "WARNING" || severidad == "warning"){
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

string enum_to_string(ETIQUETAS severidad){
    switch(severidad){
        case ETIQUETAS::ERROR: 
            return "ERROR";
        case ETIQUETAS::DEBUG: 
            return "DEBUG";
        case ETIQUETAS::INFO: 
            return "INFO";
        case ETIQUETAS::WARNING: 
            return "WARNING";    
        case ETIQUETAS::CRITICAL: 
            return "CRITICAL";
        default:
            return "INVALID";
    }
}

int main(){
    int op;
    string msg;
    char menu;
    bool inicio = true;
    while(inicio){
        cout << "\nEliga la operación que desea registrar:\n1.Severidades comunes: ERROR,DEBUG,INFO,WARNING,CRITICAL\n2.Otros errores\n3.Acceso de usuario\n4.Prueba funcionalidad\n5.SALIR"<<endl;
        cin >> op;
        switch(op){
            case 1:{
                string severidad;
                
                bool valid = true;
                ETIQUETAS enum_severidad;
                while(valid){
                    cout << "Ingrese la etiqueta de severidad:" <<" ";
                    cin >> severidad;
                    enum_severidad = make_enum_element(severidad);
                    if(enum_severidad != ETIQUETAS::iNVALID){
                        valid = false;
                    }
                }
                cout << "Ingrese el mensaje:" <<" ";
                cin >> msg;
                logmessage(msg, enum_severidad);
                break;
            }
            case 2:{
                string file;
                int error_line;
                cout << "Ingrese el nombre de su error, el nombre del archivo y la linea de código donde se encontraba el error:" << " ";
                cin >> msg>> file >>error_line;
                logmessage(msg,file,error_line);
                break;
            }
            case 3:{
                string username;
                cout << "Ingrese el usuario y el mensaje de acceso: "<< " ";
                cin >> username >> msg;
                logmessage(msg, username);
                break;
            }
            case 4:{
                try{
                    string a;
                    string b;
                    cout <<"\n COMPARACIÓN DE STRINGS\nIngrese el valor de la 1ra variable: ";
                    cin >> a;
                    cout <<"Ingrese el valor de la 2da variable: ";
                    cin >> b;
                    if(a != b){
                        throw runtime_error("Strings distintos!");
                    }
                    cout << "Strings iguales!\n";
                }catch(const runtime_error& e){
                    logmessage(e.what(), ETIQUETAS::ERROR);
                    return 1;
                }
                break;
            }
            case 5:
                return 0;
            default:
                cout << "\nIngreso un comando inválido, intente nuevamente.\n";  
        }
        try{
            cout << "¿Desea realizar otra operación? Y/N\n";
            cin >>menu;
            if(menu == 'N' || menu == 'n'){
                cout << "Cerrando...";
                inicio = false;
            }
            else if(menu == 'Y' || menu == 'y'){
                continue;
            }
            else{
                throw "\nComando invalido, escriba 'Y' o 'N'. Vuelva a intentar.\n";
            }
        }
        catch(const char* f){
            cout << f;
        }     
    }  
 
    return 0;
}