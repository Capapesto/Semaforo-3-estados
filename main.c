#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

// Pinos
#define VERMELHO 23
#define AMARELO  22
#define VERDE    19

//VARIÁVEL DE ESTADO 

int estado_atual = 0;
//0=Vermelho
//1=Verde
//2=Amarelo


void inicializar_pinos() {
    gpio_reset_pin(VERMELHO);
    gpio_set_direction(VERMELHO, GPIO_MODE_OUTPUT);
    
    gpio_reset_pin(AMARELO);
    gpio_set_direction(AMARELO, GPIO_MODE_OUTPUT);

    gpio_reset_pin(VERDE);
    gpio_set_direction(VERDE, GPIO_MODE_OUTPUT);
}

void app_main() {
    printf("Semáforo\n");
    inicializar_pinos();

    while (true) {
        
        switch(estado_atual) {
            case 0: // VERMELHO
                printf("Pare!\n");
                gpio_set_level(VERMELHO, 1);
                gpio_set_level(AMARELO, 0);
                gpio_set_level(VERDE, 0);
                vTaskDelay(3000 / portTICK_PERIOD_MS);
                estado_atual = 1; // Próximo passo: Verde
                break;

            case 1: // VERDE
                printf("Siga!\n");
                gpio_set_level(VERMELHO, 0);
                gpio_set_level(AMARELO, 0);
                gpio_set_level(VERDE, 1);
                vTaskDelay(3000 / portTICK_PERIOD_MS);
                estado_atual = 2; // Próximo passo: Amarelo
                break;

            case 2: // AMARELO
                printf("Atenção!\n");
                gpio_set_level(VERMELHO, 0);
                gpio_set_level(AMARELO, 1);
                gpio_set_level(VERDE, 0);
                vTaskDelay(1000 / portTICK_PERIOD_MS);
                estado_atual = 0; // Próximo passo: Vermelho
                break;
        }
    }
}
