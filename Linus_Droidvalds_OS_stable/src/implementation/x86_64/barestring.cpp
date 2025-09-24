#include "barestring.h"


char* inttostr(int value){
    static char buffer[128];
    char* ptr = &buffer[127];
    *ptr = '\0';
    
    unsigned int num = (value < 0) ? (unsigned int)(-value) : (unsigned int)value;
    
    // Convert digits in reverse order
    do {
        ptr--;
        *ptr = '0' + (num % 10);
        num /= 10;
    } while (num > 0);
    
    // Add sign if negative
    if (value < 0) {
        ptr--;
        *ptr = '-';
    }
    
    return ptr;
}

size_t strsize(char* str){
    int total = 0;
    while(str[total] != '\0'){
        total++;
    }
    return total;
}


int strfind(char* str, char firstappearance){
    int sz = strsize(str);
    for (int i = 0; i < sz; i++){
        if (str[i] == firstappearance){
            return i;
        }
    }
    return -1;
}