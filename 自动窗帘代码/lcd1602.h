/*************************************************
更多51单片机资料请关注微信公众号：电子应用学习馆
**************************************************
*****************《电子应用学习馆》***************
***************************************************/


#ifndef _LCD1602_H_
#define _LCD1602_H_

#define uchar unsigned char 
#define uint unsigned int 

#define data_1602 P0
uchar code table_num[]="0123456789abcdefg";

sbit rs=P1^0;	 //寄存器选择信号 H:数据寄存器  	L:指令寄存器
sbit rw=P1^1;	 //寄存器选择信号 H:数据寄存器  	L:指令寄存器
sbit e =P1^2;	 //片选信号   下降沿触发

/***********************延时函数************************/
void delay_uint(uint q)
{
	while(q--);
}

/***********************lcd1602写命令函数************************/
void write_com(uchar com)
{
	e=0;
	rs=0;
	rw=0;
	data_1602=com;
	delay_uint(10);
	e=1;
	delay_uint(50);
	e=0;
}

/***********************lcd1602写数据函数************************/
void write_data(uchar dat)
{
	e=0;
	rs=1;
	rw=0;
	data_1602=dat;
	delay_uint(10);
	e=1;
	delay_uint(50);
	e=0;	
}

/***********************lcd1602初始化设置************************/
void init_1602()
{
	write_com(0x38);	//
	write_com(0x0c);
	write_com(0x06);
}


/***********************lcd1602上显示两位十进制数************************/
void write_sfm1(uchar hang,uchar add,uchar date)
{
	if(hang==1)   
		write_com(0x80+add);
	else
		write_com(0x80+0x40+add);
	write_data(0x30+date % 10);	
}



/***********************lcd1602上显示两位十进制数************************/
void write_sfm2_ds1302(uchar hang,uchar add,uchar date)
{
	uchar shi,ge;
	if(hang==1)   
		write_com(0x80+add);
	else
		write_com(0x80+0x40+add);
	shi=date/16;
	ge=date%16;		  
	write_data(table_num[shi]);
	write_data(table_num[ge]);	
}


/***********************lcd1602上显示这字符函数************************/
void write_string(uchar hang,uchar add,uchar *p)
{
	if(hang==1)   
		write_com(0x80+add);
	else
		write_com(0x80+0x40+add);
		while(1)														 
		{
			if(*p == '\0')  break;
			write_data(*p);
			p++;
		}	
}

/***********************lcd1602上显示 两位温度正负************************/
void write_sfm_18b20(uchar hang,uchar add,uint date)
{
	if(hang==1)   
		write_com(0x80+add);
	else
		write_com(0x80+0x40+add);
	write_data(0x30+date / 10 % 10);	
	write_data(0x30+date % 10);	
	write_data(0xdf);	 //度
}

/***********************lcd1602清除显示************************/
void clear_1602()
{
	write_string(1,0,"                ");
	write_string(2,0,"                ");
}

/****************开机液晶显示函数 初始化液晶的内容********************************/
void init_1602_dis_csf()
{
	write_string(1,0,"      :  :   W  ");  
	write_string(2,0,"  2000-  -      ");  
	if(flag_zd_sd == 0)		   //手动
		write_string(1,0," sd");  
	if(flag_zd_sd == 1)		   //自动
		write_string(1,0," zd");  
}

#endif