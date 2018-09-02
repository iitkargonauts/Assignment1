#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 25250
#define SERVER_IP "172.18.0.2"

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

int isnum(char* str){
	int i;
	for(i=0;i<strlen(str);i++){
		if(!isdigit(str[i])){
			break;
		}
	}
	return i==strlen(str);
}


int main(int argc, char const *argv[])
{
	struct sockaddr_in address;
	int sock = 0, valread;
	struct sockaddr_in serv_addr;
	char *hello = "Hello from client";
	char buffer[1000] = {0};
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

	/*---- Read the message from the server into the buffer ----*/
	int dogs=0,cats=0,cars=0,trucks=0;

	size_t bufsize = 1024;
	char* str = (char*)malloc(1025*sizeof(char));
	memset(str, '\0', 1024*sizeof(char));

	printf("Enter a string : ");
	int cnt=0;
	int size=fscanf(stdin, "%[^\n]", str);

	printf("Size of : %d\n", strlen(str));
	int L=strlen(str);
	str[strlen(str)]='\0';

	printf("Recieved : %s\n", str);

	char* rest;

	char *token = strtok(str, " ");
	int num=0;
	int flag=0;
	int readd=0;

	readd = readd + strlen(token) + 1;

                if(isnum(token)){
                        num=atoi(token);
                }
                if(strcmp(token, "dogs") == 0 || strcmp(token, "dog")==0){
                        printf("dogs\n");
                        dogs = num;
                }else if(strcmp(token, "cats") == 0 || strcmp(token, "cat")==0){
                        printf("cats\n");
                        cats=num;
                }else if(strcmp(token, "cars") == 0 || strcmp(token, "car")==0){
                        cars=num;
                        printf("cars : %d\n", cars);
                }else if(strcmp(token, "trucks") == 0 || strcmp(token, "truck")==0){
                        printf("trucks\n");
                        trucks=num;
                }



	while(1)
	{   
		token = strtok(NULL, " ");
		if(!token){
			break;
		}
		printf("token : %s\n", token);
		readd = readd + strlen(token) + 1;

		if(isnum(token)){
			num=atoi(token);
		}
		if(strcmp(token, "dogs") == 0 || strcmp(token, "dog")==0){
			printf("dogs\n");
			dogs = num;
		}else if(strcmp(token, "cats") == 0 || strcmp(token, "cat")==0){
			printf("cats\n");
			cats=num;
		}else if(strcmp(token, "cars") == 0 || strcmp(token, "car")==0){
			cars=num;
			printf("cars : %d\n", cars);
		}else if(strcmp(token, "trucks") == 0 || strcmp(token, "truck")==0){
			printf("trucks\n");
			trucks=num;
		}
		printf("readd : %d\n", readd);
		printf("L : %d\n", L);
		if(readd>=L){
			printf("inside");
			break;
		}
	} 

	printf("Recieved %d dogs, %d cats, %d trucks, %d cars", dogs, cats, trucks, cars);

	for(int i=1;i<=dogs+cats+cars+trucks;i++){
		int size;
		read(sock, buffer, 1024);
		size=atoi(buffer);
		printf("Picture Size=%d\n",size);
		char* recv_buffer=(char*)(malloc(size*sizeof(char)));
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
		printf("Size of recv_buffer = %ld\n",sizeof(recv_buffer) );
		fwrite(recv_buffer,  1,size, image);
		fclose(image);
		free(recv_buffer);
	}

	printf("running web\n");

	char com[50]="./web.sh ";
	char n_images[50];
	tostring(n_images,dogs+cats+cars+trucks);
	strcat(com,n_images);
	char f[30]=" > index.html";
	strcat(com,f);
	system(com);
	system("firefox index.html");

	return 0;
}
