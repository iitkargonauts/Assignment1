#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 25250
#define SERVER_IP "172.18.0.2"



#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>

void tostring(char str[], int num)
{
    int i, rem, len = 0, n;
    n = num;
    while (n != 0)
    {
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++)
    {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';
}

  
int main(int argc, char const *argv[])
{
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
  
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
      
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
  
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    /*send(sock , hello , strlen(hello) , 0 );
    printf("Hello message sent\n");
    valread = read( sock , buffer, 1024);
    printf("%s\n",buffer );*/

    /*---- Read the message from the server into the buffer ----*/
  int dogs=0,cats=0,cars=0,trucks=0;
  printf("Enter number of dogs:" );
  scanf("%d",&dogs);
  printf("\nEnter number of cats:" );
  scanf("%d",&cats);
  printf("\nEnter number of cars:" );
  scanf("%d",&cars);
  printf("\nEnter number of trucks:" );
  scanf("%d",&trucks);
  printf("\n");
  tostring(buffer,dogs);
  send(sock,buffer,1024,0);
  tostring(buffer,cats);
  send(sock,buffer,1024,0);
  tostring(buffer,cars);
  send(sock,buffer,1024,0);
  tostring(buffer,trucks);
  send(sock,buffer,1024,0);


  for(int i=1;i<=dogs+cats+cars+trucks;i++){
    int size;
    recv(sock, buffer, 1024, 0);
    size=atoi(buffer);
    // printf("Picture Size=%d\n",size);
    char recv_buffer=(char)(malloc(size*sizeof(char)));
    // printf("Reading Picture Byte Array\n");
    // printf("Converting Byte Array to Picture\n");
    FILE *image;
    char name[20];
    tostring(name,i);
    char jp[]=".jpg";
    strcat(name,jp);
    image = fopen(name, "w");
    //recv(sock, recv_buffer, size, 0);
    read(sock, recv_buffer, size);
    // printf("Size of recv_buffer = %ld\n",sizeof(recv_buffer) );
    fwrite(recv_buffer,  1,size, image);
    fclose(image);
  }

  char com[50]="./web.sh ";
  char n_images[50];
  tostring(n_images,dogs+cats+cars+trucks);
  strcat(com,n_images);
  char f[30]=" > index.html";
  strcat(com,f);
  system(com);
	




    return 0;
}
