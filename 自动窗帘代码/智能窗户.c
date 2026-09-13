

#include <reg52.h>
	   
#define uchar unsigned char 
#define uint  unsigned int	 

bit flag_200ms ;
sbit beep = P1^7;     //蜂鸣器IO口定义
sbit LED=P2^7;        //灯光模块
bit flag_relay_en;   
uchar flag_kaig_moshi=0;//开关模式
bit flag_zd_sd;		  //自动 手动 模式

bit flag_lj_en;		 //按键连加使能
bit flag_lj_3_en;	 //按键连3次连加后使能 加的数就越大了 
uchar key_time,flag_value;      //用做连加的中间变量
bit key_500ms  ;
uchar menu_shudu = 20;  //用来控制连加的速度
uchar value,i;

uchar k_shi=1,k_fen=2;	//开窗帘时间
uchar g_shi=3,g_fen=4;			//关窗帘时间
 
uint t_high;                  //高温报警值

sbit DO=P3^7;		//DO定义为P1口的第4位脚，连接ADC0832DO脚
sbit SCL=P3^6;		//SCL定义为P1口的第3位脚，连接ADC0832SCL脚
sbit CS=P3^5;		//CS定义为P1口的第4位脚，连接ADC0832CS脚
uchar guanxian,guanxian_set = 4;     //光线
void write_eepom();


#include "eepom52.h"
#include "key.h"
#include "ds1302.h"
#include "lcd1602.h"
#include "18b20_2lu.h"
#include "bujindianji.h"

sbit key_jia = P3^1;   //加
sbit key_jie = P3^2;   //减


/*************写单片机内部EEPOM*************/
void write_eepom()
{	
	SectorErase(0x2000);
	byte_write(0x2000,flag_zd_sd);
	byte_write(0x2001,k_shi%256);
	byte_write(0x2002,k_fen%256);
	byte_write(0x2003,g_shi%256);
	byte_write(0x2004,g_fen%256);
	byte_write(0x2005,t_high%256);
	byte_write(0x2009,guanxian_set%256);	
	byte_write(0x2010,bjdj_value%256);	
	byte_write(0x2050,a_a);	
}

/*************读单片机内部EEPOM*************/
void read_eepom()
{
	flag_zd_sd = byte_read(0x2000);	
	k_shi  = byte_read(0x2001);	
	k_fen  = byte_read(0x2002);	
	g_shi  = byte_read(0x2003);	
	g_fen  = byte_read(0x2004);	
	t_high  = byte_read(0x2005);	
	guanxian_set  = byte_read(0x2009);	
	bjdj_value  = byte_read(0x2010);	
	a_a = byte_read(0x2050);
}	

/*************初始化EEPROM************/
void init_eepom()	//初始化EEPROM
{
   read_eepom();
 	if(a_a == 0xff)	
	{
		flag_zd_sd = 1;     //模式设置
		a_a=1;
		k_shi=8;
		k_fen=2;			//开
		g_shi=3;
		g_fen=4;			//关
		t_high=35;	
		guanxian_set=4;
		bjdj_value=0;
		write_eepom();		
	}
	
}
#include "menu.h"

/***************读数模转换数据****************/	
//请先了解ADC0832模数转换的串行协议，再来读本函数，主要是对应时序图来理解，本函数是模拟0832的串行协议进行的
						//  1  0  0 通道
						//  1  1  1 通道 
unsigned char ad0832read(bit SGL,bit ODD)
{
	unsigned char i=0,value=0,value1=0;		
		SCL=0;
		DO=1;
		CS=0;		//开始
		SCL=1;		//第一个上升沿	
		SCL=0;
		DO=SGL;
		SCL=1;  	//第二个上升沿
		SCL=0;
		DO=ODD;
		SCL=1;	    //第三个上升沿
		SCL=0;	    //第三个下降沿
		DO=1;
		for(i=0;i<8;i++)
		{
			SCL=1;
			SCL=0; //开始从第四个下降沿接收数据
			value<<=1;
			if(DO)
				value++;						
		}
		for(i=0;i<8;i++)
		{			//接收校验数据
			value1>>=1;
			if(DO)
				value1+=0x80;
			SCL=1;
			SCL=0;
		}
		CS=1;
		SCL=1;	
		if(value==value1)		//与校验数据比较，正确就返回数据，否则返回0	
			return value;
	return 0;
}



