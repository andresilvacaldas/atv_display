#ifndef LED_MATRIX_H
#define LED_MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"

// Configurações da matriz
#define COLUMNS 5
#define ROWS 5
#define NUM_LEDS 25
#define OUT_PIN 7
#define NUM_PIXELS 25

extern PIO pio;  // Declare como extern para ser definida em outro arquivo

void bin_printf(int num);
void animacao(uint8_t repeticoes, uint8_t num_frames, uint32_t desenho[num_frames][NUM_PIXELS], uint sm);
void setup_led_matrix();
void draw(double **desenhoRGB);
void anima(uint8_t num_frames, uint32_t desenho[num_frames][NUM_PIXELS], uint sm);

void desenho_pio1(double *desenho, PIO pio, uint sm, double r, double g, double b);

extern uint32_t xadrez[10][NUM_PIXELS];

extern double numero0[25];
extern double numero1[25];
extern double numero2[25];
extern double numero3[25];
extern double numero4[25];
extern double numero5[25];
extern double numero6[25];
extern double numero7[25];
extern double numero8[25];
extern double numero9[25];




#endif // LED_MATRIX_H
