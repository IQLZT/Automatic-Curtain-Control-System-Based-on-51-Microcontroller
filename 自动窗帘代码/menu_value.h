#ifndef _MENU_VALUE_H_
#define _MENU_VALUE_H_
#define uchar unsigned char
#define uint unsigned int


/****************菜单变量的定义*******************/

uchar menu_1;	   //第1级菜单变量
uchar menu_2;	   //第2级菜单变量
uchar menu_3;	   //第3级菜单变量
uchar menu_4;	   //第4级菜单变量
uchar menu_5;	   //第5级菜单变量
uchar menu_i;	   //做上下键的变量

void (*key_up_down)(uchar n);	  //定义上下键指针函数
void (*key_shuzi)(uchar n);		  //定义数字键指针函数
void (*key_break)(void);		  //定义退出键指针函数


/***********************延时函数************************/
//void delay_uchar(uchar q)
//{
//	while(q--);
//}


/***********************空函数************************/
void null()
{

}

/***********************带形参的空函数************************/
void null_1(uchar num)
{
	num = num;
}

#endif