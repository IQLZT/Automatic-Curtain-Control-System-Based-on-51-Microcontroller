/*************************************************
更多51单片机资料请关注微信公众号：电子应用学习馆
**************************************************
*****************《电子应用学习馆》***************
***************************************************/


#ifndef _BUJINDIANJI_H_
#define _BUJINDIANJI_H_

void write_eepom_shoudong();

uchar flag_z_f;        //正反标志位  0为顺时钟 1为逆时史上转
unsigned char code zheng[4]={0xf8,0xf4,0xf2,0xf1};//正转表格
unsigned char code fan[4]={0xf1,0xf2,0xf4,0xf8};//反转表格
uint bjdj_value;   //步进电机的量
uchar bjdj_zidong;   //步进电机的量	自动


void bujindj()	 //步进电机函数
{
	static uchar i;
	if(flag_z_f != 0)	
	{	
		if(flag_z_f == 1)	   //开
		{
			if(bjdj_value >= 254)
			{
				flag_z_f = 0;
				bjdj_value = 254;
				P2 = P2 & 0xf0;	//让4个IO口都不输出
				write_eepom();  //保存
			}else 
				bjdj_value ++;	
		}
		if(flag_z_f == 2)	   //关
		{				
			if(bjdj_value <= 1)
			{
				flag_z_f = 0;
				bjdj_value = 1;
				P2 = P2 & 0xf0;	//让4个IO口都不输出
				write_eepom();  //保存
			}else  
				bjdj_value --;
		}
		for(i=0;i<4;i++)          //4相
		{
			if(flag_z_f == 1)	  //开
				P2=zheng[i];// & (P2 | 0xf0);	       //
			else if(flag_z_f == 2)//关
				P2=fan[i];// & (P2 | 0xf0);	        //
			delay_uint(500);        //改变这个参数可以调整电机转速
		}
	}
}





#endif