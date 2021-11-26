/*
 * File:   C.c
 * Author: ana_k
 *
 * Created on 26 de octubre de 2021, 11:24
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


#define _XTAL_FREQ 20000000
#include <xc.h>
char o=0x00;
char m=0x00;
int p=0;

void boton(void);
void sw(int v);
void escudo(void);
void clear(void);
void conf(void);
void portada(void);
void corrimiento(void);


void main(void) {
    //PARA el CLOCK
    TRISDbits.RD0=0;
    //PARA EL LATCH
    TRISDbits.RD1=0;
    //PARA EL DATA
    TRISDbits.RD2=0;  
    
    //PARA EL LCD
   // ini_lcd();
    //caratula_lcd();
    conf();
portada(); 
for(int i=0; i<14;i++){
corrimiento ();
}
    //INICIO DEL PROGRAMA
    while (1){
        for(int i = 0; i <= 255; i++) {
             LATDbits.LATD1 = 0;
             for(int x = 0; x <= 7; x++) {
             LATDbits.LATD0 = 0;
             if (i & (1 << x)) {
                  LATDbits.LATD2 = 1;
             }
             else {
                 LATDbits.LATD2 = 0;
             }
             LATDbits.LATD0 = 1;
        }
             LATDbits.LATD1 = 1;
             __delay_ms(500);
        }
    }
    return;
}
           
    


void boton(void){
    LATAbits.LA1=0;
    __delay_ms(5);
    LATAbits.LA1=1;
}

void sw(int v){
    if(v==1){
        LATA=0x03;
    }else{
        LATA=0x02;
    }
    __delay_ms(50);
}

void escudo(void){
    sw(1);  //Caracter basura
    LATD=0X00;
    boton();
    boton();
    LATD=0X00;
    boton();
    LATD=0X10;
    boton();
    LATD=0X00;
    boton();
    LATD=0X20;
    boton();
    LATD=0X00;
    boton();
    LATD=0X30;
    boton();
    LATD=0X00;
    boton();
    LATD=0X40;
    boton();
    LATD=0X00;
    boton();
    LATD=0X50;
    boton();
    
    sw(0);  //segunda linea posicion 1
    LATD=0X40;
    boton();
    LATD=0X00;
    boton();
    
    sw(1);  //modifica caracter basura 1
    LATD=0X00;  //1
    boton();
    LATD=0X70;  
    boton();
    LATD=0X00;  //2
    boton();
    LATD=0XF0;
    boton();
    LATD=0X00;  //3
    boton();
    LATD=0XF0;
    boton();
    LATD=0X00;  //4
    boton();
    LATD=0XF0;
    boton();
    LATD=0X00;  //5
    boton();
    LATD=0XF0;
    boton();
    LATD=0X00;  //6
    boton();
    LATD=0XF0;
    boton();
    LATD=0X00;  //7
    boton();
    LATD=0XF0;
    boton();
    LATD=0X10;  //8
    boton();
    LATD=0XF0;
    boton();
    
    sw(1);  //modifica caracter basura 2
    LATD=0X00;  //1
    boton();
    boton();
    LATD=0X10;  //2
    boton();
    LATD=0X70;
    boton();
    LATD=0X10;  //3
    boton();
    LATD=0X50;
    boton();
    LATD=0X10;  //4
    boton();
    LATD=0X70;
    boton();
    LATD=0X10;  //5
    boton();
    LATD=0X40;
    boton();
    LATD=0X10;  //6
    boton();
    LATD=0XF0;
    boton();
    LATD=0X00;  //7
    boton();
    boton();
    LATD=0X10;  //8
    boton();
    boton();
    
    sw(1);  //modifica caracter basura 3
    LATD=0X00;  //1
    boton();
    boton();
    LATD=0X10;  //2
    boton();
    LATD=0X20;
    boton();
    LATD=0X10;  //3
    boton();
    LATD=0XA0;
    boton();
    LATD=0X10;  //4
    boton();
    LATD=0X60;
    boton();
    LATD=0X10;  //5
    boton();
    LATD=0X20;
    boton();
    LATD=0X10;  //6
    boton();
    LATD=0XE0;
    boton();
    LATD=0X00;  //7
    boton();
    LATD=0XC0; 
    boton();
    LATD=0X00;  //8
    boton();
    LATD=0X60;
    boton();
    
    sw(1);  //modifica caracter basura 4
    LATD=0X10;  //1
    boton();
    LATD=0XF0;  
    boton();
    LATD=0X00;  //2
    boton();
    LATD=0XF0;
    boton();
    LATD=0X10;  //3
    boton();
    LATD=0X80;
    boton();
    LATD=0X00;  //4
    boton();
    LATD=0X80;
    boton();
    LATD=0X10;  //5
    boton();
    LATD=0XD0;
    boton();
    LATD=0X00;  //6
    boton();
    LATD=0X60;
    boton();
    LATD=0X00;  //7
    boton();
    LATD=0X30;
    boton();
    LATD=0X00;  //8
    boton();
    LATD=0X10;
    boton();
    
    sw(1);  //modifica caracter basura 5
    LATD=0X00;  //1
    boton();
    LATD=0XE0;  
    boton();
    LATD=0X10;  //2
    boton();
    LATD=0XF0;
    boton();
    LATD=0X00;  //3
    boton();
    LATD=0XE0;
    boton();
    LATD=0X10;  //4
    boton();
    boton();
    LATD=0X00;  //5
    boton();
    boton(); 
    boton();     //6
    boton(); 
    LATD=0X10;  //7
    boton();
    LATD=0XF0;
    boton();
    LATD=0X10;  //8
    boton();
    LATD=0X50;
    boton();
    
    sw(1);  //modifica caracter basura 1
    LATD=0X00;  //1
    boton();
    LATD=0X60;  
    boton();
    LATD=0X00;  //2
    boton();
    LATD=0X30;
    boton();
    LATD=0X00;  //3
    boton();
    LATD=0X60;
    boton();
    LATD=0X00;  //4
    boton();
    LATD=0X40;
    boton();
    LATD=0X10;  //5
    boton();
    LATD=0X60;
    boton();
    LATD=0X00;  //6
    boton();
    LATD=0XC0;
    boton();
    LATD=0X10;  //7
    boton();
    LATD=0X80;
    boton();
    LATD=0X10;  //8
    boton();
    LATD=0X00;
    boton();
}

void clear(void){
    sw(0);
    LATD=0X00;
    boton();
    LATD=0X10;
    boton();
}

void conf(void){
    ADCON1=0X0F;    // Inhabilitamos al convertidor AD
    CMCON=0X07;     //Inhabilitamos los comparadores asociados al puerto A
    TRISA=0X7C;     //Las terminales RA0 y RA1 son declaradas salidas digital, las otras son entradas
    __delay_ms(500);
    LATA=0X03;      //valor inicial para verificar cambios y colocado en las terminales de PORTA, uso de la logica positiva
    __delay_ms(500);
    
    TRISD=0X00;     //Todas las terminales (RD7-RD0) son declaradas terminales de salida digital
    __delay_ms(500);
    LATD=0XFF;      ////valor inicial para verificar cambios y colocado en las terminales de PORTD, uso de logica positiva.
    __delay_ms(500);

    sw(0);
    LATD=0x20;
    __delay_ms(50);
    boton();
    LATD=0x00;  //Activar cursor
    boton();
    LATD=0xF0;
    boton();
    escudo();
    clear();
    /*Inicializacion del puerto D del microcontrolador. Todas las terminales de PORTD son
digitales, sólo hay que definir si son terminales de entrada o salida*/
}

