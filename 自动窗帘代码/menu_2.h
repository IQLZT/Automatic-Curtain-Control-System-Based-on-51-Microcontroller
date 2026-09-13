#ifndef _MENU_2_H_
#define _MENU_2_H_

#include "menu_value.h"

void menu_1_init();
void menu_2_init();
void menu_3_init();
void menu_4_init();

void menu_1_1_n(uchar num);
void menu_1_2_n(uchar num);
void menu_1_3_n(uchar num);
void menu_1_4_n(uchar num);
void menu_1_5_n(uchar num);
void menu_1_6_n(uchar num);
void menu_1_7_n(uchar num);
void menu_2_1_n(uchar num);
void menu_2_2_n(uchar num);
void menu_3_1_n(uchar num);
void menu_3_2_n(uchar num);
void menu_3_3_n(uchar num);
void menu_3_4_n(uchar num);
void menu_4_1_n(uchar num);

/**************************_1_1******************************/
void menu_1_1_dis()
{
	write_string(1,0,"    -  -    W:  ");
    write_string(2,0," 20  -  -       ");	
	write_sfm2_ds1302(2,3,nian);	
	write_sfm2_ds1302(2,6,yue);	
	write_sfm2_ds1302(2,9,ri);	
	write_sfm2_ds1302(1,2,shi);	
	write_sfm2_ds1302(1,5,fen);	
	write_sfm2_ds1302(1,8,miao);
	write_sfm1(1,14,week);
}

void menu_1_1_shudu()
{
	if(flag_lj_3_en == 0)
		menu_shudu = 10 ;  //500ms 	加减一次
	else 
		menu_shudu = 6;  //200ms 加减一次
}

void menu_1_1_init()		//时
{
    menu_2 = 1; menu_3 = 0; 
    menu_1_1_dis();
	write_com(0x80+2);  //将光标移动到秒个位
	write_com(0x0f);    //显示光标并且闪烁	
    key_up_down = menu_1_1_n;
    key_break = menu_1_init;
    menu_i = 1;
	menu_shudu = 20 ;       //50ms 的定时、 10就对应500ms  20对应1s	
}

void menu_1_2_init()	    //分
{
    menu_2 = 2; menu_3 = 0; 
	write_com(0x80+5);//将光标移动到秒个位
	write_com(0x0f);//显示光标并且闪烁	
    key_up_down = menu_1_2_n;
    key_break = menu_1_init;
    menu_i = 2;
	menu_shudu = 20 ;       //50ms 的定时、 10就对应500ms  20对应1s	
}

void menu_1_3_init()	   //秒
{
    menu_2 = 3; menu_3 = 0; 	
	write_com(0x80+8);//将光标移动到秒个位
	write_com(0x0f);//显示光标并且闪烁	
    key_up_down = menu_1_3_n;
    key_break = menu_1_init;
    menu_i = 3;
	menu_shudu = 20 ;       //50ms 的定时、 10就对应500ms  20对应1s	
}

void menu_1_4_init()	//星期
{
    menu_2 = 3; menu_3 = 0; 
	write_sfm1(1,14,week);
	write_com(0x80+14);//将光标移动到秒个位
	write_com(0x0f);   //显示光标并且闪烁	
    key_up_down = menu_1_4_n;
    key_break = menu_1_init;
    menu_i = 4;
	menu_shudu = 20 ;       //50ms 的定时、 10就对应500ms  20对应1s	
}

void menu_1_5_init()	 //年
{
    menu_2 = 5; menu_3 = 0; 
	write_com(0x80+0x40+3);//将光标移动到秒个位
	write_com(0x0f);//显示光标并且闪烁	
    key_up_down = menu_1_5_n;
    key_break = menu_1_init;
    menu_i = 5;
	menu_shudu = 20 ;       //50ms 的定时、 10就对应500ms  20对应1s	
}

void menu_1_6_init()	  //月
{
    menu_2 = 6; menu_3 = 0; 
	write_sfm2_ds1302(2,6,yue);	
	write_com(0x80+0x40+6);//将光标移动到秒个位
	write_com(0x0f);//显示光标并且闪烁	
    key_up_down = menu_1_6_n;
    key_break = menu_1_init;
    menu_i = 6;
	menu_shudu = 20 ;       //50ms 的定时、 10就对应500ms  20对应1s	
}

