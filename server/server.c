
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <math.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define MAXSIZE 100000

int main(int argc, char** argv){

  int welcomeSocket, newSocket, num, b, p;
  int typ[4] = {0};
  int uu[1] = {1};
  
  char buffer[MAXSIZE];
  char sendbuffer[MAXSIZE];
  char imagename[17] = "files/typ0/1.jpg"; //change idx 9,11
  struct sockaddr_in serverAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size;

  welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(atoi(argv[2]));
  serverAddr.sin_addr.s_addr = inet_addr(argv[1]);
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
  bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
  if(listen(welcomeSocket,5)==0){
    printf("I'm listening\n");
  } else {
    printf("Connection Error\n");
  }

  addr_size = sizeof serverStorage;
  newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);
  printf("Server got connection from a client\n");


  int dogs=0,cats=0,cars=0,trucks=0;

  read(newSocket, buffer,1024);
  int encode=atoi(buffer);
  printf("encode = %d ", encode);
  trucks = encode/125;
  cats = (encode%125)/25;
  cars = (encode%25)/5;
  dogs = encode%5;
  printf("I have recieved %d dogs, %d cats, %d cars and %d trucks\n", dogs, cats, cars, trucks);

  typ[0]=dogs;
  typ[1]=cats;
  typ[2]=cars;
  typ[3]=trucks;



  printf("Server:Msg Received %d %d %d %d\n", typ[0], typ[1], typ[2], typ[3]);
  FILE *fp;
  

  // while(typ[0]+typ[1]+typ[2]+typ[3]>0){
  //     //printf("in loop begin %d %d %d\n", typ[0], typ[1], typ[2]);
  //     if(typ[0]>0){
  //         imagename[9] = '0';
  //         imagename[11] = typ[0] +'0';
  //         typ[0]--;
  //     } else if(typ[1]> 0){
  //         imagename[9] = '1';
  //         imagename[11] = typ[1] +'0';
  //         typ[1]--;
  //     } else if(typ[2]>0){
  //         imagename[9] = '2';
  //         imagename[11] = typ[2] +'0';
  //         typ[2]--;
  //     } else if(typ[3]>0){
  //         imagename[9] = '3';
  //         imagename[11] = typ[3] +'0';
  //         typ[3]--;
  //     }
  //     fp = fopen(imagename, "rb");
  //     //printf("%s\n",imagename);
  //     b = fread(sendbuffer, 1, sizeof(sendbuffer), fp);
  //     // if(send(newSocket, sendbuffer, b, 0)==-1){
  //     //     fprintf(stderr, "Failure Sending Message\n");
  //     //     close(newSocket);
  //     //     break;
  //     // }
  //     send(newSocket, sendbuffer, b, 0)
  //     while(!(recv(newSocket, i, sizeof(int), 0)>0));
  //     printf("File sent %d\n",b);
  //     fclose(fp);
  //     //printf("in loop end %d %d %d\n", typ[0], typ[1], typ[2]);
  // }

  int a[4]={dogs,cats,cars,trucks};
  char image[]="images/";
  char jp[]=".jpg";
  char index[4][2]={"1","2","3","4"};
  char str[4][10]={"dogs/","cats/","cars/","trucks/"};

  for(int i=0;i<4;i++){
    char location[25];
    strcpy(location,image);
    strcat(location,str[i]);
    for(int j=0;j<a[i];j++){
      char final[40];
      strcpy(final,location);
      strcat(final,index[j]);
      strcat(final,jp);

      FILE *picture;
      picture = fopen(final, "rb");

      int r = fread(buffer, 1, MAXSIZE, picture);
      printf("Size of send_buffer = %d\n",r );
      send(newSocket,buffer,r,0);
      // printf("here_11\n");
      while(!(recv(newSocket, uu, sizeof(int), 0)>0));
      // printf("here_12\n");
      fclose(picture);
    
    }
  }

  close(newSocket);
  close(welcomeSocket);
  return 0;
}
