const char base[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/="; 
char* base64_encode(const char* data, int data_len); 
char *base64_decode(const char* data, int data_len); 
static char find_pos(char ch); 
