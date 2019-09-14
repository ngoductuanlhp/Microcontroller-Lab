/*******************************************************************************************
* FileName:        BBSPI_LCD.c
* Dependencies:    See INCLUDES section below
* Processor:       PIC18F8722 and PIC18F87J11 on PICDEM PIC18 Explorer
* Compiler:        XC8
* Version:         1.34
* Company:         Microchip Technology, Inc.
********************************************************************************************
*   PICDEM PIC18 Explorer Setup Details
*
*   LCD Module on PICDEM PIC18 Explorer is LCM-S01602DTR/M
*   Display controller is based on the Hitachi 44780U
*   Display is 16 characters x 2 lines; 5x7 dot resolution w/ cursor or 5x8 w/o cursor
*   Parallel I/O Expander for SPI interface is MCP23S17
*********************************************************************************************
*   LCD interface on PICDEM PIC18 Explorer board:
*
*   Control/Power Lines to LCD Module
*   MCP23S17 PORTA7 = RS        : LCD Register Select, (Instruction Reg = 0; Data Reg = 1)
*   MCP23S17 PORTA7 = LCD EN    : LCD enable signal
*   R/W = GND (0)               : Data Write only
*   Vdd = +5                    : LCM-S01602DTR/M Specification for Vdd
*   Vss = GND (0)               : LCM-S01602DTR/M Specification for Vss
*
*   Data lines for LCD Module
*   MCP23S17 PORTB<7:0> = LCD D<7:0>
*********************************************************************************************
*   SPI (Master) interface to MCP23S17 (Slave):
*
*   RA2       = CS              : MCP23S17 Chip Select
*   RC5/SD01  = SI              : MCP23S17 Serial Data Input
*   RC3/SCK1  = SCK             : MCP23S17 Serial Clock Input
*   RF6       = RESET           : MCP23S17 Hardware Reset
*********************************************************************************************/

#include "BBSPI_LCD.h"

/*******************************************************************
* FUNCTION:     LCDInit ()
* INPUTS:       None
* OUTPUTS:      None
* DESCRIPTION:  Initialize the LCD
********************************************************************/

void LCDInit (void)
{
    InitBBSPI();                    // initialize SPI
    LCD_RST_TRIS = 0;               // set RF6 as output to control RESET pin
    LCD_RST = 0;                    // reset MCP23S17
    __delay_ms(LCD_delay);
    LCD_RST = 1;
    Port_BBSPIInit (PORTA_DIR);     // initialize MCP23S17 PORTA
    Port_BBSPIInit (PORTB_DIR);     // initialize MCP23S17 PORTB
    WritePort_BBSPI (PORTA_ADD, 0);
    __delay_ms(LCD_Startup);        // required by display controller to allow power to stabilize
    LCDPutInst(0x32);               // required by display initialization
    LCDPutInst(FUNCTION_SET);       // set interface size, # of lines and font
    LCDPutInst(DISPLAY_SETUP);      // turn on display and sets up cursor
    mLCD_CLEAR;                     // clear the display
    LCDPutInst(ENTRY_MODE);         // set cursor movement direction
}

/*******************************************************************
* FUNCTION:     InitBBSPI ()
* INPUTS:       None
* OUTPUTS:      None
* DESCRIPTION:  Initialize I/O Ports for Bit Bang SPI
********************************************************************/

void InitBBSPI (void)
{
    LCD_CS_TRIS = 0;      // make the CS pin an output
    LCD_DIN_TRIS = 1;     // make the DIN pin an input
    LCD_DOUT_TRIS = 0;    // make the DOUT pin an output
    LCD_SCLK_TRIS = 0;    // make the SCLK pin an output

    LCD_CS = 1;           // raise the CS pin
    LCD_DIN = 1;          // set the DIN pin
    LCD_DOUT = 0;         // clear the DOUT pin
    LCD_SCLK = 0;         // clear the SCLK pin
}

/*******************************************************************
* FUNCTION:     SendByteBBSPI ()
* INPUTS:       output = byte to be transmitted
* OUTPUTS:      None
* DESCRIPTION:  Outputs a byte through the set DOUT pin
*               and receives dummy data through the DIN pin
********************************************************************/

