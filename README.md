# Assignment1

# Instructions regarding docker:

This repository has dockerized both server as well as client and works as follows :

First, create a network cs252_net for communication : 

        docker network create cs252_net
        
Next, Build a cs252/server image from server/Dockerfile (need to be done only once) :

        docker build -t cs252/server:v1 ./server/
        
Next, Build a cs252/cient image from client/Dockerfile (need to be done only once) :

        docker build -t cs252/client:v1 ./client/
        
Next, run server and client using above cs252_net network (preferably run server in background and client in terminal) :
```
        docker run -d --net cs252_net --name server cs252/server:v1
        docker run --net cs252_net --name client cs252/client:v1
```