void menu_1_7_init()	  //日
{
    menu_2 = 7; menu_3 = 0; 
	write_sfm2_ds1302(2,9,ri);
	write_com(0x80+0x40+9);//将光标移动到秒个位
	write_com(0x0f);//显示光标并且闪烁	
    key_up_down = menu_1_7_n;
    key_break = menu_1_init;
    menu_i = 7;
	menu_shudu = 20 ;       //50ms 的定时、 10就对应500ms  20对应1s	
}

void menu_1_1_n(uchar num)	 //调时
{
	menu_1_1_shudu();
    if(num == 1)
    {
    	shi+=0x01;
		if((shi & 0x0f) >= 0x0a)
			shi = (shi & 0xf0) + 0x10;
		if(shi >= 0x24)
			shi = 0;
    }
    else
    {
		if(shi == 0x00)
			shi = 0x24;
		if((shi & 0x0f) == 0x00)
			shi = (shi | 0x0a) - 0x10;
		shi -- ; 
    }  
	write_sfm2_ds1302(1,2,shi);
	write_com(0x80+2);  //将光标移动到秒个位
	write_com(0x0f);    //显示光标并且闪烁
	write_time();
}

void menu_1_2_n(uchar num)	 //调分
{
	menu_1_1_shudu();
    if(num == 1)
    {
    	fen+=0x01;
		if((fen & 0x0f) >= 0x0a)
			fen = (fen & 0xf0) + 0x10;
		if(fen >= 0x60)
			fen = 0;
    }
    else
    {
		if(fen == 0x00)
			fen = 0x5a;
		if((fen & 0x0f) == 0x00)
			fen = (fen | 0x0a) - 0x10;
		fen -- ;
    }  
	write_sfm2_ds1302(1,5,fen);
	write_com(0x80+5);  //将光标移动到秒个位
	write_com(0x0f);    //显示光标并且闪烁
	write_time();
}

void menu_1_3_n(uchar num)	  //调秒
{
	menu_1_1_shudu();
    if(num == 1)
    {
    	miao+=0x01;
		if((miao & 0x0f) >= 0x0a)
			miao = (miao & 0xf0) + 0x10;
		if(miao >= 0x60)
			miao = 0;
    }
    else
    {
		if(miao == 0x00)
			miao = 0x5a;
		if((miao & 0x0f) == 0x00)
			miao = (miao | 0x0a) - 0x10;
		miao -- ;
    }  
	write_sfm2_ds1302(1,8,miao);
	write_com(0x80+8);  //将光标移动到秒个位
	write_com(0x0f);    //显示光标并且闪烁
	write_time();
}

void menu_1_4_n(uchar num)	  //调星期
{
	menu_1_1_shudu();
    if(num == 1)
    {
    	week+=0x01;
			if((week & 0x0f) >= 0x0a)
				week = (week & 0xf0) + 0x10;
			if(week >= 0x08)
				week = 1;
    }
    else
    {
		if(week == 0x01)
				week = 0x08;
			if((week & 0x0f) == 0x00)
				week = (week | 0x0a) - 0x10;
			week -- ;
    }  
	write_sfm1(1,14,week);
	write_com(0x80+14);  //将光标移动
	write_com(0x0f);    //显示光标并且闪烁
	write_time();
}

void menu_1_5_n(uchar num)	 //调年
{
	menu_1_1_shudu();
    if(num == 1)
    {
    	nian+=0x01;
		if((nian & 0x0f) >= 0x0a)
			nian = (nian & 0xf0) + 0x10;
		if(nian >= 0x9a)
			nian = 1;
    }
    else
    {
		if(nian == 0x01)
			nian = 0x9a;
		if((nian & 0x0f) == 0x00)
			nian = (nian | 0x0a) - 0x10;
		nian -- ;
    }  
	write_sfm2_ds1302(2,3,nian);
	write_com(0x80+0x40+3);  //将光标移动到秒个位
	write_com(0x0f);    //显示光标并且闪烁
	write_time();
}

