/*
 * File:   P.c
 * Author: ana_k
 *
 * Created on 23 de noviembre de 2021, 20:07
 */

#include <xc.h>
#include "Configuracion.h"
#include "USART_libreria.h"

void USART_Init(long BAUD){
    
    //Se inicializa la interrupcion
    INTCONbits.GIE=0;   //Deshabilita las interrupciones globales
    PIR1bits.RCIF = 0;  //Bandera de interrupcion a 0
    IPR1bits.RCIP = 1;  //Prioridad alta
    PIE1bits.RCIE = 1;  //Habilitacion de interrupcion de EUSART de recepcion
    
    RCONbits.IPEN = 1;      //Habilitó prioridad
    INTCONbits.GIEL = 1;    //Permite paso de interrupciones de baja prioridad
    INTCONbits.GIEH = 1;    //Habilita las prioridades enmascarables
    
    
    //Configuración de los pines
    TRISCbits.RC6 = 0;      //RC6 = Tx -> Salida
    TRISCbits.RC7 = 1;      //RC7 = Rx -> Entrada
    
    //Baudios
    SPBRG = (unsigned char)(((_XTAL_FREQ/BAUD)/64)-1);
    
    //Configuración 
    TXSTAbits.BRGH = 0;     //Low Speed
    TXSTAbits.SYNC = 0;     //Asincrono
    RCSTAbits.SPEN = 1;     //Habilitar Tx y Rx
    
    //Transmisión
    TXSTAbits.TX9 = 0;      //8 bits
    TXSTAbits.TXEN = 1;     //Activamos transmisión
    
    //Recepción
    RCSTAbits.RC9 = 0;      //8 bits
    RCSTAbits.CREN = 1;     //Activamos recepción
}

void USART_Tx(char data){
    while(TXSTAbits.TRMT == 0);
    TXREG = data;
}

char USART_Rx(){
    return RCREG; 
}

void USART_Cadena(char *str){
    while(*str != '\0'){
        USART_Tx(*str);
        str++;
    }
}


void LCD_Init(void){
        
    TRISDbits.RD0=0;    //Entrada
    TRISDbits.RD1=0;    //Shift CLK
    TRISDbits.RD2=0;    //Latch CLK
    LATD=0;
   
    __delay_ms(15); //Segun datasheet

    
    
    RegistroCOM(0x30);
    __delay_ms(5);
    RegistroCOM(0x30);
    __delay_us(100);
    RegistroCOM(0x32);
    __delay_us(100);
    
    
    __delay_us(100);
    RegistroCOM(0x28);      //Lineas y caracteres
    __delay_us(100);
    RegistroCOM(0x08);      //Display cursor y parpadero: apagado
    __delay_us(100);
    RegistroCOM(0x0f);      //Display cursor y parpadero: enciende
    __delay_us(100);
    RegistroCOM(0x01);      //Limpiar LCD
    __delay_us(100);
    RegistroCOM(0x04);
    __delay_us(100);
    
    __delay_us(100);
    RegistroCOM(0x06);      //Display
    RegistroCOM(0x0C);      //Incremento y no se mueve
    
    
    
    
    __delay_ms(500);
    return;
    
}

void LCD_XY(int x,int y){
    if(x>0){
        //LCD_Comando(0xC0+y);
        RegistroCOM(0xC0+y);
    }
    else{
        //LCD_Comando(0x80+y);
        RegistroCOM(0x80+y);
    }
}

void LCD_Cadena(const char *dato){
    while(*dato){
        __delay_us(100);
        //LCD_Data(*dato);
        RegistroESCR(*dato);
        dato++;
    }
}

void RegistroESCR(char cmd){
 for (int j=4; j>=0; j-=4){
         for(char i=3; i>0; i--){
            LATDbits.LD0=1;         //RS
            LATDbits.LD1=1;
            LATDbits.LD1=0;

            if((i%2)==0){
                LATDbits.LD0=1;         //E
                LATDbits.LD1=1;
                LATDbits.LD1=0;
             }
            else{
                LATDbits.LD0=0;         //E
                LATDbits.LD1=1;
                LATDbits.LD1=0;
            }
            
               for(int k = j; k <= j+3; k++){
                    if((cmd & (1 << k)) != 0){
                    //1
                    LATDbits.LD0 = 1;
                    LATDbits.LD1 = 1;
                    LATDbits.LD1 = 0;
                    }else{
                    //0
                    LATDbits.LD0 = 0;
                    LATDbits.LD1 = 1;
                    LATDbits.LD1 = 0;
            
                    }
                }
          
            

            LATDbits.LD2=1;     //Latch CLK
            LATDbits.LD2=0;
        __delay_ms(3);     
        }
    }
}

void RegistroCOM(PARAM_SCLASS char cmd){
    for (int j=4; j>=0; j-=4){
         for(char i=3; i>0; i--){
            LATDbits.LD0=0;         //RS
            LATDbits.LD1=1;
            LATDbits.LD1=0;

          if((i%2)==0){
                LATDbits.LD0=1;         //E
                LATDbits.LD1=1;
                LATDbits.LD1=0;
             }
            else{
                LATDbits.LD0=0;         //E
                LATDbits.LD1=1;
                LATDbits.LD1=0;
            }

             for(int k = j; k <= j+3; k++){
                    if((cmd & (1 << k)) != 0){
                    //1
                    LATDbits.LD0 = 1;
                    LATDbits.LD1 = 1;
                    LATDbits.LD1 = 0;
                    }else{
                    //0
                    LATDbits.LD0 = 0;
                    LATDbits.LD1 = 1;
                    LATDbits.LD1 = 0;
            
                }
               }

            LATDbits.LD2=1;     //Latch CLK
            LATDbits.LD2=0;
        __delay_ms(3);     
        }
    }
}

