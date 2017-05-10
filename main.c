#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <openssl/sha.h>

int main(int argc, char** argv) {
    int i; //for loop index
    int length; //length of string to hash./
    unsigned char buffer[1024] = {0};
    char userid[16] = {0};
    char targetuid[] = "user1\n";
    char pw1[16] = {0}; //password entered by user
    char hash1[33] = {0}; //SHA256 hash of pw1 in bytes (32 bytes)
    char hash1hex[64]={0}; //hash1[] as a 64 long hex string
    //pw1: abcdefghi
    char target1[] = "19cc02f26df43cc571bc9ed7b0c4d29224a3ec229529221725ef76d021c8326f";
    char hash2[33] = {0};
    char hash2hex[64] = {0};
    //pw2: abcd
    char target2[] = "88d4266fd4e6338d13b845fcf289579d209c897823b9217da3e161936f031589";
    char hash3[33] = {0};
    char hash3hex[64] = {0};
    //pw3: abc
    char target3[] = "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad";    
    char pw2[16] = {0};
    char pw3[16] = {0};
    char* hash_ptr;

    printf("userid: ");
    fgets(buffer, 1024, stdin);
    printf("buffer: ");
    for (i=0; i < 32; i++)
       printf("%02hhx", buffer[i]);
    printf("\n");  
    strcpy(userid,buffer);
       
    printf("password1: ");
    fgets(buffer, 1024, stdin);
    printf("buffer: ");
    for (i=0; i < 32; i++)
       printf("%02hhx", buffer[i]);
    printf("\n");  
    strcpy(pw1,buffer);
   i=123;
   printf("i addr: %p\n",(void *) &i);
   printf("i contents: %08x\n", i);
   long *ptr= (long *) buffer;
   for (i=0; i<8; i++){
     printf("address %p is %08x\n", 
                (void *) (ptr+i), 
                (unsigned int) (*(ptr+i)));
   }    
    printf("password2: ");
    fgets(buffer, 1024, stdin);
    printf("buffer: ");
    for (i=0; i < 32; i++)
       printf("%02hhx", buffer[i]);
    printf("\n");  
    strcpy(pw2,buffer);    

    printf("password3: ");
    fgets(buffer, 1024, stdin);
    printf("buffer: ");
    for (i=0; i < 32; i++)
       printf("%02hhx", buffer[i]);
    printf("\n");  
    strcpy(pw3,buffer);
    
    length = strlen(pw1)-1;
    if (length>16)
        length=16;
    SHA256(pw1, length, hash1);
    i = 0;
   printf("pw1: ");
   for (i=0; i < 16; i++)
       printf("%02hhx", pw1[i]);
   printf("\n"); 
   printf("hash1: ");
   for (i=0; i < 32; i++)
       printf("%02hhx", hash1[i]);
   printf("\n");    
    hash_ptr = hash1hex;
    for (i=0; i < 32; i++){
        hash_ptr += sprintf(hash_ptr,"%02hhx", hash1[i]);
    }
    hash1hex[64]=0;
    printf("target1: %s\n", target1);
    printf("hash1hex:  %s\n",hash1hex);
    
    length = strlen(pw2)-1;
    if (length>16)
        length=16;
    SHA256(pw2, length, hash2);
    i = 0;
    printf("hash2: ");
    for (i=0; i < 32; i++)
        printf("%02hhx", hash2[i]);
    printf("\n");    
    hash_ptr = hash2hex;
    for (i=0; i < 32; i++){
        hash_ptr += sprintf(hash_ptr,"%02hhx", hash2[i]);
    }
    hash2hex[64]=0;
    
    length = strlen(pw3)-1;
    if (length>16)
        length=16;    
    SHA256(pw3, length, hash3);
    i = 0;
   printf("hash3: ");
   for (i=0; i < 32; i++)
        printf("%02hhx", hash3[i]);
    printf("\n");    
    hash_ptr = hash3hex;
    for (i=0; i < 32; i++){
        hash_ptr += sprintf(hash_ptr,"%02hhx", hash3[i]);
    }
    hash3hex[64]=0;
 
    if (strncmp(userid, targetuid,16)==0 &&
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
