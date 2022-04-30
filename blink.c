#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"

    
#define ADC_NUM 0
#define ADC_PIN (26 + ADC_NUM)    
#define sample_number 2000

const uint LED_PIN = PICO_DEFAULT_LED_PIN;
bool state = true;
static int flag = 0;
int measure_number = 0;
int i = 0, j =0;



u_int16_t current [sample_number];

bool repeating_timer_callback(struct repeating_timer *t)
{
    state = true;
    flag = 1;

    return true;
}
struct repeating_timer timer;

void print_data()
{
printf("Medida=%d\n", measure_number);
for(j=0; j<sample_number; j++)
    {
        printf("%d\n",current[j]);
        sleep_ms(2);

    }
    printf("7000\r");
}

int main() {

stdio_init_all();    

gpio_init(LED_PIN);
gpio_set_dir(LED_PIN, GPIO_OUT);

adc_init();
adc_gpio_init( ADC_PIN);
adc_select_input( ADC_NUM);

add_repeating_timer_us(500, repeating_timer_callback, NULL, &timer);

while (1) {
 //tight_loop_contents();
    while (i != sample_number)
    {
        if(flag == 1)
         {
            current[i] = adc_read();
            i++;
            flag=0;
            state = false;
        }  
    }
    print_data();
    i=0;
    measure_number++;
    sleep_ms(500);
}
return 0;
}