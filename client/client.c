

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

int main(){
  int clientSocket;
  char buffer[1024];
  struct sockaddr_in serverAddr;
  socklen_t addr_size;

  /*---- Create the socket. The three arguments are: ----*/
  /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
  clientSocket = socket(PF_INET, SOCK_STREAM, 0);

  /*---- Configure settings of the server address struct ----*/
  /* Address family = Internet */
  serverAddr.sin_family = AF_INET;
  /* Set port number, using htons function to use proper byte order */
  serverAddr.sin_port = htons(5432);
  /* Set IP address to localhost */
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  /* Set all bits of the padding field to 0 */
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

  /*---- Connect the socket to the server using the address struct ----*/
  addr_size = sizeof serverAddr;
  connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);

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
  send(clientSocket,buffer,1024,0);
  tostring(buffer,cats);
  send(clientSocket,buffer,1024,0);
  tostring(buffer,cars);
  send(clientSocket,buffer,1024,0);
  tostring(buffer,trucks);
  send(clientSocket,buffer,1024,0);


  for(int i=1;i<=dogs+cats+cars+trucks;i++){    
    int size;
    recv(clientSocket, buffer, 1024, 0);
    size=atoi(buffer);
    // printf("Picture Size=%d\n",size);
    char *recv_buffer=(char*)(malloc(size*sizeof(char)));
    // printf("Reading Picture Byte Array\n");
    // printf("Converting Byte Array to Picture\n");
    FILE *image;
    char name[20];
    tostring(name,i);
    char jp[]=".jpg";
    strcat(name,jp);
    image = fopen(name, "w");
    recv(clientSocket, recv_buffer, size, 0);
    // printf("Size of recv_buffer = %ld\n",sizeof(recv_buffer) );
    fwrite(recv_buffer,  1,size, image);
    fclose(image);
  }

  return 0;
}
