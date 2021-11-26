/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  

// TODO Insert appropriate #include <>

// TODO Insert C++ class definitions if appropriate

// TODO Insert declarations

// Comment a function and leverage automatic documentation with slash star star
/**
    <p><b>Function prototype:</b></p>
  
    <p><b>Summary:</b></p>

    <p><b>Description:</b></p>

    <p><b>Precondition:</b></p>

    <p><b>Parameters:</b></p>

    <p><b>Returns:</b></p>

    <p><b>Example:</b></p>
    <code>
 
    </code>

    <p><b>Remarks:</b></p>
 */
// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

//Libreria LCD//
#define PARAM_SCLASS

/* Display ON/OFF Control defines */
#define DON         0b00001100  /* Display on      */
#define DOFF        0b00001000  /* Display off     */
#define CURSOR_ON   0b00001111  /* Cursor on       */
#define CURSOR_OFF  0b00001101  /* Cursor off      */
#define BLINK_ON    0b00001111  /* Cursor Blink    */
#define BLINK_OFF   0b00001110  /* Cursor No Blink */

/* Comandos creados	*/
#define BORRAR_LCD		0x01		/* Clears the LCD		*/
#define CURSOR_INICIO	0x02		/* Returns the cursor to the HOME position	*/
#define LINEA1          0b10000000  /* 4-bit Interface               */
#define LINEA2          0b11000000  /* 4-bit Interface               */
#define CGRAM_ADDRESS   0b01000000  /* 4-bit Interface
/* Cursor or Display Shift defines */
#define SHIFT_CUR_LEFT    0b00010100  /* Cursor shifts to the left   */
#define SHIFT_CUR_RIGHT   0b00010101  /* Cursor shifts to the right  */
#define SHIFT_DISP_LEFT   0b00011110  /* Display shifts to the left  */
#define SHIFT_DISP_RIGHT  0b00011011  /* Display shifts to the right */

/* Function Set defines */
#define FOUR_BIT   0b00101100  /* 4-bit Interface               */
#define EIGHT_BIT  0b00111100  /* 8-bit Interface               */
#define LINE_5X7   0b00110000  /* 5x7 characters, single line   */
#define LINE_5X10  0b00110100  /* 5x10 characters               */
#define LINES_5X7  0b00111000  /* 5x7 characters, multiple line */

//Caracteres especiales
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
const char es11[]={ 0b00000000,
                    0b00000000,
                    0b00000011,
                    0b00000110,
                    0b00001000,
                    0b00001111,
                    0b00011111,
                    0b00010000, 0};
const char es12[]={ 0b00010101,
                    0b00010010,
                    0b00001001,
                    0b00001001,
                    0b00000110,
                    0b00000011,
                    0b00000000,
                    0b00000000, 0};
const char es21[]={ 0b00000000,
                    0b00000000,
                    0b00011000,
                    0b00001100,
                    0b00000010,
                    0b00011110,
                    0b00011111,
                    0b00000001, 0};
const char es22[]={ 0b00010101,
                    0b00001001,
                    0b00010010,
                    0b00010010,
                    0b00001100,
                    0b00011000,
                    0b00000000,
                    0b00000000, 0};

const char ipn11[]={0b00000000,
                    0b00011100,
                    0b00011101,
                    0b00011101,
                    0b00011101,
                    0b00011100,
                    0b00011110,
                    0b00010001, 0};
const char ipn12[]={0b00011111,
                    0b00010001,
                    0b00001001,
                    0b00001010,
                    0b00000100,
                    0b00000110,
                    0b00000011,
                    0b00000000, 0};
const char ipn21[]={0b00000000,
                    0b00000000,
                    0b00011011,
                    0b00011011,
                    0b00010011,
                    0b00000000,
                    0b00001001,
                    0b00010001, 0};
const char ipn22[]={0b00011111,
                    0b00001001,
                    0b00001010,
                    0b00000110,
                    0b00000100,
                    0b00001100,
                    0b00011000,
                    0b00000000, 0};

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


//Función:
void LCD_Init(void);
void LCD_XY(int x,int y);
void LCD_Cadena(const char *);
void RegistroCOM(PARAM_SCLASS char cmd);
void RegistroESCR(char cmd);
void LCD_WriteChr_CGRAM( const char *buffer, char Addres);
void SetCGRamAddr(char);
void Portada(void);

//Libreria USART//
void USART_Init(long BAUD);
void USART_Tx(char data);
char USART_Rx(void);
void USART_Cadena(char *str);