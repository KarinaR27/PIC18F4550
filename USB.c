/*
 * File:   USB.c
 * Author: ana_k
 *
 * Created on 23 de noviembre de 2021, 20:28
 */


#include <xc.h>
#include "Configuracion.h"
#include "USART_libreria.h"

void __interrupt(high_priority) Serial(void);

void main(void) {
    LCD_Init();
    Portada();
    USART_Init(9600);
    
    while(1){
        
    }
    return;
}


void __interrupt(high_priority) Serial(void){
    if(PIR1bits.RCIF == 1 ){
        char letra = USART_Rx();
        
        __delay_us(500);
        
        //Escribe en Comptadora
        if(letra == 0x1B){
            USART_Tx(0x0C);
        }
        if (letra == 0x3D)
        {
            
    USART_Cadena("                                __                       | ");USART_Tx(0x0D); USART_Tx(0x0A);
    USART_Cadena("                              .'||     _.--.           | ");USART_Tx(0x0D); USART_Tx(0x0A);
    USART_Cadena("                             |_| ` |---/     ``.         | ");USART_Tx(0x0D); USART_Tx(0x0A);
    USART_Cadena("                             | ` .'   .--.___`|        | ");USART_Tx(0x0D); USART_Tx(0x0A);
    USART_Cadena("                              | /    /# __ _<  |/        | ");USART_Tx(0x0D); USART_Tx(0x0A);
    USART_Cadena("                               |    |# /  || |           | ");USART_Tx(0x0D); USART_Tx(0x0A);
    USART_Cadena("                               |__  |# |  @| @            ");USART_Tx(0x0D); USART_Tx(0x0A);
    USART_Cadena("                              , -. .|#  |/|/            ");USART_Tx(0x0D); USART_Tx(0x0A);
    USART_Cadena("                              |   ` \\  _<.`)_          ");USART_Tx(0x0D); USART_Tx(0x0A);
    USART_Cadena("              .'~~`.           `._,|\\ | `-` /          ");USART_Tx(0x0D); USART_Tx(0x0A);
    USART_Cadena("            ,' .--. `.            )    \\(  `'           ");USART_Tx(0x0D); USART_Tx(0x0A);
    USART_Cadena("           / ,'    `. |         /  ,,  \\--            ");USART_Tx(0x0D); USART_Tx(0x0A);
    USART_Cadena("          (/       | |        / \\/  ``\\/   `-.___   ");USART_Tx(0x0D); USART_Tx(0x0A);
    USART_Cadena("                   .' .        |  \\    ___<__))  ");USART_Tx(0x0D); USART_Tx(0x0A);
    USART_Cadena("                 .' .'        /|   \\--'  ___----.`-'   ");USART_Tx(0x0D); USART_Tx(0x0A);
    USART_Cadena("                / .'         / (    >----'  .-<_==='      ");USART_Tx(0x0D); USART_Tx(0x0A);
    USART_Cadena("               / /          |   \\          /              ");USART_Tx(0x0D); USART_Tx(0x0A);
    USART_Cadena("              | .           |__\\        /               ");USART_Tx(0x0D); USART_Tx(0x0A);
    USART_Cadena("              | |             |   \\      /                ");USART_Tx(0x0D); USART_Tx(0x0A);
    USART_Cadena("              | .             |    \\   _/`                ");USART_Tx(0x0D); USART_Tx(0x0A);
    USART_Cadena("                `.         .'|    `\\_(`|                 ");USART_Tx(0x0D); USART_Tx(0x0A);
    USART_Cadena("                `. `----~' .'\\    \\    )                ");USART_Tx(0x0D); USART_Tx(0x0A);
    USART_Cadena("                  `-.___.-'  |    )   /                 ");USART_Tx(0x0D); USART_Tx(0x0A);
    USART_Cadena("                               |   /|  /                  ");USART_Tx(0x0D); USART_Tx(0x0A);
    USART_Cadena("                               |  / (-<___            ");USART_Tx(0x0D); USART_Tx(0x0A);
    USART_Cadena("                              /--`-------_\           ");USART_Tx(0x0D); USART_Tx(0x0A);
    USART_Cadena("                              `---._  ==='                ");USART_Tx(0x0D); USART_Tx(0x0A);
    USART_Cadena("                                   `--'                   ");USART_Tx(0x0D); USART_Tx(0x0A);
        }
        else
            USART_Tx(letra);
        
        
        //Escribe en LCD
        if(letra == 0x1B || letra == 0x7F || letra == 0x0D){
            if(letra == 0x7F){
                RegistroCOM(SHIFT_CUR_LEFT);
                RegistroESCR(0x20);
                RegistroCOM(SHIFT_CUR_LEFT);
            }  
            if(letra == 0x0D){
                LCD_XY(1,0);
            }
            if(letra == 0x1B)
                RegistroCOM(0x01);
        }
        else
        RegistroESCR(letra);
    }
    INTCONbits.INT0IF = 0;
}
