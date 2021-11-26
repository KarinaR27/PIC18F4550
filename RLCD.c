/*
 * File:   RLCD.c
 * Author: ana_k
 *
 * Created on 9 de noviembre de 2021, 10:41
 */
// CONFIG1L
#pragma config PLLDIV = 1       // PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
#pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
#pragma config USBDIV = 1       // USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes directly from the primary oscillator block with no postscale)

// CONFIG1H
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator (HS))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = OFF        // Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
#pragma config BORV = 3         // Brown-out Reset Voltage bits (Minimum setting 2.05V)
#pragma config VREGEN = OFF     // USB Voltage Regulator Enable bit (USB voltage regulator disabled)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = ON      // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config ICPRT = OFF      // Dedicated In-Circuit Debug/Programming Port (ICPORT) Enable bit (ICPORT disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) is not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) is not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) is not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) is not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) is not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) is not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) is not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) is not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) is not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM is not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) is not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) is not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#define _XTAL_FREQ 20000000L
#include <xc.h>
//#include "LCD_Libreria.h"


//4 bits -> R0 R1 R2 R3

//Variables de configuracion

// nc RW RS E D7 D6 D5 D4<-MENOS SIGNIFICATIVO
#define RW_PIN_on  0b01000000 //habilita con OR
#define RW_PIN_off 0b10111111 //habilita con AND

#define RS_PIN_on  0b00100000
#define RS_PIN_off 0b11011111

#define E_PIN_on  0b00010000
#define E_PIN_off 0b11101111

#define SERIAL_DATA LATBbits.LATB0
#define LATCH_CLOCK LATBbits.LATB1
#define SHIFT_CLOCK LATBbits.LATB2

#define BORRAR_LCD 0x01

//Función:
void LCD_Init(void);
void LCD_Comando(unsigned char cmd);
void LCD_XY(int x,int y);
void LCD_Cadena(const char *);
void LCD_Data(const char);
void datos(char);
void positiveSR_tg(void);
void positiveLR_tg(void);
void portada(void);
void LCD_WriteChr_CGRAM(const char *buffer, unsigned char Addres);


const char ipn_1[]={
    0x07,
    0x0F,
    0x0F,
    0x0F,
    0x0F,
    0x0F,
    0x0F,
    0x1F
};
const char ipn_2[]={
    0x00,
    0x17,
    0x15,
    0x17,
    0x14,
    0x1F,
    0x00,
    0x11
};
const char ipn_3[]={
    0x00,
    0x12,
    0x1A,
    0x16,
    0x12,
    0x1E,
    0x0C,
    0x06
};
const char ipn_4[]={
    0x1F,
    0x0F,
    0x18,
    0x08,
    0x1D,
    0x06,
    0x03,
    0x01
};
const char ipn_5[]={
    0x0E,
    0x1F,
    0x0E,
    0x11,
    0x00,
    0x00,
    0x1F,
    0x15
};
const char ipn_6[]={
    0x06,
    0x1C,
    0x06,
    0x04,
    0x16,
    0x0C,
    0x18,
    0x10
};

const char esime_1[]={
    0x00,
    0x01,
    0x00,
    0x03,
    0x04,
    0x07,
    0x08,
    0x0F
};
const char esime_2[]={
    0x05,
    0x15,
    0x00,
    0x1D,
    0x11,
    0x1D,
    0x05,
    0x1D
};
const char esime_3[]={
    0x14,
    0x15,
    0x00,
    0x11,
    0x1B,
    0x15,
    0x11,
    0x11
};
const char esime_4[]={
    0x00,
    0x10,
    0x00,
    0x18,
    0x10,
    0x1C,
    0x10,
    0x1E
};
const char esime_5[]={
    0x0F,
    0x03,
    0x0F,
    0x01,
    0x07,
    0x01,
    0x02,
    0x00
};
const char esime_6[]={
    0x10,
    0x08,
    0x06,
    0x11,
    0x19,
    0x1F,
    0x0F,
    0x05
};
const char esime_7[]={
    0x01,
    0x02,
    0x0C,
    0x11,
    0x13,
    0x1F,
    0x1E,
    0x14
};
const char esime_8[]={
    0x1E,
    0x18,
    0x1E,
    0x10,
    0x1C,
    0x10,
    0x08,
    0x00
};

