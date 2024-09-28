//#include <at89x52.h>
#include <8052.h>

typedef unsigned int u16;	
typedef unsigned char u8;

u8 rec_data[3];
u8 rec_cnt;

void uart_init(u8 baud) {
	TMOD|=0X20;	//设置计数器工作方式2
	SCON=0X50;	//设置为工作方式1
	PCON=0X80;	//波特率加倍
	TH1=baud;	//计数器初始值设置
	TL1=baud;
	ES=1;		//打开接收中断
	EA=1;		//打开总中断
	TR1=1;		//打开计数器		
}

void uart_send(u8 wdata){
    SBUF = wdata;
    while(!TI);		//waiting for send
    TI=0;			//clear send flag				
}

void main(){	
    rec_cnt = 0;

    P1 = 0x00; // Turn OFF all LED's connected to Port1
    P2 = 0x00;
    P0 = 0x00;

	uart_init(0XFA);//9600
	while(1){			
        if(rec_cnt == 3){
            if(rec_data[0] == 'A'){
                //0~23-->IO
                //24->stop
                u8 index = (rec_data[1]-'0')*10+(rec_data[2]-'0');
                if(index < 24){
                    P0 = 0;
                    P1 = 0;
                    P2 = 0;
                    
                    u8 duan = index/8;//0,1,2
                    u8 wei = index%8;//0~7
                    switch(duan){
                        case 0:P0 = 1<<wei;break;
                        case 1:P1 = 1<<wei;break;
                        case 2:P2 = 1<<wei;break;
                        default:break;
                    }
                }else if(index == 24){
                    P0 = 0;
                    P1 = 0;
                    P2 = 0;
                }

                uart_send('B');
                uart_send(rec_data[1]);
                uart_send(rec_data[2]);
            }
            rec_cnt = 0;  
        }						
	}		
}

//https://github.com/platformio/platform-intel_mcs51/issues/28
void uart1_isr() __interrupt 4
{
    u8 rdata;

	RI = 0;			//clear receive flag
    rdata = SBUF;

    if(rdata == 'A'){
        rec_cnt = 0;
        rec_data[rec_cnt] = rdata;
        rec_cnt = 1;
    }else if(rec_cnt > 0 && rec_cnt < 3){
        rec_data[rec_cnt] = rdata;
        rec_cnt++;
    }


}
