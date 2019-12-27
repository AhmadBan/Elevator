#include "main.h"
void assert_failed(uint8_t* file, uint32_t line){
	/* do something to control damages */
	while(1){
		
	}
	NVIC_SystemReset();
}