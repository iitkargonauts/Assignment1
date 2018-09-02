#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 25250



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
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "Hello from server";
      
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
      
    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, 
                                 sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
                       (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    int dogs=0,cats=0,cars=0,trucks=0;
    valread = read( new_socket , buffer, 1024);
    dogs=atoi(buffer);
    valread = read( new_socket , buffer, 1024);
    cats=atoi(buffer);
    valread = read( new_socket , buffer, 1024);
    cars=atoi(buffer);
    valread = read( new_socket , buffer, 1024);
    trucks=atoi(buffer);
    int a[4]={dogs,cats,cars,trucks};
  char image[]="images/";
  char jp[]=".jpg";
  char index[4][2]={"1","2","3","4"};
  char str[4][10]={"dogs/","cats/","cars/","trucks/"};
  // char d[]="dogs/";
  // char ct[]="cats/";
  // char cr[]="cars/";
  // char t[]="trucks/";


  for(int i=0;i<4;i++){
    char location[25];
    strcpy(location,image);
    strcat(location,str[i]);
    for(int j=0;j<a[i];j++){
      char final[40];
      strcpy(final,location);
      strcat(final,index[j]);
      strcat(final,jp);
      // printf("%s\n", final);     

      // printf("Getting Picture Size\n");
      FILE *picture;
      picture = fopen(final, "r");
      int size;
      fseek(picture, 0, SEEK_END);
      size = ftell(picture);
      fseek(picture, 0, SEEK_SET);
      tostring(buffer,size);
      send(new_socket,buffer,1024,0);
      // printf("Sending Picture Size=%d\n",size);
      //Send Picture as Byte Array
      // printf("Sending Picture as Byte Array\n");
      char send_buffer=(char)(malloc(size*sizeof(char)));
      fread(send_buffer, 1, size, picture);
      // printf("Size of send_buffer = %d\n",size );
      send(new_socket,send_buffer,size,0);
      bzero(send_buffer, sizeof(send_buffer));

    }
  }
    return 0;
}
