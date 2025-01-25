#include "pico/stdlib.h"

// Definição dos pinos
#define LED_PIN 11
#define BUTTON_PIN 5

// Definição dos estados
typedef enum {
    STATE_OFF,    // Desligado
    STATE_ON,     // Ligado
    STATE_BLINK    // Piscar
} state_t;

// Variável para armazenar o estado atual
state_t current_state = STATE_OFF;

// Função para inicializar os pinos
void init_gpio() {
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT); // Configura o LED como saída

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN); // Configura o botão como entrada
    gpio_pull_up(BUTTON_PIN); // Ativa o resistor pull-up
}

// Função para alternar o estado
void toggle_state() {
    switch (current_state) {
        case STATE_OFF:
            current_state = STATE_ON;
            break;
        /*case STATE_ON:
            current_state = STATE_BLINK;
            break;*/
        case STATE_ON: //case STATE_BLINK:
            current_state = STATE_OFF;
            break;
    }
}

// Função para atualizar o LED com base no estado atual
void update_led() {
    switch (current_state) {
        case STATE_OFF:
            gpio_put(LED_PIN, 0); // Desliga o LED
            break;
        case STATE_ON:
            gpio_put(LED_PIN, 1); // Liga o LED
            break;
        case STATE_BLINK:
            gpio_put(LED_PIN, 1); // Liga o LED
            sleep_ms(500);        // Espera 500 ms
            gpio_put(LED_PIN, 0); // Desliga o LED
            sleep_ms(500);        // Espera 500 ms
            break;
    }
}

int main() {
    stdio_init_all(); // Inicializa a comunicação padrão
    init_gpio();      // Inicializa os pinos GPIO

    while (true) {
        // Verifica se o botão foi pressionado
        if (gpio_get(BUTTON_PIN) == 0) { // Botão pressionado (nível baixo)
            toggle_state(); // Alterna o estado
            sleep_ms(500);  // Debounce: espera 200 ms para evitar múltiplas leituras
        }

        // Atualiza o LED com base no estado atual
        update_led();
    }

    return 0; // O código nunca chega aqui, pois o loop é infinito
}