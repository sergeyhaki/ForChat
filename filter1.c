/*
Обратное быстрое преобразование Фурье (IFFT) - это алгоритм, обратный FFT, который преобразует частотный домен обратно во временной домен. Пример реализации на языке С с использованием целых чисел:```*/

#include <stdio.h>
#include <math.h>
#define N 8

void ifft(int n, int x_real[], int x_imag[], int X_real[], int X_imag[])
 {    
  if (n == 1)
 {  
      X_real[0] = x_real[0];        X_imag[0] = x_imag[0];       
 return;    
} 
      
 int x_even_real[n/2], x_even_imag[n/2], x_odd_real[n/2], x_odd_imag[n/2];   
 int X_even_real[n/2], X_even_imag[n/2], X_odd_real[n/2], X_odd_imag[n/2];        

for (int i = 0; i < n/2; i++)
 {      
  x_even_real[i] = x_real[2*i];        x_even_imag[i] = x_imag[2*i];        x_odd_real[i] = x_real[2*i+1];        x_odd_imag[i] = x_imag[2*i+1];  
  }     

   ifft(n/2, x_even_real, x_even_imag, X_even_real, X_even_imag);  

  ifft(n/2, x_odd_real, x_odd_imag, X_odd_real, X_odd_imag);   

     for (int k = 0; k < n; k++) 
{       
 int kth = 2 * M_PI * k / n * pow(2, ceil(log2(N)));    
    int W_real = cos(kth);   
     int W_imag = sin(kth);        X_real[k] = X_even_real[k % (n/2)] + W_real * X_odd_real[k % (n/2)] - W_imag * X_odd_imag[k % (n/2)];    
    X_imag[k] = X_even_imag[k % (n/2)] + W_real * X_odd_imag[k % (n/2)] + W_imag * X
