FROM ubuntu:latest

RUN apt-get update && apt-get install -y build-essential libmysqlclient-dev

COPY server.c /app/server.c

WORKDIR /app

RUN gcc -o server server.c -lmysqlclient -I /usr/include/mysql -L /usr/lib/mysql

EXPOSE 7123

CMD ["./server"]