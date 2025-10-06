#include "barestring.h"


char* inttostr(int value){
    static char buffer[128];
    char* ptr = &buffer[127];
    *ptr = '\0';
    
    unsigned int num = (value < 0) ? (unsigned int)(-value) : (unsigned int)value;
    
    
    do {
        ptr--;
        *ptr = '0' + (num % 10);
        num /= 10;
    } while (num > 0);
    
    
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

void strreplace(char* str, int index, char repl) {
    str[index] = repl;
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

int strcmp(char* strA, char* strB){
    int szA = strsize(strA);
    int szB = strsize(strB);
    if (szA != szB){
        return 0;
    }
    for (int i = 0; i<szA; i++){
        if (strA[i] != strB[i]){
            return 0;
        }
    }
    return 1;
}

char* substr(char* str, int startindex, int endindex) {
    static char output[256] = {0};

    if (startindex < 0 || startindex >= endindex || endindex > 255) {
        output[0] = '\0';
        return output;
    }

    int i; 
    int j = 0; 

    for(i = startindex; i < endindex; i++) {
        if (str[i] == '\0') {
            break;
        }
        output[j] = str[i]; 
        j++;
    }
    output[j] = '\0'; 
    return output;
}

int strfindsub(char* str, int startindex, char* occurence){
    int j = 0;
    int i;
    int drop = 0;
    int strsz = strsize(str);
    int ocsz = strsize(occurence);
    
    if (ocsz > strsz || startindex >= strsz || startindex < 0){
        return -1;
    }
    
    for (i = startindex; i < strsz; i++){
        if (occurence[j] == str[i]){
            if (drop == 0) {
                drop = i;
            }
            j++;
            
            if (j == ocsz){
                return drop;
            }
        }
        else {
            if (drop > 0) {
                i = drop;
            }
            drop = 0;
            j = 0;
        }
    }
    return -1;
}