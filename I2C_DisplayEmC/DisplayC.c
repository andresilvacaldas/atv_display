#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "inc/ssd1306.h"
#include "inc/font.h"


// Define os pinos dos botões e LEDs
#define BUTTON_A 5
#define BUTTON_B 6
#define LED_AZUL 12    
#define LED_VERDE 11   
#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define endereco 0x3C

// Variáveis para armazenar o estado dos LEDs
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
        ssd1306_draw_string(&ssd, "LED VERDE", 32, 0);
        ssd1306_draw_string(&ssd, ledVerdeLigado ? "LIGADO" : "DESLIGADO", 32, 16);
        ssd1306_send_data(&ssd);
        printf("Botão A pressionado! LED Verde: %s\n", ledVerdeLigado ? "Ligado" : "Desligado");
    }

    if (gpio == BUTTON_B && current_time - last_time_B > debounce_delay_us) {
        last_time_B = current_time;
        ledAzulLigado = !ledAzulLigado;
        gpio_put(LED_AZUL, ledAzulLigado);

        ssd1306_fill(&ssd, false);
        ssd1306_draw_string(&ssd, "LED AZUL", 32, 0);
        ssd1306_draw_string(&ssd, ledAzulLigado ? "LIGADO" : "DESLIGADO", 32, 16);
        ssd1306_send_data(&ssd);
        printf("Botão B pressionado! LED Azul: %s\n", ledAzulLigado ? "Ligado" : "Desligado");
    }
}

void exibir_no_display(char c) {
    ssd1306_fill(&ssd, 0);
    ssd1306_rect(&ssd, 0, 0, 0, 0, 0, 0);

    char texto[2] = {c, '\0'};
    ssd1306_draw_string(&ssd, texto, 53, 30);
    ssd1306_send_data(&ssd);
    sleep_ms(2000);
}

int main() {
    stdio_init_all();

    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    ssd1306_init(&ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT);
    ssd1306_config(&ssd);
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

    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(BUTTON_B, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

    while (true) {
        char c;
        if (scanf(" %c", &c) == 1) {
            printf("Recebido: '%c'\n", c);
            exibir_no_display(c);
        }
        sleep_ms(10);
    }

    return 0;
}