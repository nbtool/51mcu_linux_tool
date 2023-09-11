#include <at89x52.h>

typedef unsigned int u16;	//对系统默认数据类型进行重定义
typedef unsigned char u8;


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

void main(){	
	uart_init(0XFA);//波特率为9600

	while(1){			
							
	}		
}

//https://github.com/platformio/platform-intel_mcs51/issues/28
void uart1_isr() __interrupt 4 //串口通信中断函数
{
	u8 rec_data;

	RI = 0;			//清除接收中断标志位
	rec_data=SBUF;	//存储接收到的数据
	SBUF=rec_data;	//将接收到的数据放入到发送寄存器
	while(!TI);		//等待发送数据完成
	TI=0;			//清除发送完成标志位				
}
