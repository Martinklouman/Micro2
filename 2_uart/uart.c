#include "uart.h"
#include "gpio.h"



void uart_init()
{
    GPIO->PIN_CNF[6] = (0 << 0);
    GPIO->PIN_CNF[8] = (1 << 0); 

    UART->PSELTXD = 6; 
    UART->PSELRXD = 8; 
    UART->PSELRTS= 0xFFFFFFFF;
    UART->PSELCTS= 0xFFFFFFFF;

    UART->BAUDRATE = 0x00275000;

    UART->ENABLE = 4;
    UART->TASK_STARTTX = 1;
}

void uart_send(char letter)
{
    UART->TASK_STARTTX = 1;
    UART->TXD = letter;
    while(!(UART->EVENTS_RXDRDY))
    {

    }
    UART->EVENTS_TXDRDY = 0;
    UART->TASK_STOPTX = 1;
}

char uart_read()
{
    char letter;
    UART->EVENTS_RXDRDY = 0;
    UART->TASK_STARTRX = 1;
    if (UART->EVENTS_RXDRDY)
    {
        letter = UART->RXD;
    }
    else 
    {
        letter = '\0';
    }
    return letter;
}

//UART REGISTRE 538
//GPIO PIN_CNF 6 140
//GPIO PIN_CNF 8 141

