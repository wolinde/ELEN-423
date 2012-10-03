#include <stdio.h>
#include "xparameters.h"
#include "xil_cache.h"
#include "xbasic_types.h"
#include "xgpio.h"
#include "gpio_header.h"

#define LED_DATA *(volatile int *)(XPAR_LEDS_8BIT_BASEADDR)
#define LED_DATA_DIRECTION *(volatile int *)(XPAR_LEDS_8BIT_BASEADDR + 4)
#define SWITCH_INPUT *(volatile int *)(XPAR_SWITCHES_8BIT_BASEADDR)
#define SWITCH_DATA_DIRECTION *(volatile int *)(XPAR_SWITCHES_8BIT_BASEADDR + 4)
#define PUSH_DATA *(volatile int *)(XPAR_PUSH_BUTTONS_3BIT_BASEADDR)
#define PUSH_DATA_DIRECTION *(volatile int *)(XPAR_PUSH_BUTTONS_3BIT_BASEADDR + 4)

int AddMoney();
int Debounce();
int wait(u32 wait_count);

// to read... switch_input = SWITCH_DATA
// to write switches to leds...LED_DATA=switch_input

int main()
{
	  SWITCH_DATA_DIRECTION = 0x00;
	  PUSH_DATA_DIRECTION = 0x00;
	  LED_DATA_DIRECTION = 0xFF;

	  Xil_ICacheEnable();
	  Xil_DCacheEnable();

	  u32 buttons;
	  u32 switches;
	  u32 cost;
	  u32 change;
	  int state;
	  state = 0;
	  int totmoneyin;
	  int add;

	  totmoneyin = 0;

   while(1){

	   if(state==0){
		   print("--------Please Insert Money-------- \r");
		   wait(0x1F);
		   buttons = PUSH_DATA;
		   if (buttons==4){
			   add = AddMoney();
			   totmoneyin=totmoneyin+add;
			   xil_printf("\nTotal money in is $ %d\r\n",totmoneyin);//more of these
			   add = 0;
			   state = 1;
			   wait(0xFF);
			   buttons = Debounce();
		   }
	   }
	   else if(state == 1){
		   buttons = PUSH_DATA;
		   if (buttons==4){
			   add = AddMoney();
			   totmoneyin = totmoneyin + add;
			   xil_printf("\nTotal money in is $ %d \r\n", totmoneyin);//more of these
			   add = 0;
			   buttons = Debounce();
		   }
		   switches = SWITCH_INPUT;
		   buttons = PUSH_DATA;
		   cost = switches&0xFFFFFFFC;
		   cost>>=2;
		   cost=cost*25;
		   xil_printf("Cost is $ %d \r", cost);
		   if (totmoneyin>=cost){
			   state = 2;
			   print("\nPlease Make a Selection \n\r");
			   wait(0xFF);
		   }
		   else if(buttons==2){
			   state = 0;
			   totmoneyin=0;
			   print("\nMoney Returned \r\n");
			   wait(0xFF);
			   buttons = Debounce();
		   }
	   }
	   else if(state == 2){
		   buttons = PUSH_DATA;
		   switches = SWITCH_INPUT;
		   cost = switches&0xFFFFFFFC;
		   cost>>=2;
		   cost=cost*25;
		   xil_printf("Cost is $ %d \r", cost);
		   if (buttons==4){
			   add = AddMoney();
			   totmoneyin = totmoneyin + add;
			   xil_printf("\nTotal money in is $ %d \r\n", totmoneyin);
			   add = 0;
			   buttons = Debounce();
		   }
		   else if ((buttons==1)&&(cost<=totmoneyin)) {
			   print("Good Choice. Vending... \r\n");
			   wait(0x3FF);
			   state = 3;
			   buttons = Debounce();
		   }
		   else if(cost>totmoneyin){
			   print("Woops! The price went up, give me more money.\r\n");
			   state = 1;
		   }
		   else if(buttons==2){
			   state = 0;
			   totmoneyin=0;
			   print("\nMoney Returned \r\n");
			   wait(0x2FF);
			   buttons = Debounce();
		   }
		   else {
			   state = 2;
		   }
	   }
	   else if(state == 3){
		   print ("Vending Complete. Enjoy! \n\r");
		   totmoneyin=totmoneyin-cost;
		   wait(0x2FF);
		   state = 4;
	   }
	   else if(state == 4){
		   change = totmoneyin;
		   xil_printf("Your Change is $ %d \n\rHave a Nice Day!!\r\n",change);
		   wait(0x2FF);
		   totmoneyin = 0;
		   state = 0;
	   }
   }

   Xil_DCacheDisable();
   Xil_ICacheDisable();

   return 0;
}

//*****************//subroutines//********************//

int AddMoney(){
    int moneyin;
  	int add;
  	u32 money;
  	u32 switches;

  	switches = SWITCH_INPUT;
	moneyin = switches&0x00000003;
	if (moneyin==0x00000000){
		add = 0x00000019;
	}
	else if (moneyin==0x00000001){
		add = 0x00000064;
	}
	else if (moneyin==0x00000002){
		add = 0x000001F4;
	}
	else if (moneyin==0x00000003){
		add = 0x000003E8;
	}
	money = 0;
	return add;
 }

int Debounce() {
	u32 buttons;
	buttons = PUSH_DATA;;
	while (buttons>0) {
		buttons = PUSH_DATA;
	}
   return buttons;
}

int wait(u32 wait_count) {
	u32 i;
	u32 l;
	for(i=0; i<=wait_count; i++){
		for(l=0;l<=0xFFF;l++){
		}
	}
	return i;
}
=======
#include <stdio.h>
#include "xparameters.h"
#include "xil_cache.h"
#include "xbasic_types.h"
#include "xgpio.h"
#include "gpio_header.h"

