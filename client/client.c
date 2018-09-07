/* credit @Daniel Scocco */

/****************** CLIENT CODE ****************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <math.h>
#include <string.h>
#include <arpa/inet.h>
#define MAXSIZE 100000
static char name[12];

int isnum(char* str){
  int i;
  for(i=0;i<strlen(str);i++){
    if(!isdigit(str[i])){
      break;
    }
  }
  return i==strlen(str);
}
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

int main(int argc, char** argv){
    system("rm -f *.jpg");
    int clientSocket, num, b, p;
    char fileb[1024];
    int count[4] = {0};
    int i[1] = {1};
    char buffer[MAXSIZE];
    struct sockaddr_in serverAddr;
    socklen_t addr_size;
    clientSocket = socket(PF_INET, SOCK_STREAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(atoi(argv[2]));
    serverAddr.sin_addr.s_addr = inet_addr(argv[1]);
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
    addr_size = sizeof serverAddr;
    connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);


    printf("Enter your Query here! :\n");
    int dogs=0,cats=0,cars=0,trucks=0;
  {
    char* str = (char*)malloc(1025*sizeof(char));
    memset(str, '\0', 1024*sizeof(char));
  
    // printf("Enter a string : ");
    int cnt=0;
    int size=fscanf(stdin, "%[^\n]", str);
  
    // printf("Size of : %d\n", strlen(str));
    int L=strlen(str);
    str[strlen(str)]='\0';
  
    // printf("Recieved : %s##\n", str);
  
    char *token = strtok(str, " ");
  
    int num=0;
    int flag=0;
    int readd=0;
    if(isnum(token)){
        num=atoi(token);
      }
    while(token !=NULL)
    {   
      // printf("token : %s\n", token);
      // str = str + strlen(token);
      if(isnum(token)){
        num=atoi(token);
      }
      if(strcmp(token, "dogs") == 0 || strcmp(token, "dog")==0){
        // printf("dogs\n");
        dogs = num;
      }else if(strcmp(token, "cats") == 0 || strcmp(token, "cat")==0){
        // printf("cats\n");
        cats=num;
      }else if(strcmp(token, "cars") == 0 || strcmp(token, "car")==0){
        // printf("cars\n");
        cars=num;
      }else if(strcmp(token, "trucks") == 0 || strcmp(token, "truck")==0){
        // printf("trucks\n");
        trucks=num;
      }
      token = strtok(NULL, " ");
      
    }
    // printf("Recieved %d dogs, %d cats, %d trucks, %d cars", dogs, cats, trucks, cars);
  
  }
    count[0] = dogs;
    count[1] = cats;
    count[2] = cars;
    count[3] = trucks;
    int encode = dogs + cars*5 + cats*25 + trucks*125;
    printf("%d %d %d %d\n",count[0], count[1], count[2], count[3]);
    tostring(buffer, encode);
    send(clientSocket, buffer, 1024, 0);
    FILE* fp;
    char str[4][10]={"dogs","cats","cars","trucks"};
    for(int qw =0;qw<4;qw++){
      for(int k = 0;k<count[qw];k++){
        static char jp[6];
        jp[0]=k+1-0+'0';
        jp[1]='.';
        jp[2]='j';
        jp[3]='p';
        jp[4]='g';
        jp[5]='\0';
        jp[6]='\0';
        char final[50];
        strcpy(final,str[qw]);
        strcat(final,jp);

        fp = fopen(final, "wb");
        b = recv(clientSocket, buffer, sizeof(buffer), 0);
        printf("%d\n",b);
        fwrite(buffer, 1, b, fp);
        // printf("here_11\n");
      
        send(clientSocket, i, sizeof(int), 0);
        // printf("here_12\n");
      
        fclose(fp);
      }
  }
  system("./web.sh > index.html");
  system("firefox index.html  ");

  return 0;
}
