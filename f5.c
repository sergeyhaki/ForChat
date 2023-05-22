/*
Конечный вариант кода зависит от того, какую структуру вы выберете для вашего фильтра. Ниже приведен один из возможных вариантов реализации all-pass фильтра на языке C:*/

typedef struct {
    float b0, b1, b2;
    float a0, a1, a2;
    float x1, x2;
    float y1, y2;
} allpass_filter_t;

void allpass_filter_init(allpass_filter_t* f, float g, float d)
{
    float a0 = 1.0f + g;
    float a1 = -2.0f * d / a0;
    float a2 = (1.0f - g) / a0;
    f->b0 = 1.0f - g;
    f->b1 = -2.0f * d;
    f->b2 = g - 1.0f;
    f->a0 = a0;
    f->a1 = a1;
    f->a2 = a2;
    f->x1 = 0.0f;
    f->x2 = 0.0f;
    f->y1 = 0.0f;
    f->y2 = 0.0f;
}

float allpass_filter_process(allpass_filter_t* f, float x)
{
    float y = f->b0 * x + f->b1 * f->x1 + f->b2 * f->x2
            - f->a1 * f->y1 - f->a2 * f->y2;
    f->x2 = f->x1;
    f->x1 = x;
    f->y2 = f->y1;
    f->y1 = y;
    return y;
}

/*Здесь all-pass фильтр реализован в виде функций allpass_filter_init() и allpass_filter_process(). Параметры g и d определяют характеристики фильтра, а именно, его коэффициенты передачи и задерж*/