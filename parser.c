#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mosquitto.h>
#include <time.h> 
#include "parser.h"

int my_parser(uint8_t *data, int data_length)
{
	int x;
        for( x = 0; x < data_length; x++ ){
            //printf( " 0x%02X (ASCII: %c)", data[ x ], data[ x ] );
            printf( " 0x%02X ", data[ x ] );
        }
        printf( "\n\n\n" );
}
