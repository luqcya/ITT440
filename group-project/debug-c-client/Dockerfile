FROM ubuntu:latest

RUN apt-get update \
    && apt-get install -y iputils-ping nano gcc dnsutils \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY client.c /app/client.c

CMD [ "/bin/bash" ]

