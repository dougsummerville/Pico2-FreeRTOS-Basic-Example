#include <stdio.h>
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"

#define BLINK_TASK_STACK_SIZE configMINIMAL_STACK_SIZE
#define MESSAGE_TASK_STACK_SIZE configMINIMAL_STACK_SIZE

StackType_t uxBlinkTaskStack[BLINK_TASK_STACK_SIZE]; 
StaticTask_t xBlinkTaskTCB;                         

StackType_t uxMessageTaskStack[MESSAGE_TASK_STACK_SIZE]; 
StaticTask_t xMessageTaskTCB;                             


void vBlinkTask(void *pvParameters) {
    const uint led_pin = PICO_DEFAULT_LED_PIN;
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);
    while (true) {
        gpio_put(led_pin, 1);
        vTaskDelay(1000); 
        gpio_put(led_pin, 0);
        vTaskDelay(1000);
    }
}


void vMessageTask(void *pvParameters) {
    while (true) {
        printf("FreeRTOS is running!\n");
        vTaskDelay(pdMS_TO_TICKS(5000)); 
    }
}


int main() {
    stdio_init_all(); 

    
    xTaskCreateStatic(
        vBlinkTask,            
        "Blink",               
        BLINK_TASK_STACK_SIZE,     
        NULL,                      
        1,                         
        uxBlinkTaskStack,          
        &xBlinkTaskTCB             
    );

    
    xTaskCreateStatic(
        vMessageTask,              
        "MessageTask",             
        MESSAGE_TASK_STACK_SIZE,   
        NULL,                      
        1,                         
        uxMessageTaskStack,        
        &xMessageTaskTCB           
    );

    
    vTaskStartScheduler();

    
    while (true) {
        
    }
}

