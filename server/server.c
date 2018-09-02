
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
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


int main(){
  int welcomeSocket, newSocket;
  char buffer[1024];
  struct sockaddr_in serverAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size;

  /*---- Create the socket. The three arguments are: ----*/
  /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
  welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);

  /*---- Configure settings of the server address struct ----*/
  /* Address family = Internet */
  serverAddr.sin_family = AF_INET;
  /* Set port number, using htons function to use proper byte order */
  serverAddr.sin_port = htons(5432);
  /* Set IP address to localhost */
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  /* Set all bits of the padding field to 0 */
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

  /*---- Bind the address struct to the socket ----*/
  bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

  /*---- Listen on the socket, with 5 max connection requests queued ----*/
  if(listen(welcomeSocket,5)==0)
    printf("I'm listening\n");
  else
    printf("Error\n");

  /*---- Accept call creates a new socket for the incoming connection ----*/
  addr_size = sizeof serverStorage;
  newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);

  /*---- Send message to the socket of the incoming connection ----*/


  //Get Picture Size
  
  int dogs=0,cats=0,cars=0,trucks=0;
  recv(newSocket, buffer, 1024, 0);
  dogs=atoi(buffer);
  recv(newSocket, buffer, 1024, 0);
  cats=atoi(buffer);
  recv(newSocket, buffer, 1024, 0);
  cars=atoi(buffer);
  recv(newSocket, buffer, 1024, 0);
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
      printf("%s\n", final);     

      printf("Getting Picture Size\n");
      FILE *picture;
      picture = fopen(final, "r");
      int size;
      fseek(picture, 0, SEEK_END);
      size = ftell(picture);
      fseek(picture, 0, SEEK_SET);
      tostring(buffer,size);
      send(newSocket,buffer,1024,0);
      printf("Sending Picture Size=%d\n",size);
      //Send Picture as Byte Array
      printf("Sending Picture as Byte Array\n");
      char *send_buffer=(char*)(malloc(size*sizeof(char)));
      fread(send_buffer, 1, size, picture);
      printf("Size of send_buffer = %d\n",size );
      send(newSocket,send_buffer,size,0);
      bzero(send_buffer, sizeof(send_buffer));

    }
  }

  
  
  return 0;
}
