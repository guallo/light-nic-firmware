// Modified from https://www.appelsiini.net/2011/simple-usart-with-avr-libc/

#include <avr/io.h>
#include <stdio.h>

#define F_CPU 16000000UL
#define BAUD 9600
#include <util/setbaud.h>

static int uart_getchar(FILE *stream);
static int uart_putchar(char c, FILE *stream);

static FILE uart_rx = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);
static FILE uart_tx = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);


static int
uart_getchar(FILE *stream) {
  loop_until_bit_is_set(UCSR0A, RXC0);  // Wait until data exists
  return UDR0;
}

static int
uart_putchar(char c, FILE *stream)
{
  loop_until_bit_is_set(UCSR0A, UDRE0);  // Wait until data register empty
  UDR0 = c;
  return 0;
}

static void
uart_init(void)
{
  /* Configure UART speed */

  UBRR0H = UBRRH_VALUE;
  UBRR0L = UBRRL_VALUE;

#if USE_2X
  UCSR0A |= _BV(U2X0);
#else
  UCSR0A &= ~_BV(U2X0);
#endif

  UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);  // 8-bit data
  UCSR0B = _BV(RXEN0) | _BV(TXEN0);  // Enable RX and TX
}

int main(void)
{
  char input;
  
  uart_init();

  stdin = &uart_rx;
  stdout = &uart_tx;

  printf("%s", "hello from arduino nano! :)\r\n");
  
  while (1) {
    printf("%s", "press a key...\r\n");
    input = getchar();
    printf("I got: %c\r\n", input);
  }

  return 0;
}
