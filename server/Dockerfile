FROM gcc:latest
COPY . /code
WORKDIR /code
EXPOSE 5555
RUN gcc -w server.c -o ser
CMD ["./ser", "0.0.0.0", "5555"]
