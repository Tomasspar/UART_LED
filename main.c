#include <msp430.h>

#define LED_PIN BIT1 // Define the pin connected to the LED

void UART_Init() {
    P1SEL |= BIT1 + BIT2; // Select UART mode for P1.1 and P1.2
    P1SEL2 |= BIT1 + BIT2; // Select UART mode for P1.1 and P1.2

    UCA0CTL1 |= UCSWRST; // Put UART in reset state

    UCA0CTL1 |= UCSSEL_2; // Use SMCLK as clock source
    UCA0BR0 = 8; // Set the baud rate to 115200 (based on specific clock frequency)
    UCA0MCTL = UCBRS2 + UCBRS1 + UCBRS0; // Modulation UCBRSx = 6

    UCA0CTL1 &= ~UCSWRST; // Release UART from reset state
    IE2 |= UCA0RXIE; // Enable UART receive interrupt
}

void LED_Init() {
    P2DIR |= LED_PIN; // Set LED pin as output
    P2OUT &= ~LED_PIN; // Initially turn off the LED
}

void main(void) {
    WDTCTL = WDTPW + WDTHOLD; // Stop the watchdog timer

    UART_Init(); // Initialize UART
    LED_Init(); // Initialize LED

    __bis_SR_register(GIE); // Enable global interrupts

    while(1) {
        // Main loop, the LED will be controlled by the UART interrupt
    }
}

#pragma vector = USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void) {
    char receivedChar = UCA0RXBUF; // Read received character

    if (receivedChar == '1') {
        P2OUT |= LED_PIN; // Turn on the LED if '1' is received
    } else if (receivedChar == '0') {
        P2OUT &= ~LED_PIN; // Turn off the LED if '0' is received
    }
}
