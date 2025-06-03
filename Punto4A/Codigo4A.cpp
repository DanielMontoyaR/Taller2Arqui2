#include <iostream>
#include <cstring>
using namespace std;
size_t contar_ocurrencias_serial(const char* str, char char_x, size_t M) {
    size_t contador = 0;
    for (size_t i = 0; i < M; ++i) {
        if (str[i] == char_x) {
            ++contador;
        }
    }
    return contador;
}

int main() {

    const char* str = "Aslkadj;skjd;j;0";
    char char_x = ';';
    size_t M = std::strlen(str);
    
    size_t ocurrencias = contar_ocurrencias_serial(str, char_x, M);
    std::cout << "Numero de ocurrencias de '" << char_x << "': " << ocurrencias << std::endl;

    return 0;
}