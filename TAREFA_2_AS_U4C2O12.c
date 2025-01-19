#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"

// Definições dos pinos
#define LED_RED 13
#define LED_GREEN 11
#define LED_BLUE 12
#define BUZZER_A 21

// Função para desligar todos os LEDs
void turn_off_leds() {
    gpio_put(LED_RED, 0);
    gpio_put(LED_GREEN, 0);
    gpio_put(LED_BLUE, 0);
}

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

    // Inicializar todos os LEDs e buzzers desligados
    turn_off_leds();
    gpio_put(BUZZER_A, 0);
}

// controlar os buzzers
void buzzer_control(int buzzer, int sleep){
    for (int i; i<5; i++){
        gpio_put(buzzer, 1);
        sleep_ms(sleep); // vai ativar o buzzer A ou B por 2 segundos
        gpio_put(buzzer, 0);
    }
}

void process_command(const char *command) {

    turn_off_leds();

    if (strcmp(command, "RED") == 0) {
        gpio_put(LED_RED, 1);
        printf("LED vermelho ligado.\n");
        buzzer_control(BUZZER_A, 500);

    } else if (strcmp(command, "GREEN") == 0) {
        gpio_put(LED_GREEN, 1);
        printf("LED verde ligado.\n");
        buzzer_control(BUZZER_A, 800);

    } else if (strcmp(command, "BLUE") == 0) {
        gpio_put(LED_BLUE, 1);
        printf("LED azul ligado.\n");
        buzzer_control(BUZZER_A, 1000);

    } else if (strcmp(command, "OFF") == 0) {
        turn_off_leds();
        printf("LEDs desligados.\n");
    } else {
        printf("Comando desconhecido: %s\n", command);
    }
}

int main() {
    stdio_init_all();
    setup_gpio();

    char command[64];
    int index = 0;

    while (1) {
        char c = getchar();

        if (c == '_') {
            command[index] = '\0'; // Finaliza a string
            printf("Comando recebido: %s\n", command);
            process_command(command);
            index = 0;
            command[0] = '\0'; // Limpa o início da string
        } else {
            if (index < 63) { // Previne overflow no buffer
                command[index++] = c;
            } else {
                printf("Comando muito longo, descartando.\n");
                index = 0;
                command[0] = '\0'; // Reseta a string em caso de erro
            }
        }
    }
    sleep_ms(10);

    return 0;
}
