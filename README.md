# Assignment1

# Instructions regarding Assignment :

build server image
`docker build -t cs252/server:v1 ./server`

build client from c file
`cd ./client && gcc client.c -o cli.out`

Run docker server
`docker run cs252/server:v1`

Run client
`./cli.out`

Submit your query :)
