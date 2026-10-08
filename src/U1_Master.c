#include <reg52.h>

sbit write_mode = P3^4; 
sbit COL1 = P2^3; sbit COL2 = P2^2; sbit COL3 = P2^1; 
sbit ROW1 = P2^4; sbit ROW2 = P2^5; sbit ROW3 = P2^6; sbit ROW4 = P2^7;


void UART_Init() {
    SCON = 0x50;  
    TMOD = 0x20;  
    TH1 = 0xFD; //predkosc dzialania
    PCON = 0x00;  
    TR1 = 1; //wlaczenie timera   
}

void SendByte(unsigned char dat) {
    SBUF = dat; //wyslanie
    while(TI == 0); //czeka do momentu wyslania
    TI = 0;
}

unsigned char KeyScan() {
	  unsigned char k = 0;
	
		ROW1 =0;
		if(COL1 == 0) k = '1'; 
		else if(COL2 == 0) k = '2';
    else if(COL3 == 0) k = '3'; 
		ROW1 = 1; if(k) return k;
		
		ROW2 =0;
		if(COL1 == 0) k = '4'; 
		else if(COL2 == 0) k = '5';
    else if(COL3 == 0) k = '6'; 
		ROW2 = 1; if(k) return k;
	
		ROW3 =0;
		if(COL1 == 0) k = '7'; 
		else if(COL2 == 0) k = '8';
    else if(COL3 == 0) k = '9'; 
		ROW3 = 1; if(k) return k;
	
		ROW4 =0;
		if(COL1 == 0) k = '*'; 
		else if(COL2 == 0) k = '0';
    else if(COL3 == 0) k = '#'; 
		ROW4 = 1; if(k) return k;
	
}

void main() {
    unsigned char k, last_k = 0;
    UART_Init();
    write_mode = 1; 
    
    while(1) {
        k = KeyScan();
        if(k != 0 && k != last_k) { //jezeli wykrylo i nie jest trzymany
            SendByte(k);
            last_k = k;
        } else if(k == 0) {
            last_k = 0;
        }
    }
}
