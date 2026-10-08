#include <reg52.h>

sbit RS485_DIR = P3^4; 
sbit DIG1 = P2^0; sbit DIG2 = P2^1; 

unsigned char disp_val = 0; 
unsigned char seg_map[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

void Init_System() {
    SCON = 0x50; 
    TMOD = 0x21; //Dwa timery
    TH1 = 0xFD;
    TR1 = 1; //wlacza timer

    TH0 = 0xFC; IE = 0x92; TR0 = 1;
    RS485_DIR = 0; // Tylko sluchanie
}

void UART_ISR() interrupt 4 {
    if(RI){
        unsigned char r = SBUF;
        RI = 0;
        if(r >= '0' && r <= '9') {
            disp_val = (disp_val % 10) * 10 + (r - '0');
        }
        else if(r == '*' || r == '#') {
            disp_val = 0;
        }
    }
}

void T0_ISR() interrupt 1 {
    static unsigned char digit = 0; //Flaga co zapalone
    TH0 = 0xFC; TL0 = 0x66;
    DIG1 = 1; DIG2 = 1; //Wygasza obie na chwile
    
    if(digit == 0) { //wyswietla raz jeden raz drugi ekran
        P1 = seg_map[disp_val / 10]; 
        DIG1 = 0; 
    }
    else { 
        P1 = seg_map[disp_val % 10]; 
        DIG2 = 0; 
    }
    digit = !digit; //nast ekran w nast powtorzeniu
}

void main() {
    Init_System();
    while(1);
}
