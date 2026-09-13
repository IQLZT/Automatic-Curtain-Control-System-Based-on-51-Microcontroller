#ifndef _18B20_2LU_H_
#define _18B20_2LU_H_

sbit dq1   = P1^6;	//18b20 IO口的定义
uint temperature1; //


/***********************18b20初始化函数*****************************/
void init1_18b20()
{
	bit q;
	dq1 = 1;				//把总线拿高
	delay_uint(1);	    //15us
	dq1 = 0;				//给复位脉冲
	delay_uint(80);		//750us
	dq1 = 1;				//把总线拿高 等待
	delay_uint(10);		//110us
	q = dq1;				//读取18b20初始化信号
	delay_uint(20);		//200us
	dq1 = 1;				//把总线拿高 释放总线
}

/*************写18b20内的数据***************/
void write1_18b20(uchar dat)
{
	uchar i;
	for(i=0;i<8;i++)
	{					 //写数据是低位开始
		dq1 = 0;			 //把总线拿低写时间隙开始 
		dq1 = dat & 0x01; //向18b20总线写数据了
		delay_uint(5);	 // 60us
		dq1 = 1;			 //释放总线
		dat >>= 1;
	}	
}

/*************读取18b20内的数据***************/
uchar read1_18b20()
{
	uchar i,value;
	for(i=0;i<8;i++)
	{
		dq1 = 0;			 //把总线拿低读时间隙开始 
		value >>= 1;	     //读数据是低位开始
		dq1 = 1;			 //释放总线
		if(dq1 == 1)		 //开始读写数据 
			value |= 0x80;
		delay_uint(5);	 //60us	读一个时间隙最少要保持60us的时间
	}
	return value;		 //返回数据
}

/*********1111****读取温度的值 读出来的是小数***************/
uint read1_temp()
{
	uint value;
	uchar low;			   //在读取温度的时候如果中断的太频繁了，就应该把中断给关了，否则会影响到18b20的时序
	init1_18b20();		   //初始化18b20
	write1_18b20(0xcc);	   //跳过64位ROM
	write1_18b20(0x44);	   //启动一次温度转换命令
	delay_uint(50);		   //500us

	EA = 0;
	init1_18b20();		   //初始化18b20	
	write1_18b20(0xcc);	   //跳过64位ROM
	write1_18b20(0xbe);	   //发出读取暂存器命令
		
	low = read1_18b20();	//读温度低字节
	value = read1_18b20();  //读温度高字节
	EA = 1;

	value <<= 8;		   //把温度的高位左移8位
	value |= low;		   //把读出的温度低位放到value的低八位中
	value *= 0.0625;	       //转换到温度值 小数
	return value;		   //返回读出的温度 
}



#endif