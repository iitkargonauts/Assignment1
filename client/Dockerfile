FROM gcc:latest
RUN apt-get update && apt-get -y install telnet
COPY . /code
WORKDIR /code
EXPOSE 25250
RUN gcc -w client.c -o cli
CMD ["./cli"]