char k;


void main(void) {
    TRISBbits.RB0=0;
    TRISBbits.RB1=0;
    TRISBbits.RB2=0;
    
    SERIAL_DATA=0;
    LATCH_CLOCK=0;
   
    //positiveSR_tg();
    //positiveSR_tg();
    LCD_Init();
    
    while(1)
    {
        portada();
        __delay_ms(1); 
    }
    return;
}

void LCD_Init(void){
   
    datos(0x00);
    
    __delay_ms(15); //Segun datasheet

    LCD_Comando(0x30);
    __delay_ms(5);
    LCD_Comando(0x30);
    __delay_us(100);
    LCD_Comando(0x32);
    __delay_us(100);
    
    //4 bits configuracion:
    __delay_us(100);
    LCD_Comando(0x28);      //Lineas y caracteres
    __delay_us(100);
    LCD_Comando(0x08);      //Display cursor y parpadero: apagado
    __delay_us(100);
    LCD_Comando(0x0C);      //Display cursor y parpadero: enciende
    __delay_us(100);
    LCD_Comando(0x01);      //Limpiar LCD
    __delay_us(100);
    LCD_Comando(0x04);
    __delay_us(100);
    
    __delay_us(100);
    LCD_Comando(0x06);      //Display
    LCD_Comando(0x0C);      //Incremento y no se mueve
    return;
    
}

void LCD_Comando(unsigned char cmd){
    
    unsigned char aux;
    
    datos(0x00);//limpia el registro
    
    //mas significativo
    aux=cmd>>4;//corrimiento de 4 bits para el nible bajo
    aux=RW_PIN_off & aux;//modo escritura        
    aux=RS_PIN_off & aux;//modo comando
    
    datos(aux);
    __delay_us(5);  //18TCY -> 20MHZ: 18*TCY = 18*(4/20MHZ) = 3.6uS
    
    aux=E_PIN_on | aux;//Habilita LCD
    datos(aux);
    __delay_us(5);
    aux=E_PIN_off & aux;//Deshabilita LCD
    datos(aux);
    
    //menos significativo
    aux=cmd&0x0f;//borrado del nibble alto
    aux=RW_PIN_off & aux;//modo escritura        
    aux=RS_PIN_off & aux;//modo comando    
    datos(aux);
    __delay_us(5);  //18TCY -> 20MHZ: 18*TCY = 18*(4/20MHZ) = 3.6uS
    
    aux=E_PIN_on | aux;//Habilita LCD
    datos(aux);
    __delay_us(5);
    aux=E_PIN_off & aux;//Deshabilita LCD
    datos(aux);
      
    return;
}

void LCD_XY(int x,int y){
    if(x>0){
        LCD_Comando(0xC0+y);
    }
    else{
        LCD_Comando(0x80+y);
    }
}

void LCD_Cadena(const char *dato){
    while(*dato){
        __delay_ms(10);
        LCD_Data(*dato);
        dato++;
        __delay_ms(10);
    }
}

void LCD_Data(const char data){
    char aux;
    __delay_us(100);
    
    datos(0x00);
    
    aux=data>>4;//corrimiento de 4 bits para el nible bajo
            
    aux=RW_PIN_off & aux;//modo escritura  
    aux=RS_PIN_on | aux;//modo caracter
        
    datos(aux);
    
    __delay_us(5);  //18TCY -> 20MHZ: 18*TCY = 18*(4/20MHZ) = 3.6uS
    
    aux=E_PIN_on | aux;//Habilita LCD
    
    datos(aux);
    __delay_us(5);
    aux=E_PIN_off & aux;//Deshabilita LCD
    datos(aux);
    
    aux=data&0x0f;//borrado del nibble alto
    
    aux=RW_PIN_off & aux;//modo escritura        
    aux=RS_PIN_on | aux;//modo comando    
    datos(aux);
    __delay_us(5);  //18TCY -> 20MHZ: 18*TCY = 18*(4/20MHZ) = 3.6uS
    
    aux=E_PIN_on | aux;//Habilita LCD
    datos(aux);
    __delay_us(5);
    aux=E_PIN_off & aux;//Deshabilita LCD
    datos(aux);
      
    
    return;
    
}