void SendByteBBSPI (unsigned char output)
{
    unsigned char bitcount;
    unsigned char input = output;
    
    for(bitcount=0;bitcount<8;bitcount++)
    {
       // transmit data MSB
        if(output & 0x80)                // condition if transmit byte MSB is 1
            LCD_DOUT = 1;                // make SDO pin output high
        else                             // condition if byte MSB is 0
            LCD_DOUT = 0;                // make SDO pin output low
        // receive dummy data
        if (LCD_DIN)                     // condition if receive byte MSB is 1
            input = (input << 1) | 0x1;  // shift input 1 bit to the left and move carry bit to LSB
        else                             // condition if receive bit is 0
            input = input << 1;          // shift input 1 bit to the left
        LCD_SCLK = 1;                           // set the SCLK pin
        NOP();NOP();NOP();NOP();NOP();NOP();    // produces ~50% duty cycle clock
        NOP();NOP();NOP();NOP();NOP();NOP();
        LCD_SCLK = 0;                           // clear the SCLK pin
        output <<= 1;                           // shift output 1 bit to the left
    }
}

/*******************************************************************
* FUNCTION:     Port_BBSPIInit ()
* INPUTS:       port_dir = address of IODIRx
* OUTPUTS:      None
* DESCRIPTION:  Initialize MCP923S17 Portx as output
********************************************************************/

void Port_BBSPIInit (unsigned char port_dir)
{
    // IOCON.BANK POR/RST Value = 0
    // Sequence = Device Opcode + Register Address + 1 Data Byte

    LCD_CS = 0;                 // lower CS to initialize SPI write operation on MCP923S17
    SendByteBBSPI(0x40);        // transmit device opcode (slave address and write enable)
    SendByteBBSPI(port_dir);    // point to address of IODIRx(I/O Direction register of PORTx)
    SendByteBBSPI(0x00);        // set all PORTx pins as output
    LCD_CS = 1;                 // end sequence
}

/*******************************************************************
* FUNCTION:     WritePort_BBSPI ()
* INPUTS:       port_add = address of GPIOx
*               a = instruction register or data register
* OUTPUTS:      None
* DESCRIPTION:  Writes to PORTx and selects between data and instruction
*               register
********************************************************************/

void WritePort_BBSPI (unsigned char port_add, unsigned char a)
{
    LCD_CS = 0;                 // lower CS to initialize SPI write operation on MCP923S17
    SendByteBBSPI(0x40);        // transmit device opcode (slave address and write enable)
    SendByteBBSPI(port_add);    // point to address of GPIOx (General Purpose I/O of PORTx)
    SendByteBBSPI(a);           // write value to GPIOx
    LCD_CS = 1;                 // end sequence
}

/*******************************************************************
* FUNCTION:     LCDPutChar ()
* INPUTS:       ch = character to send
* OUTPUTS:      None
* DESCRIPTION:  Writes character to LCD at current cursor position
********************************************************************/

void LCDPutChar (unsigned char ch)
{
    __delay_ms(LCD_delay);
    WritePort_BBSPI (PORTA_ADD, data);        // prepare to send data to LCD
    __delay_ms(1);
    WritePort_BBSPI (PORTB_ADD, ch);          // write the character to be displayed
    __delay_ms(1);
    WritePort_BBSPI (PORTA_ADD, send_data);   // send data to LCD
    __delay_ms(1);
    WritePort_BBSPI (PORTA_ADD, 0x00);        // stop sending data to LCD
}

/*******************************************************************
* FUNCTION:     LCDPutInst ()
* INPUTS:       ch = character to send
* OUTPUTS:      None
* DESCRIPTION:  Writes character to LCD instruction register
*******************************************************************/

void LCDPutInst (unsigned char ch)
{
    __delay_ms(LCD_delay);
    WritePort_BBSPI (PORTA_ADD, instr);       // prepare to send instruction to LCD
    __delay_ms(1);
    WritePort_BBSPI (PORTB_ADD, ch);          // write the instruction to be sent to LCD
    __delay_ms(1);
    WritePort_BBSPI (PORTA_ADD,send_instr);   // send instruction to LCD
    __delay_ms(1);
    WritePort_BBSPI (PORTA_ADD, 0x00);        // stop sending instruction to LCD
}

/*******************************************************************
* FUNCTION:     LCDPutStr ()
* INPUTS:       *ptr = Pointer to string to send
* OUTPUTS:      None
* DESCRIPTION:  Writes string to LCD at current cursor position
*******************************************************************/

void LCDPutStr (const char *ptr)
{
    while(*ptr) LCDPutChar(*(ptr++));
}