/*Си, который использует целочисленную арифметику с 16-битными целыми числами:```c*/

#include <stdio.h>

#include <stdlib.h>

#include <math.h>

#define N 16 // длина входной последовательности

short x[N] = { // входная последовательность  32767, 32767, 32767, 32767,  0,     0,     0,     0,    -32767,-32767,-32767,-32767,  0,     0,     0,     0};

short real[N];  // действительная часть спектра

short imag[N];  // мнимая часть спектра

// Реализация прямого 

DFTvoid dft(short *x, short *real, short *imag) {
  for (int k = 0; k < N; k++) {  
  real[k] = imag[k] = 0;  
  for (int n = 0; n < N; n++) {   
   real[k] += x[n] * cos(2*M_PI*k*n/N); 
     imag[k] -= x[n] * sin(2*M_PI*k*n/N);   
 } 
 }
}

// Реализация обратного 

DFTvoid idft(short *real, short *imag, short *x) { 
 for (int n = 0; n < N; n++) {  
  x[n] = 0;  
  for (int k = 0; k < N; k++) {  
    x[n] += real[k] * cos(2*M_PI*k*n/N) - imag[k] * sin(2*M_PI*k*n/N);  
  }  
  x[n] /= N; // Нормировка  
}
}

int main() { 
 dft(x, real, imag); 
 idft(real, imag, x); 
 for (int i = 0; i < N; i++) {    printf("%d\n", x[i]);  } 
 return 0;
}

/*```Здесь `short` обозначает 16-битные целые числа, используемые для представления входных данных, действительной и мнимой частей спектра и 
*/