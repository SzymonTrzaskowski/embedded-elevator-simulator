#include <reg52.h>

sbit LCD_RS = P2^4; 
sbit LCD_RW = P2^5; 
sbit LCD_E  = P2^6; 

sbit RS485_DIR = P3^4; 

//stale deklaracje mozna wrzucic do pamieci program a nie dat a
unsigned char code arrow_up[] = {0x04, 0x0E, 0x1F, 0x04, 0x04, 0x04, 0x04, 0x00};
unsigned char code elevator[] = {0x1F, 0x11, 0x15, 0x15, 0x11, 0x1F, 0x00, 0x00};

unsigned int disp_val = 0;
unsigned int floor_target = 0;
unsigned char update_lcd = 0;


void Lcd_Nibble(unsigned char n) {
    P2 = (P2 & 0xF0) | (n & 0x0F); //czysci i wysyla n
    LCD_E = 1; //znaczy pobierz wystawione dane 
    LCD_E = 0;
}

void Lcd_Write(unsigned char value, unsigned char mode) {
    LCD_RS = mode; //czy komendy czy wyswietlanie
    LCD_RW = 0;
    Lcd_Nibble(value >> 4); //starsze 4
    Lcd_Nibble(value);
}

void Lcd_Text(char *s) { //cale zdania
    while(*s) Lcd_Write(*s++, 1);
}

void Create_Char(unsigned char number, unsigned char *ptr) { //Deklaracja emoji
    unsigned char i;
    Lcd_Write(0x40 + (number * 8), 0);
    for(i=0; i<8; i++) Lcd_Write(ptr[i], 1);
}

void Show_Welcome() {
    Lcd_Write(0x01, 0); //Czysc ekran
    Lcd_Write(0x80, 0); 
		Lcd_Text(" Witaj w ");
    Lcd_Write(1, 1);    //Emoji windy
    Lcd_Write(0xC0, 0);
		Lcd_Text(" Podaj pietro:");
		Lcd_Write(0xC0, 0);
}

void Init_System() {
    SCON = 0x50; 
    TMOD = 0x21; 
    TH1 = 0xFD;  
    TR1 = 1;
    
    ES = 1; // Wlacz przerwania UART
    EA = 1; // Globalne przerwania
    RS485_DIR = 0; 
}

void UART_ISR() interrupt 4 {
    if(RI) {
        unsigned char r = SBUF;
        RI = 0;
        if(r >= '0' && r <= '9') {
            disp_val = (disp_val * 10) + (r - '0');
        } 
				else if(r == '*') {
            floor_target = disp_val;
            update_lcd = 1;
            disp_val = 0;
        } 
				else if(r == '#') {
            disp_val = 0;
            Show_Welcome();
        }
    }
}

void main() {
    Init_System(); 

    LCD_RS = 0; LCD_RW = 0; LCD_E = 0;
    Lcd_Nibble(0x03); 
    Lcd_Nibble(0x03); 
    Lcd_Nibble(0x03); 
    Lcd_Nibble(0x02); 
    Lcd_Write(0x28, 0); // 4 bity, 2 linie
		Create_Char(1, elevator);
    Create_Char(2, arrow_up);
    Lcd_Write(0x0C, 0); // ON, kursor OFF
    Lcd_Write(0x01, 0); 


    Show_Welcome();

    while(1) {
        if(update_lcd) {
            Lcd_Write(0x01, 0);
            Lcd_Write(0x80, 0); //poczatek pierwszej linii
            Lcd_Text(" Jedziemy");
						Lcd_Write(2, 1);
            Lcd_Write(0xC0, 0);
						Lcd_Text(" PIETRO ");
						Lcd_Write((floor_target / 10) + '0', 1); 
						Lcd_Write((floor_target % 10) + '0', 1);
            
            update_lcd = 0;
        }
    }
}
