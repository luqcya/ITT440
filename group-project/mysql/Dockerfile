FROM mysql:latest

COPY my.cnf /etc/mysql/conf.d/
COPY init.sql /docker-entrypoint-initdb.d/

ENV MYSQL_ROOT_PASSWORD=root123
ENV MYSQL_DATABASE=itt440
ENV MYSQL_USER=luqman
ENV MYSQL_PASSWORD=luqman123

EXPOSE 3306