void LCD_WriteChr_CGRAM( const char *buffer, char Addres){
    char Dir = (Addres*8) |0b01000000;
    
    RegistroCOM(Dir);
    //SetCGRamAddr(Addres*8);
    for (int i=0;i<8;i++)                        // Write data to LCD up to null
    {  RegistroESCR(*buffer);      // Write character to LCD
       __delay_us(100);
       ++buffer;
    }
}

void Portada(void){
    
        LCD_Init();
        
        LCD_WriteChr_CGRAM(esime_1, 0);
        LCD_WriteChr_CGRAM(esime_2, 1);
        LCD_WriteChr_CGRAM(esime_3, 2);
        LCD_WriteChr_CGRAM(esime_4, 3);
        LCD_WriteChr_CGRAM(esime_5, 4);
        LCD_WriteChr_CGRAM(esime_6, 5);
        LCD_WriteChr_CGRAM(esime_7, 6);
        LCD_WriteChr_CGRAM(esime_8,7);
        
            RegistroCOM(0x01);
            LCD_XY(0, 12);
            RegistroESCR(0);
            __delay_ms(100);
            RegistroESCR(2);
            __delay_ms(100);
            RegistroESCR(3);
            __delay_ms(100);
            
    LCD_WriteChr_CGRAM(ipn_1,9);
    LCD_WriteChr_CGRAM(ipn_2,8);
    LCD_WriteChr_CGRAM(ipn_3,10);
    LCD_WriteChr_CGRAM(ipn_4,11);
    LCD_WriteChr_CGRAM(ipn_5,12);
    LCD_WriteChr_CGRAM(ipn_6,13);
    
        LCD_XY(0, 0);
            RegistroESCR(8);
            __delay_ms(100);
            RegistroESCR(9);
            __delay_ms(100);
            RegistroESCR(10);
            __delay_ms(100);
            
            LCD_XY(0, 0);
            LCD_Cadena("      IPN");
            __delay_ms(100);
            LCD_XY(1, 0);
            LCD_Cadena("   ESIME ZAC");
            __delay_ms(100);

            LCD_XY(0,0);
            RegistroESCR(0);
            __delay_ms(100);
            RegistroESCR(2);
            __delay_ms(100);
            LCD_XY(1,0);
            RegistroESCR(1);
            __delay_ms(100);
            RegistroESCR(3);
            __delay_ms(100);

            LCD_XY(0,14);
            RegistroESCR(4);
            __delay_ms(100);
            RegistroESCR(6);
            __delay_ms(100);
            LCD_XY(1,14);
            RegistroESCR(5);
            __delay_ms(100);
            RegistroESCR(7);
            __delay_ms(100);

            __delay_ms(1500);



            LCD_XY(0, 17);
            LCD_Cadena(" uControladores");
            __delay_ms(100);
            LCD_XY(1, 17);
            LCD_Cadena(" Cobilt Catana");
            __delay_ms(100);

            for(int i=0; i<=22; i++){
                RegistroCOM(SHIFT_DISP_LEFT);
            __delay_ms(100);
            }
    
            __delay_ms(1500);
            //RegistroCOM(0x01);

            LCD_XY(1, 17);
            LCD_Cadena(" >>>>>>>>>>>>>> ");
            __delay_ms(500);
            LCD_XY(0, 17);
            LCD_Cadena(" <<<<<<<<<<<<<< ");
            __delay_ms(500);

            LCD_XY(1, 17);
            LCD_Cadena("     SERIAL       ");
            __delay_ms(500);
            LCD_XY(0, 17);
            LCD_Cadena("  Meza Gonzalez   ");
            __delay_ms(100);
            LCD_XY(1, 17);
            LCD_Cadena("     Ivan      ");
            __delay_ms(1500);

            LCD_XY(0, 0);
            LCD_Cadena("  Presentacion     ");
            __delay_ms(100);
            LCD_XY(1, 0);
            LCD_Cadena("                ");
            LCD_XY(0,0);
            RegistroESCR(0);
            __delay_ms(100);
            RegistroESCR(2);
            __delay_ms(100);
            LCD_XY(1,0);
            RegistroESCR(1);
            __delay_ms(100);
            RegistroESCR(3);
            __delay_ms(100);

            LCD_XY(0,14);
            RegistroESCR(4);
            __delay_ms(100);
            RegistroESCR(6);
            __delay_ms(100);
            LCD_XY(1,14);
            RegistroESCR(5);
            __delay_ms(100);
            RegistroESCR(7);
            __delay_ms(100);


            for(int i=0; i<=22 ; i++){
                RegistroCOM(SHIFT_DISP_RIGHT);
            __delay_ms(100);
            }
            
            
            __delay_ms(4000);
}
