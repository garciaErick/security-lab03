#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <openssl/sha.h>

int main(int argc, char** argv) {
    int i; //for loop index
    void * p;
    int length; //length of string to hash./
    unsigned char buffer[1024] = {0};
    char userid[16] = {0};
    char targetuid[] = "user1\n";
    char pw1[16] = {0}; //password entered by user
    short v1=1121;
    char hash3[33] = {0};
    short v2=1211;
    char pw2[16] = {0};
    char target1[] = "aacf8828b6d4eb5b1570ac8301ea85773a9ed48fedef528a1dabdf9aee5838c4";
    char hash2[33] = {0};
    short v3=1112;
    char target2[] = "d28c9c86fcfccb6453a0cd966817e7d82d206fb326a0c831f582baa9f646d40c";
    char hash1hex[64]={0}; 
    char hash2hex[64] = {0};
    char hash1[33] = {0}; 
    char target3[] = "8456e8d08d45240339b944195f5c4cc9363a473c25cd6bf4728b938225969262";
    char hash3hex[64] = {0};
    char pw3[16] = {0};
    char* hash_ptr;

    printf("pw1 address: %p\n",(void *) &pw1);
    printf("\n");
    printf("hash3hex address: %p\n",(void *) &hash3hex);
    printf("\n");
    printf("hash1hex address: %p\n",(void *) &hash1hex);
    printf("\n");
    printf("hash2hex address: %p\n",(void *) &hash2hex);
    printf("\n");
    printf("target2 address: %p\n",(void *) &target2);
    printf("\n");
    printf("hash3 address: %p\n",(void *) &hash3);
    printf("\n");
    printf("v3 address: %p\n",(void *) &v3);
    printf("\n");
    printf("v2 address: %p\n",(void *) &v2);
    printf("\n");
    printf("target1 address: %p\n",(void *) &target1);
    printf("\n");
    printf("target3 address: %p\n",(void *) &target3);
    printf("\n");
    printf("hash2 address: %p\n",(void *) &hash2);
    printf("\n");
    printf("pw2 address: %p\n",(void *) &pw2);
    printf("\n");
    printf("v1 address: %p\n",(void *) &v1);
    printf("\n");
    printf("hash1 address: %p\n",(void *) &hash1);
    printf("\n");
    printf("pw3 address: %p\n",(void *) &pw3);
    printf("\n");
    printf("v1: %x\n", v1);
    printf("v2: %x\n", v2);
    printf("v3: %x\n", v3);

    printf("userid: ");
    fgets(buffer, 1024, stdin);
    strcpy(userid,buffer);
       
    printf("password1: ");
    fgets(buffer, 1024, stdin);
    strcpy(pw1,buffer);

    printf("password2: ");
    fgets(buffer, 1024, stdin);  
    strcpy(pw2,buffer);    

    printf("password3: ");
    fgets(buffer, 1024, stdin); 
    strcpy(pw3,buffer);
    
    // force allocation of variables v1, v2 and v3
    p=(void *) &v1;
    p=(void *) &v2;
    p=(void *) &v3;
    
    length = strlen(pw1)-1;
    if (length>16)
        length=16;
    SHA256(pw1, length, hash1);
    i = 0;   
    hash_ptr = hash1hex;
    for (i=0; i < 32; i++){
        hash_ptr += sprintf(hash_ptr,"%02hhx", hash1[i]);
    }
    hash1hex[65]=0;
    
    length = strlen(pw2)-1;
    if (length>16)
        length=16;
    SHA256(pw2, length, hash2);
    i = 0; 
    hash_ptr = hash2hex;
    for (i=0; i < 32; i++){
        hash_ptr += sprintf(hash_ptr,"%02hhx", hash2[i]);
    }
    hash2hex[65]=0;
    
    length = strlen(pw3)-1;
    if (length>16)
        length=16;    
    SHA256(pw3, length, hash3);
    i = 0;    
    hash_ptr = hash3hex;
    for (i=0; i < 32; i++){
        hash_ptr += sprintf(hash_ptr,"%02hhx", hash3[i]);
    }
    hash3hex[65]=0;
 
    printf("v1: %x\n", v1);
    printf("v2: %x\n", v2);
    printf("v3: %x\n", v3);
    if (v1==1121){
        printf("v1 match");
        printf("\n");
    }
        else{printf("v1 did NOT match");
        printf("\n");}
        
    if (v2==1211){
        printf("v2 match");
        printf("\n");
    }
        else{printf("v2 did NOT match");
        printf("\n");}
        
    if (v3==1112){
        printf("v3 match");
        printf("\n");
    }
        else{printf("v3 did NOT match");
        printf("\n");}
        
    printf("target1: %s\n", target1);
    printf("target2: %s\n", target2);
    printf("target3: %s\n", target3);
    printf("hash1hex: %s\n", hash1hex);
    printf("password1: %s\n", pw1);
    printf("password2: %s\n", pw2);
    printf("password3: %s\n", pw3);
    if (strncmp(target1, hash1hex, 64) == 0) {
        printf("target1 matches\n");
    } else {
        printf("target1 doesn't match\n");
    }   
    
    if (strncmp(target2, hash2hex, 64) == 0) {
        printf("target2 matches\n");
    } else {
        printf("target2 doesn't match\n");
    }   
            
    if (strncmp(target3, hash3hex, 64) == 0) {
        printf("target3 matches\n");
    } else {
        printf("target3 doesn't match\n");
    }   

    if (v1==1121 && v2==1211 && v3==1112 &&
        strncmp(userid, targetuid,16)==0 &&
        strncmp(target1, hash1hex, 64)==0 &&
        strncmp(target2, hash2hex, 64)==0 &&
        strncmp(target3, hash3hex, 64)==0) {
        printf("starting shell\n");
        freopen("/dev/tty", "r", stdin);
        execve("/bin/sh", NULL, NULL);  
    }
    else
        printf("authentication failed.\n");
}
