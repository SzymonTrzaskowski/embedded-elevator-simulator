#include <reg52.h>


sbit RS485_DIR = P3^4; 
sbit SENSOR = P3^2;    
sbit IN1 = P2^1; sbit IN2 = P2^2; 
sbit IN3 = P2^5; sbit IN4 = P2^6; 
sbit EN2 = P2^4; 

volatile unsigned int disp_val = 0; 
volatile unsigned int rev_goal = 0;  
volatile unsigned int rev_count = 0; 
volatile unsigned char motor_running = 0;    

void Init_System() {
    SCON = 0x50; TMOD = 0x21; TH1 = 0xFD; TR1 = 1;
    IT0 = 1; EX0 = 1; //przerwania i0 na wysoki i zezwalaj
		ES = 1; EA = 1; //wlacz przerwania i4
    RS485_DIR = 0; 
}

void Reset_All() {
    motor_running = 0;
    IN3 = 0; IN4 = 0; EN2 = 0; //wylacza segment mostka
    rev_count = 0;
    disp_val = 0; // Czyscimy wpisana liczbe, zeby zaczac od nowa
}

void External0_ISR() interrupt 0 { //Liczy i wylacza silnik (P3.2 zmiany)
    if (motor_running) {
        rev_count++;
        if (rev_count >= rev_goal) {
            motor_running = 0; 
        }
    }
}

void UART_ISR() interrupt 4 {
    if(RI) {
        unsigned char r = SBUF;
        RI = 0;
        if(r >= '0' && r <= '9') {
            disp_val = (disp_val * 10) + (r - '0');
            if (disp_val > 99) disp_val %= 100; 
        }
        else if(r == '*') { //Akceptacja dzialania
            rev_goal = disp_val;
            rev_count = 0;
            motor_running = 1;
            disp_val = 0; 
        }
        else if(r == '#') {
            Reset_All();
        }
    }
}

void main() {
    Init_System();
    Reset_All(); 

    while(1) {
        if (motor_running) {
            EN2 = 1;
            IN3 = 1; //silnik w prawo
            IN4 = 0;
        } else {
            IN3 = 0; IN4 = 0; EN2 = 0;
        }
    }
}
