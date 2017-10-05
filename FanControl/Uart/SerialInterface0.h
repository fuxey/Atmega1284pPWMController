

#ifndef SERIALINTERFACE_H_
#define SERIALINTERFACE_H_

#include <stdint.h>
#include <avr/io.h>
#include <stdio.h>
#ifndef F_CPU
#error NO F_CPU defined!
#endif


#define BAUD 38400UL      // Baudrate

// Berechnungen
#define UBRR_VAL ((F_CPU+BAUD*8)/(BAUD*16)-1)   // clever runden
#define BAUD_REAL (F_CPU/(16*(UBRR_VAL+1)))     // Reale Baudrate
#define BAUD_ERROR ((BAUD_REAL*1000)/BAUD) // Fehler in Promille, 1000 = kein Fehler.

#if ((BAUD_ERROR<990) || (BAUD_ERROR>1010))
#error Systematischer Fehler der Baudrate grösser 1% und damit zu hoch!
#endif

#define INBUF_SIZE 0x10


uint8_t * getUartRcvPtr(void);
void printSyncronousOnUart(uint8_t *str,uint16_t len);
void initUart(void);
int putcUart(uint8_t c);
int putCharUart( char c, FILE *stream );
void putStringOnUart (char *s);


uint8_t isUartDataReceived(void);
void resetRcvFlagAndClearRcvBuffer(void);

#endif