/******************1ms 延时函数*******************/
void delay_1ms(uint q)
{
	uint i,j;
	for(i=0;i<q;i++)
		for(j=0;j<120;j++);
}

/*************定时器0初始化程序***************/
void init_1602_ds1302()
{
	write_sfm2_ds1302(2,4,nian);	
	write_sfm2_ds1302(2,7,yue);	
	write_sfm2_ds1302(2,10,ri);	
	write_sfm2_ds1302(1,4,shi);	
	write_sfm2_ds1302(1,7,fen);	
	write_sfm2_ds1302(1,10,miao);
	write_sfm1(1,14,week);		
}									   

/*************定时器0初始化程序***************/
void init_time0()	  
{
	EA   = 1;	 	  //开总中断
	TMOD = 0X01;	  //定时器0、工作方式1
	ET0  = 1;		  //开定时器0中断 
	TR0  = 1;		  //允许定时器0定时
}

/*************手动开关窗帘***************/
void shoudong_kaiguan()	  //手动开关窗帘
{
	if(flag_zd_sd == 0)	  //手动模式
	{
		if(menu_1 == 0)
		{
			if(flag_kaig_moshi == 0)
			{
				if(key_can == 2)
					flag_z_f = 1;     //手动开窗
				if(key_can == 3)
					flag_z_f = 2;     //手动关窗
				if(flag_lj_en == 0)
					flag_z_f = 0;
			}
		}
	}
}

															
/*********************智能窗帘处理函数***********************/
void zinengchuanglian_dis()	  //智能窗帘处理函数
{
	if(flag_zd_sd == 1)
	{ if((miao == 0) && (fen == k_fen) && (shi == k_shi))	  //定时开窗
	  {
		flag_z_f = 2;    //关窗 
		
			flag_kaig_moshi = 1;
	  }
	  if((miao == 0) && (fen == g_fen) && (shi == g_shi))	  //定时关窗
	  {
		flag_z_f = 1;     //开窗   
		flag_kaig_moshi = 2;
	  }
		if(flag_kaig_moshi == 0)//白天晚上适用，中午不会依据光强自动关
		{
			if(guanxian <= guanxian_set)
			  flag_z_f = 1;     //手动开窗
				
			else 
				flag_z_f = 2; 
		}	                    //手动关窗
	} 
}


void main()
{	
	init_eepom();		 //初始化EEPROM
	init_1602();		 //lcd1602初始化
	init_1602_dis_csf(); //lcd1602初始化显示
	init_ds1302_io();	 //初始化ds1302Io
	init_time0();		 //初始化定时器
	menu_1_break();	     //菜单初始界面
	init_ds1302();		 //ds1302初始化
	temperature1 = read1_temp();  //读温度1
	delay_1ms(650);
	while(1)
	{
		key();			 //按键程序
		if(key_can < 10)
		{
			key_with();	
		}
		 if(guanxian <= guanxian_set)
		  LED=1;
		 else
			  LED=0;
		       
		shoudong_kaiguan();	  //手动开关窗帘
		if(flag_200ms == 1)
		{		
			flag_200ms = 0;
			zinengchuanglian_dis();	  //智能窗帘处理函数
			temperature1 = read1_temp();  //读温度1	环境温度
			if(temperature1 >= 99)
				temperature1 = 99;
			if(temperature1 >= t_high)
		 		   beep =	~beep;        //温度报警 ，蜂鸣器报警
				else 
					 beep = 1;
			guanxian = ad0832read(1,0) * 9.0 / 255;
			if((menu_1 == 0))
			{
				read_time();		  //读时间
				init_1602_ds1302();   //显示时钟
				write_sfm_18b20(2,13,temperature1);	//显示温度
				write_sfm1(2,0,guanxian);	//显示温度
			}
		}
		bujindj();	 //步进电机函数
	}
}

void time0() interrupt 1
{			 
	static uchar value;
	TH0 = 0X3C;
	TL0 = 0XB0;	   //50ms
	value ++;
	if(value >= 4)			 //200ms
	{
		value = 0;
		flag_200ms = 1;
	}
	if(flag_lj_en == 1)	   //按下按键使能
	{
		key_time ++;
		if(key_time >= menu_shudu) //500ms
		{
			key_time = 0;
			key_500ms = 1; //500ms
			flag_value ++;
			if(flag_value > 3)
			{
				flag_value = 10;
				flag_lj_3_en = 1; //3次后1.5秒后连加大些
			}						
		}
	}
}

