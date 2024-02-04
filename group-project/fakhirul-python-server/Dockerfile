FROM python:latest

WORKDIR /usr/src/python-server

RUN pip install mysql-connector-python

COPY server.py .

EXPOSE 8123

CMD ["python3", "./server.py"]