#define LED_DATA *(volatile int *)(XPAR_LEDS_8BIT_BASEADDR)
#define LED_DATA_DIRECTION *(volatile int *)(XPAR_LEDS_8BIT_BASEADDR + 4)
#define SWITCH_INPUT *(volatile int *)(XPAR_SWITCHES_8BIT_BASEADDR)
#define SWITCH_DATA_DIRECTION *(volatile int *)(XPAR_SWITCHES_8BIT_BASEADDR + 4)
#define PUSH_DATA *(volatile int *)(XPAR_PUSH_BUTTONS_3BIT_BASEADDR)
#define PUSH_DATA_DIRECTION *(volatile int *)(XPAR_PUSH_BUTTONS_3BIT_BASEADDR + 4)

int AddMoney();
int Debounce();
int wait(u32 wait_count);

// to read... switch_input = SWITCH_DATA
// to write switches to leds...LED_DATA=switch_input

int main()
{
	  SWITCH_DATA_DIRECTION = 0x00;
	  PUSH_DATA_DIRECTION = 0x00;
	  LED_DATA_DIRECTION = 0xFF;

	  Xil_ICacheEnable();
	  Xil_DCacheEnable();

	  u32 buttons;
	  u32 switches;
	  u32 cost;
	  u32 change;
	  int state;
	  state = 0;
	  int totmoneyin;
	  int add;

	  totmoneyin = 0;

   while(1){

	   if(state==0){
		   print("--------Please Insert Money-------- \r");
		   wait(0x1F);
		   buttons = PUSH_DATA;
		   if (buttons==4){
			   add = AddMoney();
			   totmoneyin=totmoneyin+add;
			   xil_printf("\nTotal money in is $ %d\r\n",totmoneyin);//more of these
			   add = 0;
			   state = 1;
			   wait(0xFF);
			   buttons = Debounce();
		   }
	   }
	   else if(state == 1){
		   buttons = PUSH_DATA;
		   if (buttons==4){
			   add = AddMoney();
			   totmoneyin = totmoneyin + add;
			   xil_printf("\nTotal money in is $ %d \r\n", totmoneyin);//more of these
			   add = 0;
			   buttons = Debounce();
		   }
		   switches = SWITCH_INPUT;
		   buttons = PUSH_DATA;
		   cost = switches&0xFFFFFFFC;
		   cost>>=2;
		   cost=cost*25;
		   xil_printf("Cost is $ %d \r", cost);
		   if (totmoneyin>=cost){
			   state = 2;
			   print("\nPlease Make a Selection \n\r");
			   wait(0xFF);
		   }
		   else if(buttons==2){
			   state = 0;
			   totmoneyin=0;
			   print("\nMoney Returned \r\n");
			   wait(0xFF);
			   buttons = Debounce();
		   }
	   }
	   else if(state == 2){
		   buttons = PUSH_DATA;
		   switches = SWITCH_INPUT;
		   cost = switches&0xFFFFFFFC;
		   cost>>=2;
		   cost=cost*25;
		   xil_printf("Cost is $ %d \r", cost);
		   if (buttons==4){
			   add = AddMoney();
			   totmoneyin = totmoneyin + add;
			   xil_printf("\nTotal money in is $ %d \r\n", totmoneyin);
			   add = 0;
			   buttons = Debounce();
		   }
		   else if ((buttons==1)&&(cost<=totmoneyin)) {
			   print("Good Choice. Vending... \r\n");
			   wait(0x3FF);
			   state = 3;
			   buttons = Debounce();
		   }
		   else if(cost>totmoneyin){
			   print("Woops! The price went up, give me more money.\r\n");
			   state = 1;
		   }
		   else if(buttons==2){
			   state = 0;
			   totmoneyin=0;
			   print("\nMoney Returned \r\n");
			   wait(0x2FF);
			   buttons = Debounce();
		   }
		   else {
			   state = 2;
		   }
	   }
	   else if(state == 3){
		   print ("Vending Complete. Enjoy! \n\r");
		   totmoneyin=totmoneyin-cost;
		   wait(0x2FF);
		   state = 4;
	   }
	   else if(state == 4){
		   change = totmoneyin;
		   xil_printf("Your Change is $ %d \n\rHave a Nice Day!!\r\n",change);
		   wait(0x2FF);
		   totmoneyin = 0;
		   state = 0;
	   }
   }

<<<<<<< HEAD
print ("Anna was here :D ");

=======
>>>>>>> ef42f63023c2f79444b63afbb53cc4d6b22bb1ff
   Xil_DCacheDisable();
   Xil_ICacheDisable();

   return 0;
}

//*****************//subroutines//********************//

int AddMoney(){
    int moneyin;
  	int add;
  	u32 money;
  	u32 switches;

  	switches = SWITCH_INPUT;
	moneyin = switches&0x00000003;
	if (moneyin==0x00000000){
		add = 0x00000019;
	}
	else if (moneyin==0x00000001){
		add = 0x00000064;
	}
	else if (moneyin==0x00000002){
		add = 0x000001F4;
	}
	else if (moneyin==0x00000003){
		add = 0x000003E8;
	}
	money = 0;
	return add;
 }

int Debounce() {
	u32 buttons;
	buttons = PUSH_DATA;;
	while (buttons>0) {
		buttons = PUSH_DATA;
	}
   return buttons;
}

int wait(u32 wait_count) {
	u32 i;
	u32 l;
	for(i=0; i<=wait_count; i++){
		for(l=0;l<=0xFFF;l++){
		}
	}
	return i;
}
