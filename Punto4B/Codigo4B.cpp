#include <emmintrin.h>
#include <iostream>
#include <cstring>
#include <cstdint>
using namespace std;

// Para compilar ejecutar
// g++ -msse2 -O3 .\Codigo4B.cpp -o Codigo4B      
// .\Codigo4B.exe

__m128i crear_vector_char(char char_x){
    return _mm_set1_epi8(char_x);
}

void mostrar_vector(__m128i vect_x){

    alignas(16) uint8_t bytes[16];

    _mm_store_si128((__m128i*)bytes, vect_x);

    for(int index = 0; index<16; ++index){
        printf("%02X ", bytes[index]);
    }
    printf("\n");

}

int main(){
    char char_x = ';';
    __m128i vect_x = crear_vector_char(char_x);

    std::cout << "Vector SIMD con caracter char_x:  '" << char_x << "'"<<std::endl;
    mostrar_vector(vect_x);
    return 0;
}
