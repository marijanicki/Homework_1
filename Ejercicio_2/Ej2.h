#include <iostream>
#include <fstream>

using namespace std;

enum class ETIQUETAS : uint8_t {ERROR,DEBUG, INFO, WARNING,CRITICAL, iNVALID};

/*
 * Registra la severidad detectada por parametro y la imprime 
 * junto al mensaje correspondiente en un archivo txt.
 */
void logmessage(string msg, ETIQUETAS severidad);

/*
 * Se registran en un archivo de texto txt el aviso de error, 
 * el archivo y la línea correspondiente en donde fue detectado.   
 */
void logmessage(string msg, string file, int error_line);

/*
 *Se registra en un archivo txt el aviso del intento de acceso
 *de un usuario junto a su nombre y un mensaje.
 */
void logmessage(string access_msg, string username);

/*
 * Se convierte un string en su correspondiente valor
 * del enum. En caso, de no pertenecer al enum devuelve
 * un runtimeerror.
 */
ETIQUETAS make_enum_element(string severidad);

/*
 *Se convierte un valor de enum (int) a su correspondiente
 *equivalencia en tipo string.
 */
string enum_to_string(ETIQUETAS severidad);