void menu_1_6_n(uchar num)	   //调月
{
	menu_1_1_shudu();
    if(num == 1)
    {
    	yue+=0x01;
		if((yue & 0x0f) >= 0x0a)
			yue = (yue & 0xf0) + 0x10;
		if(yue >= 0x13)
			yue = 1;
    }
    else
    {
		if(yue == 0x01)
			yue = 0x13;
		if((yue & 0x0f) == 0x00)
			yue = (yue | 0x0a) - 0x10;
		yue -- ;
    }  
	write_sfm2_ds1302(2,6,yue);
	write_com(0x80+0x40+6);  //将光标移动到秒个位
	write_com(0x0f);    //显示光标并且闪烁
	write_time();
}

void menu_1_7_n(uchar num)	   //调日
{
	menu_1_1_shudu();
    if(num == 1)
    {
    	ri+=0x01;
		if((ri & 0x0f) >= 0x0a)
			ri = (ri & 0xf0) + 0x10;
		if(ri >= 0x32)
			ri = 0;
    }
    else
    {
		if(ri == 0x01)
			ri = 0x32;
		if((ri & 0x0f) == 0x00)
			ri = (ri | 0x0a) - 0x10;
		ri -- ;
    }  
	write_sfm2_ds1302(2,9,ri);
	write_com(0x80+0x40+9);  //将光标移动到秒个位
	write_com(0x0f);    //显示光标并且闪烁
	write_time();
}

void menu_1_1_fun()
{    
	switch(menu_i)
    {
        case 1:  menu_1_1_init();  break;
        case 2:  menu_1_2_init();  break;
        case 3:  menu_1_3_init();  break;
        case 4:  menu_1_4_init();  break;
        case 5:  menu_1_5_init();  break;
        case 6:  menu_1_6_init();  break;
        case 7:  menu_1_7_init();  break;
    } 
	menu_i ++;
    if(menu_i > 7)
        menu_i = 1;
}

/**************************_2_1——******************************/
void menu_2_1_dis()
{	
	write_string(1,0,"    wendu set    ");
	write_string(2,0,"                 ");
	write_sfm_18b20(2,7,t_high);	
}

void menu_2_1_init()	
{
    menu_2 = 1; menu_3 = 0; 
    menu_2_1_dis();
	write_com(0x80+0x40+7);  //将光标移动到秒个位
	write_com(0x0f);         //显示光标并且闪烁	
    key_up_down = menu_2_1_n;
    key_break = menu_2_init;
    menu_i = 1;
}


void menu_2_1_n(uchar num)	 //	设置高温度值
{
	menu_1_1_shudu();
    if(num == 1)		   	  //加高温
    {
		t_high ++ ;
		if(t_high > 99)
			t_high = 99;	
    }
    else					   //减高温
    {
		t_high -- ;
		if(t_high < 5)
			t_high = 5;
    }  
	 write_sfm_18b20(2,7,t_high);	//显示高温度
	write_com(0x80+0x40+7);  //将光标移动到秒个位
	write_com(0x0f);         //显示光标并且闪烁	
	write_eepom();		//保存数据
}

void menu_2_1_fun()
{
    switch(menu_2)
    {
        case 0:  menu_2_1_init();  break;
        case 1:  menu_2_1_init();  break;
    } 	
}

/**************_3_1_ 设置开关时间***********/
void menu_3_1_dis()
{	
	write_string(1,0,"guan 00:00      ");
    write_string(2,0," kai 00:00      ");	
}

void menu_3_1_init()		//开时
{
    menu_2 = 1; menu_3 = 0; 
    menu_3_1_dis();
	write_sfm2_ds1302(1,5,k_shi);	  //显示开时
	write_sfm2_ds1302(1,8,k_fen);	  //显示开分
	write_sfm2_ds1302(2,5,g_shi);	  //显示关时
	write_sfm2_ds1302(2,8,g_fen);	  //显示关分
    key_up_down = menu_3_1_n;
    key_break   = menu_3_init;
	write_com(0x80+5);  //将光标移动到秒个位
	write_com(0x0f);    //显示光标并且闪烁	
    menu_i = 1;
}

