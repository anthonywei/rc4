#include <stdio.h>
#include <string.h>
//#include "base64.h"

typedef unsigned long ULONG;

void rc4_init(unsigned char *s, unsigned char *key, unsigned long Len) //初始化函数
{
    int i =0, j = 0;
    char k[256] = {0};
    unsigned char tmp = 0;
    for (i=0;i<256;i++) {
        s[i] = i;
        k[i] = key[i%Len];
    }
    for (i=0; i<256; i++) {
        j=(j+s[i]+k[i])%256;
        tmp = s[i];
        s[i] = s[j]; //交换s[i]和s[j]
        s[j] = tmp;
    }
 }

void rc4_crypt(unsigned char *s, unsigned char *Data, unsigned long Len) //加解密
{
    int i = 0, j = 0, t = 0;
    unsigned long k = 0;
    unsigned char tmp;
    for(k=0;k<Len;k++) {
        i=(i+1)%256;
        j=(j+s[i])%256;
        tmp = s[i];
        s[i] = s[j]; //交换s[x]和s[y]
        s[j] = tmp;
        t=(s[i]+s[j])%256;
        Data[k] ^= s[t];
     }
} 

int main()
{ 
    unsigned char s[256] = {0}; //S-box
    char key[256] = {"12345678"};
    char pData[512] = "梯子网@91waijiao";
    ULONG len = strlen(pData);
    printf("key : %s\n", key);
    printf("raw : %s\n", pData);
    
    rc4_init(s,(unsigned char *)key,strlen(key)); //已经完成了初始化
    /*
    int i;
    for (i=0; i<256; i++)
    {
        printf("%-3d ",s[i]);
    }
    printf("\n");
    */
    rc4_crypt(s,(unsigned char *)pData,len);//加密
    printf("encrypt  : %s\n", pData);
    printf("encrypt64: %s\n", base64_encode(pData, len));
    rc4_init(s,(unsigned char *)key, strlen(key)); //初始化密钥
    rc4_crypt(s,(unsigned char *)pData,len);//解密
    printf("decrypt  : %s\n",pData);
    return 0;
}
