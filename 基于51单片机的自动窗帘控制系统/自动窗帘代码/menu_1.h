#ifndef _MENU_1_H_
#define _MENU_1_H_
#include "lcd1602.h"
#include "menu_value.h"
#include "menu_2.h"

void menu_1_n(uchar num);

void menu_1_break()			  //第一级菜单退出函数
{
	menu_1 = 0;  
	menu_2 = 0;  
	menu_3 = 0;  
	clear_1602();			 //清除LCD1602显示
	init_1602();
	init_1602_dis_csf();	 //初始化LCD1602显示
	key_break = null;		 //给退出键赋空函数
	key_up_down = null_1;	 //给上下键赋空函数
	key_shuzi = null_1;	 //给数字键赋空函数
}

void menu_1_dis()
{
    write_string(1,0,"1.set-time      ");	   
	write_string(2,0,"2.set-wendu     "); 
}

void menu_2_dis()
{	
	write_string(1,0,"3.set-dingshi kg"); 
    write_string(2,0,"4.set-guanxian");	   	
}

void menu_1_init()		 //第一级菜单第一项
{
    menu_1 = 1; menu_2 = 0; 	//menu._1 = 1;  说明菜单到了第一级第一项
    menu_1_dis();
	write_com(0x80+0);              //将光标移动到秒个位
	write_com(0x0f);                //显示光标并且闪烁	
    key_up_down = menu_1_n;		    //上下键指针函数赋值
    key_break = menu_1_break;	    //退出键指针函数赋值
    menu_i = 1;	
	menu_shudu = 20 ;       //50ms 的定时、 10就对应500ms  20对应1s				
}

void menu_2_init()		  //第一级菜单第2项
{
    menu_1 = 2; menu_2 = 0;			//menu._1 = 2;  说明菜单到了第一级第2项
	menu_1_dis();
	write_com(0x80+0x40);           //将光标移动到秒个位
	write_com(0x0f); 				//显示光标并且闪烁	
    key_up_down = menu_1_n;			//上下键指针函数赋值
    key_break = menu_1_break;		//退出键指针函数赋值
    menu_i = 2;
	menu_shudu = 20 ;       //50ms 的定时、 10就对应500ms  20对应1s	
}

void menu_3_init()		  //第一级菜单第3项
{
    menu_1 = 3; menu_2 = 0;			//menu._1 = 3;  说明菜单到了第一级第3项
	menu_2_dis();
	write_com(0x80);           //将光标移动到秒个位
	write_com(0x0f); 				//显示光标并且闪烁	
    key_up_down = menu_1_n;			//上下键指针函数赋值
    key_break = menu_1_break;		//退出键指针函数赋值
    menu_i = 3;
	menu_shudu = 20 ;       //50ms 的定时、 10就对应500ms  20对应1s	
} 

void menu_4_init()		  //第一级菜单第4项
{
    menu_1 = 4; menu_2 = 0;			//menu._1 = 4;  说明菜单到了第一级第3项
	menu_2_dis();
	write_com(0x80+0x40);           //将光标移动到秒个位
	write_com(0x0f); 				//显示光标并且闪烁	
    key_up_down = menu_1_n;			//上下键指针函数赋值
    key_break = menu_1_break;		//退出键指针函数赋值
    menu_i = 4;
	menu_shudu = 20 ;               //50ms 的定时、 10就对应500ms  20对应1s	
}

void menu_1_n(uchar num)		    //上下键的原函数
{
    if(num == 1)				   //如果形参为1 则代表是向下键
    {
        menu_i ++;
        if(menu_i > 4)
            menu_i = 1;
    }
    else						  //只要形参不为1 则代表是向上键
    {
         menu_i -- ;
         if(menu_i < 1)
            menu_i = 4;
    }
    switch(menu_i)
    {
        case 1:  menu_1_init();  break;		   //3个初始化显示函数调用
        case 2:  menu_2_init();  break;
        case 3:  menu_3_init();  break;
        case 4:  menu_4_init();  break;
    }
}

/***************************第一级菜单的功能函数****************************/
void menu_1_fun()			  
{
    switch(menu_1)
    {
        case 0:
             menu_1_init();
             break;
        case 1:
			 menu_1_1_fun();
             break;
        case 2:
			 menu_2_1_fun();
             break;
		case 3:
			 menu_3_1_fun();
             break;      
		case 4:
			 menu_4_1_fun();
             break;      
    }
}

#endif