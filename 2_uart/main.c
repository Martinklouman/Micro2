#include "uart.h"
#include "gpio.h"

void button_init(){ 
	GPIO->PIN_CNF[13] = (3 << 2);
	GPIO->PIN_CNF[14] = (3 << 2);
}

int sleep = 0;
int main() 
{
    for(int i = 17; i <= 20; i++)
        {
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	    }

    button_init();
    uart_init();


    while(1){

            
        if((GPIO->IN & (1 << 14)) == 0)
        {
            uart_send('A');
        }
        
        if((GPIO->IN & (1 << 13) ) == 0)
        {
            uart_send('B');
        }
        
        if(uart_read() == 'A')
        {
            GPIO->OUTCLR = (1 << 17);
        }
        if(uart_read() == 'B')
        {
            GPIO->OUTCLR = (1 << 18);
        }

        sleep = 10000;
		while(--sleep); 
    
    }
    return 0;
}