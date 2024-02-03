FROM ubuntu:latest

RUN apt-get update && apt-get install -y build-essential

COPY client.c /app/client.c

WORKDIR /app

RUN gcc -o client client.c

CMD sh -c './client && sleep 30'
