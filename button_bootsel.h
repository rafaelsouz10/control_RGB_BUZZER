#include "pico/bootrom.h" // Para reset_usb_boot

#define BUTTON_A 5 // Botão A

void setup_gpio_button_A(){
    // Configurar botão como entrada com pull-up
    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);
}

// Manipulador de interrupção para o botão A
void gpio_irq_handler(uint gpio, uint32_t events) {
    if (gpio == BUTTON_A) { // Verifica se a interrupção veio do botão A
        printf("\nBotão A pressionado! Habilitando o modo gravação...\n");
        reset_usb_boot(0, 0); // Entra no modo de gravação USB
    }
}


//adicione esse aquivo button_bootsel.h no seu projeto

//inclua a lib button_bootsel.h no cabeçalho

//chame a função setup_gpio_button_A() no main() para configurar o botão como entrada pull-up

//logo em seguinda, chame a função abaixo (linha 25) para configurar a interrupção no 
//GPIO5 para detectar borda de descida (botão pressionado)

// -->    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);


// exemplo:

//#include "button_bootsel.h"

// int main() {
//     //...

//     setup_gpio_button_A();
//     gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

//     while (1) {
//        //...
//     }
//     return 0;
// }