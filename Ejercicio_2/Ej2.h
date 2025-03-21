#include <iostream>
#include <fstream>

using namespace std;

enum class ETIQUETAS : uint8_t {ERROR,DEBUG, INFO, WARNING,CRITICAL, iNVALID};

void logmessage(string msg, ETIQUETAS severidad);

void logmessage(string msg, string file, int error_line);

void logmessage(string access_msg, string username);

ETIQUETAS make_enum_element(string severidad);

string enum_to_string(ETIQUETAS severidad);

