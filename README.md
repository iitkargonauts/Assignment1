# Assignment1

# Instructions regarding Assignment :

build server image
`docker build -t cs252/server:v1 ./server`


Run docker server
`docker run cs252/server:v1 --name cs252_server`i

Get docker server IP :
`docker inspect bbf2c8c5d3a6 | grep \"IPAddress\"  | tr -s ' ' | uniq | cut -d ':' -f 2 | tr -d '", '`

Change IP in client.c 

build client from c file
`cd ./client && gcc client.c -o cli.out`

Run client
`./cli.out`

Submit your query :)
