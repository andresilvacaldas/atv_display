#include <stdio.h>  
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/clocks.h"

//Arquivo display
#include "ssd1306.h"
#include "font.h"
#include "hardware/i2c.h"

// Arquivo .pio
#include "pio_matrix.pio.h"
#include "led_matrix.h"


// Define os pinos dos botões e LEDs
#define BUTTON_A 5
#define BUTTON_B 6
#define LED_AZUL 12    
#define LED_VERDE 11   
#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define ENDERECO 0x3C
#define NUM_PIXELS 25


uint sm;  // Variável para armazenar o número da máquina de estados  

float r = 0.1, g = 0.0, b = 0.001; // Inicialização das variáveis RGB

// Função que converte valores de cor em formato de ponto flutuante (entre 0.0 e 1.0)
uint32_t matrix_rgb_conversor(double b, double r, double g) {
    unsigned char R, G, B;
    R = r * 255;
    G = g * 255;
    B = b * 255;
    return (G << 24) | (R << 16) | (B << 8);
}


//Estado dos LEDs
bool ledVerdeLigado = false;
bool ledAzulLigado = false;
uint32_t last_time_A = 0, last_time_B = 0;
const uint32_t debounce_delay_us = 200000; // Tempo de debounce de 200ms

ssd1306_t ssd; // Inicializa a estrutura do display

// Função de interrupção para os botões (com debounce)
void gpio_irq_handler(uint gpio, uint32_t events) {
    uint32_t current_time = to_us_since_boot(get_absolute_time());

    if (gpio == BUTTON_A && current_time - last_time_A > debounce_delay_us) {
        last_time_A = current_time;
        ledVerdeLigado = !ledVerdeLigado;
        gpio_put(LED_VERDE, ledVerdeLigado);

        ssd1306_fill(&ssd, false);
        ssd1306_rect(&ssd, 3, 3, 122, 58, 1, 0);
        ssd1306_draw_string(&ssd, "LED VERDE", 32, 16);
        ssd1306_draw_string(&ssd, ledVerdeLigado ? "ON" : "OFF", 32, 32);
        ssd1306_send_data(&ssd);
        printf("Botão A pressionado! LED Verde: %s\n", ledVerdeLigado ? "Ligado" : "Desligado");
    }

    if (gpio == BUTTON_B && current_time - last_time_B > debounce_delay_us) {
        last_time_B = current_time;
        ledAzulLigado = !ledAzulLigado;
        gpio_put(LED_AZUL, ledAzulLigado);

        ssd1306_fill(&ssd, false);
        ssd1306_rect(&ssd, 3, 3, 122, 58, 1, 0);
        ssd1306_draw_string(&ssd, "LED AZUL", 32, 16);
        ssd1306_draw_string(&ssd, ledAzulLigado ? "ON" : "OFF", 32, 32);
        ssd1306_send_data(&ssd);
        printf("Botão B pressionado! LED Azul: %s\n", ledAzulLigado ? "Ligado" : "Desligado");
    }
}

//Função para o display inicializar apagado
void exibir_no_display(char c) {
    ssd1306_fill(&ssd, false);
    ssd1306_rect(&ssd, 3, 3, 122, 58, 1, 0); // Desenha um retângulo

    char texto[2] = {c, '\0'};
    ssd1306_draw_string(&ssd, texto, 53, 30);
    ssd1306_send_data(&ssd);
}

int main() {
    stdio_init_all();
    setup_led_matrix();

    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    ssd1306_init(&ssd, WIDTH, HEIGHT, false, ENDERECO, I2C_PORT);
    ssd1306_fill(&ssd, false);
    ssd1306_send_data(&ssd);

    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);
    gpio_init(LED_AZUL);
    gpio_set_dir(LED_AZUL, GPIO_OUT);

    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);
    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_pull_up(BUTTON_B);

    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler); //Interrupção dos botões
    gpio_set_irq_enabled_with_callback(BUTTON_B, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

    while (true) {

        if (stdio_usb_connected()) { // Certifica-se de que o USB está conectado
            sleep_ms(10);
            char c;
            if (scanf("%c", &c) == 1) { // Lê um caractere da entrada padrão
                printf("Recebido: '%c'\n", c);

        // Exibe qualquer caractere no display OLED
                 exibir_no_display(c);
        
        // Seleciona a animação correta para a matriz de LEDs
        switch (c) {
                case '0': desenho_pio1(numero0, pio, sm, r, g, b); break;
                case '1': desenho_pio1(numero1, pio, sm, r, g, b); break;
                case '2': desenho_pio1(numero2, pio, sm, r, g, b); break;
                case '3': desenho_pio1(numero3, pio, sm, r, g, b); break;
                case '4': desenho_pio1(numero4, pio, sm, r, g, b); break;
                case '5': desenho_pio1(numero5, pio, sm, r, g, b); break;
                case '6': desenho_pio1(numero6, pio, sm, r, g, b); break;
                case '7': desenho_pio1(numero7, pio, sm, r, g, b); break;
                case '8': desenho_pio1(numero8, pio, sm, r, g, b); break;
                case '9': desenho_pio1(numero9, pio, sm, r, g, b); break;

                }
            }
        }
    }
    return 0;
    }

