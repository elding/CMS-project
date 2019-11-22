#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "menu.h"
#include "message.h"
#include "Queues.h"
#include "sound.h"
#include <Windows.h>  // Includes the functions for serial communication via RS232
#include <stdlib.h>

int main(void){
	int exitCon = 1;
	
	while (exitCon == 1) {

		exitCon = MainMenu();
	}

	return 0;
	}

