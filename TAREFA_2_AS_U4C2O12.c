#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "pico/stdlib.h"
#include "pico/bootrom.h" // Para reset_usb_boot

// Definições dos pinos
#define LED_RED 13
#define LED_GREEN 11
#define LED_BLUE 12
#define BUZZER_A 21
#define BUTTON_A 5 // Botão A

// Função para configurar os GPIOs
void setup_gpio() {
    // Configurar buzzers como saída
    gpio_init(BUZZER_A);
    gpio_set_dir(BUZZER_A, GPIO_OUT);

    // Configurar LEDs como saída
    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);

    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);

    gpio_init(LED_BLUE);
    gpio_set_dir(LED_BLUE, GPIO_OUT);

    // Configurar botão como entrada com pull-up
    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);

    // Inicializar todos os LEDs e buzzers desligados
    turn_off_leds();
    gpio_put(BUZZER_A, 0);
}

// Função para desligar todos os LEDs
void turn_off_leds() {
    gpio_put(LED_RED, 0);
    gpio_put(LED_GREEN, 0);
    gpio_put(LED_BLUE, 0);
}

// Função para ligar todos os LEDs e transformar no led branco
void turn_on_leds() {
    gpio_put(LED_RED, 1);
    gpio_put(LED_GREEN, 1);
    gpio_put(LED_BLUE, 1);
}

// Função para controlar os buzzers
void buzzer_control(int BUZZER, int frequency, int duration_ms) {
    int period = 1000000 / frequency; // Calcula o período da frequência em microssegundos
    int cycles = (duration_ms * 1000) / period; // Quantos ciclos de som em um tempo de duração

    for (int i = 0; i < cycles; i++) {
        gpio_put(BUZZER, 1); // Liga o buzzer (HIGH)
        sleep_us(period / 2); // Espera metade do período
        gpio_put(BUZZER, 0); // Desliga o buzzer (LOW)
        sleep_us(period / 2); // Espera a outra metade do período
        sleep_ms(5); // Adiciona um pequeno atraso de 5ms entre os ciclos
    }
}

// Converter string para maiúsculas
void string_to_upper(char *str) {
    while (*str) {
        *str = toupper((unsigned char)*str);
        str++;
    }
}

// Função para processar o comando e ligar o respectivo led
void process_command(const char *command) {
    turn_off_leds();

    if (strcmp(command, "RED") == 0) {
        gpio_put(LED_RED, 1);
        printf("LED vermelho ligado.\n");
        buzzer_control(BUZZER_A, 800, 1000);

    } else if (strcmp(command, "GREEN") == 0) {
        gpio_put(LED_GREEN, 1);
        printf("LED verde ligado.\n");
        buzzer_control(BUZZER_A, 800, 750);

    } else if (strcmp(command, "BLUE") == 0) {
        gpio_put(LED_BLUE, 1);
        printf("LED azul ligado.\n");
        buzzer_control(BUZZER_A, 800, 500);

    } else if (strcmp(command, "BRANCO") == 0) {
        turn_on_leds();
        printf("LED branco ligado.\n");
        buzzer_control(BUZZER_A, 800, 250);

    } else if (strcmp(command, "OFF") == 0) {
        turn_off_leds();
        printf("LEDs desligados.\n");
        buzzer_control(BUZZER_A, 500, 250);
    } else {
        printf("Comando desconhecido: %s\n", command);
        sleep_ms(1000);
    }
}

// Manipulador de interrupção para o botão A
void gpio_irq_handler(uint gpio, uint32_t events) {
    if (gpio == BUTTON_A) { // Verifica se a interrupção veio do botão A
        printf("\nBotão A pressionado! Habilitando o modo gravação...\n");
        reset_usb_boot(0, 0); // Entra no modo de gravação USB
    }
}

int main() {
    stdio_init_all();
    setup_gpio();

    // Configura a interrupção no GPIO5 para detectar borda de descida (botão pressionado)
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

    char command[64];

    while (1) {
        printf("----------------- LISTA DE COMANDOS ---------------------\n");
        printf("RED \nGREEN \nBLUE \nBRANCO \nOFF\n");
        printf("-------------------------------------------------------------\n");
        printf("Digite um dos comandos acima: ");
        scanf("%s", command);

        string_to_upper(command);

        printf("\nComando: %s\n", command);

        process_command(command);

        sleep_ms(10);
    }

    return 0;
}
