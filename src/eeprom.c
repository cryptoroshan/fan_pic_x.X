#include <xc.h>


unsigned char eeprom18_read(int address) {
    /*Read operation*/
    EECON1bits.CFGS=0;
    
    EEADR=address;	/* Read data at location 0x00*/
    EECON1bits.WREN=0;	/* WREN bit is clear for Read operation*/  
    EECON1bits.EEPGD=0;	/* Access data EEPROM memory*/
    EECON1bits.RD=1;	/* To Read data of EEPROM memory set RD=1*/
    return(EEDATA);
}

void eeprom18_write(int address, char data) {
    /* Write Operation*/
    EEADR=address;		/* Write address to the EEADR register */
    EEDATA=data;		/* Copy data to the EEDATA register for
				write to EEPROM location */
    EECON1bits.EEPGD=0;		/* Access data EEPROM memory */
    EECON1bits.CFGS=0;		/* Access flash program or data memory */
    EECON1bits.WREN=1;		/* Allow write to the memory */
    INTCONbits.GIE=0;		/* Disable global interrupt */
    
    /* Assign below sequence to EECON2 Register is necessary
       to write data to EEPROM memory */

    EECON2=0x55;
    EECON2=0xaa;
    
    EECON1bits.WR=1;		/* Start writing data to EEPROM memory */
    INTCONbits.GIE=1;		/* Enable interrupt*/
    
    while(PIR2bits.EEIF==0);	/* Wait for write operation complete */
    PIR2bits.EEIF=0;		/* Reset EEIF for further write operation */
}