FROM gcc:latest
COPY . /code
WORKDIR /code
EXPOSE 25250
RUN gcc -w server.c -o ser
CMD ["./ser"]
