#include <8052.h>
 
void delay(void);
 
void main(void){
    while(1){
         P1 = 0xFF; // Turn ON all LED's connected to Port1
         P2 = 0xFF;
         P0 = 0xFF;
         delay();
         P1 = 0x00; // Turn OFF all LED's connected to Port1
         P2 = 0x00;
         P0 = 0x00;
         delay();
    }
}
 
void delay(void){
    int i,j;
    for(i=0;i<0xff;i++)
         for(j=0;j<0xff;j++);
}
