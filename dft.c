/*
  Вот пример кода дискретного преобразования Фурье (DFT) на языке C, использующий целочисленную арифметику с 16-битными целыми числами:

*/

#include
#include

#define N 16

typedef struct {
int real;
int imag;
} complex;

void DFT(complex* x, complex* X) {
int k, n;
for (k = 0; k < N; k++) {
X[k].real = 0;
X[k].imag = 0;
for (n = 0; n < N; n++) {
int angle = (k * n * 2 * M_PI) / N;
int cos_val = cos(angle) * 32767; // масштабирование до 16-битного целого числа
int sin_val = sin(angle) * 32767; // масштабирование до 16-битного целого числа
X[k].real += (x[n].real * cos_val - x[n].imag * sin_val) >> 15; // деление на 32767
X[k].imag += (x[n].real * sin_val + x[n].imag * cos_val) >> 15; // деление на 32767
}
}
}

int main() {
complex x[N], X[N];

// Заполнение входной последовательности x
for (int i = 0; i < N; i++) {
x[i].real = i;
x[i].imag = 0;
}

DFT(x, X);

// Вывод результатов
for (int i = 0; i < N; i++) {
printf("X[%d] = %d + %di\n", i, X[i].real, X[i].imag);
}

return 0;
}

/*
Этот код реализует функцию дискретного преобразования Фурье (DFT) для 
  входной последовательности `x` и записывает результат в массив `X`. 
  Входная последовательность заполняется значениями от 0 до 15, а 
  результаты DFT выводятся на экран. */