void portada(void)
{
    LCD_Comando(BORRAR_LCD);
    
    __delay_ms(200);
    LCD_WriteChr_CGRAM(ipn_1,64);
    LCD_WriteChr_CGRAM(ipn_2,72);
    LCD_WriteChr_CGRAM(ipn_3,80);
    LCD_WriteChr_CGRAM(ipn_4,88);
    LCD_WriteChr_CGRAM(ipn_5,96);
    LCD_WriteChr_CGRAM(ipn_6,104);
    
    LCD_Comando(BORRAR_LCD);
    
    __delay_ms(200);
    LCD_XY(0,0);
    LCD_Data(0);
    LCD_Data(1);
    LCD_Data(2);
    
    __delay_ms(200);
    LCD_XY(1,0);
    LCD_Data(3);
    LCD_Data(4);
    LCD_Data(5);
    
    __delay_ms(5000);
    LCD_Comando(BORRAR_LCD);
    
    LCD_XY(0,0);
    LCD_Cadena("INSTITUTO POLITECNICO NACIONAL");
    __delay_ms(2000);
    
    for(k=0;k<16;k++)
    {
        LCD_Comando(0x18);
        __delay_ms(1500);
    }
    
    LCD_XY(0,0);
    for(k=0;k<12;k++)
    {
        LCD_Data(' ');
    }
    
    for(k=0;k<16;k++)
    {
        LCD_Comando(0x18);
        __delay_ms(1500);
    }
    __delay_ms(1000);
    //-----------------------------------ESIME--------------------------------/
    LCD_Comando(BORRAR_LCD);
    __delay_ms(200);
    LCD_WriteChr_CGRAM(esime_1,64);
    LCD_WriteChr_CGRAM(esime_2,72);
    LCD_WriteChr_CGRAM(esime_3,80);
    LCD_WriteChr_CGRAM(esime_4,88);
    LCD_WriteChr_CGRAM(esime_5,96);
    LCD_WriteChr_CGRAM(esime_6,104);
    LCD_WriteChr_CGRAM(esime_7,112);
    LCD_WriteChr_CGRAM(esime_8,120);
    
    LCD_Comando(BORRAR_LCD);
    __delay_ms(200);
    LCD_XY(0,0);
    LCD_Data(0);
    LCD_Data(1);
    LCD_Data(2);
    LCD_Data(3);
    __delay_ms(200);
    LCD_XY(1,0);
    LCD_Data(4);
    LCD_Data(5);
    LCD_Data(6);
    LCD_Data(7);
    __delay_ms(5000);
    
    LCD_Comando(BORRAR_LCD);
    
    LCD_XY(0,0);
    LCD_Cadena("Escuela Superior");
    LCD_XY(1,0);
    LCD_Cadena("de Ingenieria Mecanica y Electrica");
    __delay_ms(4000);
    for(k=0; k<16;k++)
    {
        LCD_Comando(0x18);
        __delay_ms(1000);
    }
    
    LCD_XY(0,0);
    for(k=0; k<12;k++)
    {
        LCD_Data(' ');
    }
    LCD_XY(1,0);
    for(k=0; k<12;k++)
    {
        LCD_Data(' ');
    }
    for(k=0; k<19;k++)
    {
        LCD_Comando(0x18);
        __delay_ms(1000);
    }
    
    __delay_ms(200);
    
    /*
    LCD_XY(1,0);
    for(k=0; k<10;k++)
    {
        LCD_Data(' ');
    }
    __delay_ms(200);
    
    
    
    for(k=0; k<34;k++)
    {
        LCD_Comando(0x18);
        __delay_ms(800);
    }
    __delay_ms(200);
    LCD_XY(0,21);
    */
    /*
    for(k=0; k<18;k++)
    {
        LCD_Data(' ');
    }
    for(k=0; k<22;k++)
    {
        LCD_Comando(0x18);
        __delay_ms(500);
    }
    */
    //---------------------------MATERIA--------------------------------------/
    LCD_Comando(BORRAR_LCD);
    __delay_ms(200);
    LCD_XY(0,0);
    LCD_Cadena("Materia:");
    __delay_ms(200);
    LCD_XY(1,0);
    LCD_Cadena("Microcontroladores");
    __delay_ms(2000);
    for(k=0; k<20;k++)
    {
        LCD_Comando(0x18);
        __delay_ms(500);
    }
    //------------------------PROFESOR----------------------------------------/
    LCD_Comando(BORRAR_LCD);
    __delay_ms(200);
    LCD_XY(0,0);
    LCD_Cadena("Profesor:");
    __delay_ms(200);
    LCD_XY(1,0);
    LCD_Cadena("Cobilt Catana Juan Manuel");
    __delay_ms(2000);
    for(k=0; k<24;k++)
    {
        LCD_Comando(0x18);
        __delay_ms(500);
    }
    //------------------------ALUMNO------------------------------------------/
    __delay_ms(500);
    LCD_Comando(BORRAR_LCD);
    __delay_ms(1000);
    LCD_XY(0,0);
    LCD_Cadena("Alumna:");
    __delay_ms(200);
    LCD_XY(1,0);
    LCD_Cadena("Robles Gonzalez Karina");
    __delay_ms(3000);
    for(k=0; k<21;k++)
    {
        LCD_Comando(0x18);
        __delay_ms(500);
    }
    //-------------------------PRACTICA---------------------------------------/
    LCD_Comando(BORRAR_LCD);
    __delay_ms(200);
    LCD_XY(0,16);
    LCD_Cadena("  REGISTRO SIPO");
    __delay_ms(200);
    LCD_XY(1,16);
    LCD_Cadena("    CON LCD");
    for(k=0; k<17;k++)
    {
        LCD_Comando(0x18);
        __delay_ms(500);
    }
    __delay_ms(5000);
    LCD_Comando(BORRAR_LCD);
    __delay_ms(800);
    LCD_XY(0,0);   
    LCD_Cadena(" REGISTRO SIPO");
    __delay_ms(200);
    LCD_XY(1,0);
    LCD_Cadena("    CON LCD");
    __delay_ms(3000);

    LCD_Comando(BORRAR_LCD);
    __delay_ms(800);
    LCD_XY(0,0);   
    LCD_Cadena(" REGISTRO SIPO");
    __delay_ms(200);
    LCD_XY(1,0);
    LCD_Cadena("    CON LCD");
    __delay_ms(3000);
   
    LCD_Comando(BORRAR_LCD);
    __delay_ms(800);
    LCD_XY(0,0);   
    LCD_Cadena(" REGISTRO SIPO");
    __delay_ms(200);
    LCD_XY(1,0);
    LCD_Cadena("    CON LCD");
    __delay_ms(100);
    __delay_ms(3000);
    for(k=0; k<24;k++)
    {
        LCD_Comando(0x18);
        __delay_ms(500);
    }
}

void datos(char registro)
{
    char aux1,i=0;
    while(i<8)
    {
        aux1=0x01 & registro;
        SERIAL_DATA=aux1;
        positiveSR_tg();
        registro=registro>>1;
        i++;
    }
    positiveLR_tg();
}

void positiveSR_tg(void)
{
    SHIFT_CLOCK=0;
    __delay_us(1);
    SHIFT_CLOCK=1;
    __delay_us(1);
    SHIFT_CLOCK=0;
}

void positiveLR_tg(void)
{
    LATCH_CLOCK=0;
    __delay_us(1);
    LATCH_CLOCK=1;
    __delay_us(1);
    LATCH_CLOCK=0;
}

void LCD_WriteChr_CGRAM(const char *buffer, unsigned char Addres)
{
    LCD_Comando(Addres);
    //__delay_ms(8000);
    for (char i=0;i<8;i++)                        // Write data to LCD up to null
    {  
        LCD_Data(*buffer);      // Write character to LCD
        //__delay_ms(2000);
        buffer++;
        
    }
    //LCD_Cadena(buffer);
    return;
}