void portada(void){
    sw(0);
        LATD=0x20;  //Activar cursor
        boton();
        LATD=0x80;
        boton();
        sw(1);
        
        LATD=0X00;  //LOGO l
        boton();
        boton();
        LATD=0X00;  //LOGO 2
        boton();
        LATD=0X10;
        boton();
        LATD=0X00;  //LOGO 3
        boton();
        LATD=0X20;
        boton();
        LATD=0XA0;  //ESPACIO
        boton();
        LATD=0X00;
        boton();
        LATD=0X40;  //I
        boton();
        LATD=0X90;
        boton();
        LATD=0X50;  //P
        boton();
        LATD=0X00;  
        boton();
        LATD=0X40;  //N
        boton();
        LATD=0XE0;
        boton();
        LATD=0XA0;  //ESPACIO
        boton();
        LATD=0X00;
        boton();
        LATD=0X40;  //E
        boton();
        LATD=0X50;
        boton();
        LATD=0X50;  //S
        boton();
        LATD=0X30;
        boton();
        LATD=0X40;  //I
        boton();
        LATD=0X90;
        boton();
        LATD=0X40;  //M
        boton();
        LATD=0XD0;
        boton();
        LATD=0X40;  //E
        boton();
        LATD=0X50;
        boton();
     
        LATD=0XA0;  //ESPACIO
        boton();
        LATD=0X00;  
        boton();
        LATD=0X40;  //K
        boton();
        LATD=0XB0;
        boton();
        LATD=0X40;  //A
        boton();
        LATD=0X10;
        boton();
        LATD=0X50;  //R
        boton();
        LATD=0X20;
        boton();
        LATD=0X40;  //I
        boton();
        LATD=0X90;
        boton();
        LATD=0X40;  //N
        boton();
        LATD=0XE0;
        boton();
        LATD=0X40;  //A
        boton();
        LATD=0X10;
        boton();
       
        LATD=0XA0;  //ESPACIO
        boton();
        LATD=0X00;
        boton();
        LATD=0X50;  //R
        boton();
        LATD=0X20;
        boton();
        LATD=0X40;  //O
        boton();
        LATD=0XF0;  
        boton();
        LATD=0X40;  //B
        boton();
        LATD=0X20;
        boton();
        LATD=0X40;  //L
        boton();
        LATD=0XC0;
        boton();
        LATD=0X40;  //E
        boton();
        LATD=0X50;
        boton();
        LATD=0X50;  //S
        boton();
        LATD=0X30;
        boton();
        LATD=0XA0;  //ESPACIO
        boton();
        LATD=0X00;
        boton();
        LATD=0X40;  //G
        boton();
        LATD=0X70;
        boton();
        LATD=0X40;  //L
        boton();
        LATD=0XC0;
        boton();
        LATD=0X40;  //E
        boton();
        LATD=0X50;
        boton();
        LATD=0X50;  //Z
        boton();
        LATD=0X40;
        boton();
        LATD=0XA0;  //ESPACIO
        boton();
        LATD=0X00;  
        boton();
        
        sw(0);
        LATD=0XC0;  //mover a la segunda linea
        boton();
        LATD=0X00;
        boton();
        
        
        sw(1);
        LATD=0X00;  //LOGO 4
        boton();
        LATD=0X30;
        boton();
        LATD=0X00;  //LOGO 5
        boton();
        LATD=0X40;
        boton();
        LATD=0X00;  //LOGO 6
        boton();
        LATD=0X50;
        boton();
        LATD=0XA0;  //ESPACIO
        boton();
        LATD=0X00;
        boton();
        LATD=0X40;  //I
        boton();
        LATD=0X90;
        boton();
        LATD=0X40;  //N
        boton();
        LATD=0XE0;  
        boton();
        LATD=0X50;  //T
        boton();
        LATD=0X40;
        boton();
        LATD=0X40;  //E
        boton();
        LATD=0X50;
        boton();
        LATD=0X50;  //R
        boton();
        LATD=0X20;
        boton();
        LATD=0X50;  //R
        boton();
        LATD=0X20;
        boton();
        LATD=0X50;  //U
        boton();
        LATD=0X50;
        boton();
        LATD=0X50;  //P
        boton();
        LATD=0X00;
        boton();
        LATD=0X40;  //C
        boton();
        LATD=0X30;
        boton();
        LATD=0X40;  //I
        boton();
        LATD=0X90;
        boton();
        LATD=0X40;  //O
        boton();
        LATD=0XF0;  
        boton();
        LATD=0X40;  //N
        boton();
        LATD=0XE0;
        boton();
        LATD=0X40;  //E
        boton();
        LATD=0X50;
        boton();
        LATD=0X50;  //S
        boton();
        LATD=0X30;
        boton();
        
        
        sw(0);
        LATD=0X00; //apagar el cursor
        boton();
        LATD=0XC0;
        boton();
}

void corrimiento(void){
            LATD=0X10; 
            boton();
            LATD=0X80;
            boton();
            __delay_ms(1000);
    
}



void segundalinea(void){
    sw(0);
    LATD=0XC0;  //mover a la segunda linea
    boton();
    LATD=0X00;
    boton();
}
