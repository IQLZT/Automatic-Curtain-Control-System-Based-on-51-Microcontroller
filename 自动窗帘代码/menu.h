#ifndef _MENU_H_
#define _MENU_H_

#include "menu_value.h"
#include "menu_1.h"

void key_exit()
{
    (*key_break)();		// 退出键
}

void key_up()
{
    (*key_up_down)(2);  // 向上键

}

void key_down()
{
    (*key_up_down)(1);  // 向下键
}

void key_sure_1()	    // 确定键
{
 	 menu_1_fun();
}

void key_with()
{

	switch(key_can)
	{
		case 1:  key_sure_1();   // 确定键
			 	 break;
		case 4:  key_exit();  	 // 退出键
			 	 break;
		case 3:  key_up();    	 // 向上键
			 	 break;
		case 2:  key_down();  	 // 向下键
			 	 break;			
		default: break;	
	}
	if(menu_1 == 0)
	if(key_can == 5)	//设置手动还是自动模式
	{
		flag_zd_sd = ~flag_zd_sd;
		if(flag_zd_sd == 0)		   //手动
			write_string(1,0," sd");  
		if(flag_zd_sd == 1)		   //自动
			write_string(1,0," zd");  
		write_eepom();    		   //保存
		flag_kaig_moshi = 0;
	}							
}



#endif