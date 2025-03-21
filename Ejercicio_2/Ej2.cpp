#include "Ej2.h"
#include <iostream>
#include <fstream>

using namespace std;

enum class ETIQUETAS : uint8_t {ERROR,DEBUG, INFO, WARNING,CRITICAL, INVALID};

/*
El ejercicio pide varias funciones con el mismo nombre pero diferentes paramétros,
para esto utilizamos sobrecarga de funciones, en la cual usamos distintas funciones
llamadas igual pero con distintos tipos de parametros para diferenciarlas. De 
esta manera, a la hora de llamarla el programa va a saber cual usar según que 
tipo se le pase. 

El procedimiento que utilice fue primero mediante switch plantear un menu para
seleccionar cual subitem de la consigna se desea realizar. En caso de seleccionar
el 1ro que es el de ingresar el nivel de seguridad, se lo pide que lo ingrese por 
pantalla. Las complicaciones que surgen de esto es que si le pasamos ese dato directo
a la función logmessage estaría yendo a la incorrecta. Debido a que si llamamos con 
un string podría ser esa función como la del item 3(la que hace el chequeo del usuario, 
también pide por parametro un string). Por eso, utilizamos un enum para comprobar 
que sea uno de los casos que queremos evaluar de severidad. En caso de que se ingrese
un valor invalido se vuelve a llamar hasta ingresar uno correcto. Luego de tener el 
valor correcto en int se llama al logmessage correspondiente ya para escribir en el 
archivo el error ingresado. Sin embargo, si nosotros utilizamos el valor actual de 
severidad estaríamos escribiendo el valor entero asociado al dato en vez de el dato 
en sí. Por lo que debemos pasar este dato a string nuevamente (enum_to_string()).
*/

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
    //Verificamos que severidad este dentro de nuestro enum, en caso de que no salta error
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
        //Menu de opciones de que subitem elegir
        switch(op){
            case 1:{
                //Subitem 1: niveles de seguridad precargados.
                string severidad;
                bool valid = true;
                ETIQUETAS enum_severidad;
                while(valid){
                    cout << "Ingrese la etiqueta de severidad:" <<" ";
                    cin >> severidad;
                    //en caso de que el valor ingresado de severidad es inválido (no pertenece al enum) se repite el while
                    //cuando se logre un valor correcto cambiamos a válido a falso para que identifique que ya se ingreso 
                    //un valor con el que podemos seguir, es válido.
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
                //Caso 2: se ingresa el nombre de error, archivo y linea.
                string file;
                int error_line;
                cout << "Ingrese el nombre de su error, el nombre del archivo y la linea de código donde se encontraba el error:" << " ";
                cin >> msg>> file >>error_line;
                logmessage(msg,file,error_line);
                break;
            }
            case 3:{
                //Caso 3: Prueba de ingreso de un usuario.
                string username;
                cout << "Ingrese el usuario y el mensaje de acceso: "<< " ";
                cin >> username >> msg;
                logmessage(msg, username);
                break;
            }
            case 4:{
                //Caso 4: Prueba del runtime error.
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
        //Cuando se termina de realizar una operación se consulta realizar otra 
        //Se usa try y catch para comprobar que el usuario no ingrese mal los 
        //comandos para cortar el programa o seguir operando.
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