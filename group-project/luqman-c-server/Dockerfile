FROM ubuntu:latest

RUN apt-get update && apt-get install -y build-essential libmysqlclient-dev

COPY server /app/server

WORKDIR /app

# RUN gcc -o server server.c -lmysqlclient -I /usr/include/mysql -L /usr/lib/mysql

EXPOSE 6002

CMD ["./server"]
