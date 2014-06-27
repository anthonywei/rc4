/*
 *  An implementation of the ARC4 algorithm
 *
 *  Copyright (C) 2001-2003  Christophe Devine
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

//#include "stdafx.h"
#include "rc4.h"
//#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

void rc4_setup( struct rc4_state *s, unsigned char *key,  int length )
{
    int i, j, k, *m, a;

    s->x = 0;
    s->y = 0;
    m = s->m;

    for( i = 0; i < 256; i++ )
    {
        m[i] = i;
     }

    j = k = 0;

    for( i = 0; i < 256; i++ )
    {
        a = m[i];
        j = (unsigned char) ( j + a + key[k] );
        m[i] = m[j]; m[j] = a;
        if( ++k >= length ) k = 0;
    }
} 

void rc4_crypt( struct rc4_state *s, unsigned char *data, int length )
{ 
    int i, x, y, *m, a, b;

    x = s->x;
    y = s->y;
    m = s->m;

    for( i = 0; i < length; i++ )
     {
        x = (unsigned char) ( x + 1 ); a = m[x];
        y = (unsigned char) ( y + a );
        m[x] = b = m[y];
        m[y] = a;
        data[i] ^= m[(unsigned char) ( a + b )];
    }

    s->x = x;
    s->y = y;
}

int main()
{
    char key[128] = {"12345678"};
    char data[512] = {"梯子网@91waijiao"};
    struct rc4_state *s;
    s=(struct rc4_state *) malloc (sizeof(struct rc4_state));
    
    printf("key : %s\n", key);
    printf("raw : %s\n", data);
    rc4_setup(s, (unsigned char *)key, strlen(key));  
    /*
    int i;
    for (i = 0; i < 256; i++) {
        printf("%d ", s->m[i]);
    }
    printf("\n");
    */
    rc4_setup(s, (unsigned char *)key, strlen(key));  
    rc4_crypt(s, (unsigned char *)data, strlen(data));
    printf("encrypt  : %s\n",data);
    
    rc4_setup(s, (unsigned char *)key, strlen(key));  
    rc4_crypt(s, (unsigned char *)data, strlen(data));
    printf("decrypt  : %s\n",data);
    //cout<<"HELLO"<<endl;
    return 0;
}
