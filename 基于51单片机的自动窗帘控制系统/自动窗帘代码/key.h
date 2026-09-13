#ifndef _KEY_H_
#define _KEY_H_
#include "lcd1602.h"

#define key_io P3	 //按键IO口的宏定义
uchar key_can;		 //按键值的变量

void key()
{
	static uchar key_new = 0,key_old = 0,key_value = 0;
	key_io |= 0x1f;
	if(key_new == 0)		 //按键松开
	{
		if((key_io & 0x1f) == 0x1f)
			key_value ++;
		else 
			key_value = 0;
		if(key_value >= 5)	 //按键松开松手检测
		{
			key_value = 0;
			key_new = 1;
			flag_lj_en = 0;		//关闭连加使能
			flag_lj_3_en = 0;	//关闭3秒后使能
			flag_value = 0;		//清零
			key_time = 0;
//			write_eepom();  	//保存
		}
	}
	else 
	{
		if((key_io & 0x1f) != 0x1f)	 //按键按下
			key_value ++;
		else 
			key_value =0;
		if(key_value >= 2)	//按键按下消抖
		{
			key_value = 0;
			key_new = 0;
			flag_lj_en = 1;	 //连加使能
		}
	}
	key_can = 20;
	if(key_500ms == 1)
	{
		key_500ms = 0;
		key_new = 0;
		key_old = 1;
	}
	if((key_new == 0) && (key_old == 1))
	{
		switch(key_io & 0x1f)
		{
			case 0x1e: key_can = 5; break;	  //得到按键值 
			case 0x1d: key_can = 4; break;	  //得到按键值 
			case 0x1b: key_can = 3; break;	  //得到按键值 
			case 0x17: key_can = 2; break;	  //得到按键值 
			case 0x0f: key_can = 1; break;	  //得到按键值 
		}
		flag_kaig_moshi = 0;
//		write_sfm1(1,0,key_can);
	}			 
	key_old = key_new;	 
}







#endif