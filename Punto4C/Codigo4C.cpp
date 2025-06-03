#include <emmintrin.h>
#include <iostream>
#include <cstring>
#include <cstdint>
using namespace std;

__m128i comparar_vectores(__m128i vect_x, __m128i vect_y){
    //Instrucción que permite comprar dos vectores SIMD de 128 bits
    return _mm_cmpeq_epi8(vect_x,vect_y);
}

void imprimir_mascara(__m128i mask){
    alignas(16) uint8_t bytes[16];
    _mm_store_si128((__m128i*)bytes, mask);


    cout << "out_str" << endl;
    for(int index = 0; index<16; ++index){
        printf("%02X ", bytes[index]);
    }
    printf("\n");

    cout << "Mask" << endl;
    for(int index = 0; index<16; ++index){
        printf("%s", bytes[index] == 0xFF? "1  ":"0  ");
    }
    printf("\n");

}


int main(){
    __m128i vect_x = _mm_set1_epi8(';');
    __m128i vect_y = _mm_setr_epi8('A', 's', 'l','k','a','d','j',';','s','k','j','d',';','j',';','0');

    __m128i mascara = comparar_vectores(vect_x, vect_y);

    imprimir_mascara(mascara);

    return 0;
}
