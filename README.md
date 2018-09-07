# Assignment1

# Instructions regarding Assignment :

build server image
`docker build -t cs252/server:v1 ./server`


Run docker server
`docker run -p  5555:5555 cs252/server:v1`

build client from c file
`cd ./client && gcc client.c -o cli.out`

Run client
`./cli.out 0.0.0.0 5555`

Submit your query :)