void menu_3_2_init()	    //开分
{
    menu_2 = 2; menu_3 = 0; 
	write_com(0x80+8);  //将光标移动到秒个位
	write_com(0x0f);    //显示光标并且闪烁	
    key_up_down = menu_3_2_n;
    key_break   = menu_3_init;
    menu_i = 2;
}

void menu_3_3_init()	   //关时
{
    menu_2 = 3; menu_3 = 0; 	
	write_com(0x80+0x40+5);     //将光标移动到秒个位
	write_com(0x0f);            //显示光标并且闪烁	
    key_up_down = menu_3_3_n;
    key_break   = menu_3_init;
    menu_i = 3;
}

void menu_3_4_init()	   //关分
{
    menu_2 = 4; menu_3 = 0; 	
	write_com(0x80+0X40+8);     //将光标移动到秒个位
	write_com(0x0f);            //显示光标并且闪烁	
    key_up_down = menu_3_4_n;
    key_break = menu_3_init;
    menu_i = 4;
}

void menu_3_1_n(uchar num)	 //开时
{
	menu_1_1_shudu();
    set_ds1302time(num,&k_shi,0x24)	;
	write_sfm2_ds1302(1,5,k_shi);	  //显示开时
	write_com(0x80+5);  //将光标移动到秒个位
	write_com(0x0f);    //显示光标并且闪烁
	write_eepom();            //保存设置
}

void menu_3_2_n(uchar num)	 //开分
{
	menu_1_1_shudu();
    set_ds1302time(num,&k_fen,0x60)	;
	write_sfm2_ds1302(1,8,k_fen);	  //显示开分
	write_com(0x80+8);  //将光标移动到秒个位
	write_com(0x0f);    //显示光标并且闪烁
	write_eepom();            //保存设置
}

void menu_3_3_n(uchar num)	  //关时
{
	menu_1_1_shudu();
    set_ds1302time(num,&g_shi,0x24)	;
	write_sfm2_ds1302(2,5,g_shi);	  //显示关时
	write_sfm2_ds1302(2,8,g_fen);	  //显示关分
	write_com(0x80+0x40+5);     //将光标移动到秒个位
	write_com(0x0f);    //显示光标并且闪烁
	write_eepom();            //保存设置
}

void menu_3_4_n(uchar num)	  //关分
{
	menu_1_1_shudu();
    set_ds1302time(num,&g_fen,0x60)	;
	write_sfm2_ds1302(2,8,g_fen);	  //显示关分
	write_com(0x80+0x40+8);   //将光标移动到秒个位
	write_com(0x0f);          //显示光标并且闪烁
	write_eepom();            //保存设置
}

void menu_3_1_fun()
{	
	menu_2 ++;
    if(menu_2 > 4)
        menu_2 = 1;
    switch(menu_2)
    {
        case 1:  menu_3_1_init();  break;
        case 2:  menu_3_2_init();  break;
        case 3:  menu_3_3_init();  break;
        case 4:  menu_3_4_init();  break;
    } 	
}

/**************_4_1_ 设置光线等级***********/
void menu_4_1_dis()
{	
	write_string(1,0,"  Set Guanxian  ");
    write_string(2,0,"                ");	
}

void menu_4_1_init()		//开时
{
    menu_2 = 1; menu_3 = 0; 
    menu_4_1_dis();
    key_up_down = menu_4_1_n;
    key_break   = menu_4_init;
	write_sfm1(2,7,guanxian_set);	//显示光线等级度
	write_com(0x0c);    //关光标	
    menu_i = 1;
}

void menu_4_1_n(uchar num)	 //	设置光线
{
	menu_1_1_shudu();
    if(num == 1)		   	  //加光线等级
    {
		guanxian_set ++ ;
		if(guanxian_set > 9)
			guanxian_set = 9;	
    }
    else					   //减光线等级
    {
		if(guanxian_set < 1)
			guanxian_set = 1;
		guanxian_set -- ;
    }  
	write_sfm1(2,7,guanxian_set);	//显示光线等级度
	write_eepom();		//保存数据
}

void menu_4_1_fun()
{
    switch(menu_2)
    {
        case 0:  menu_4_1_init();  break;
        case 1:  menu_4_1_init();  break;
    } 	
}


#endif