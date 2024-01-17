FROM python:latest

WORKDIR /usr/src/python-server

RUN pip install mysql-connector-python

COPY server.py .

CMD ["python3", "./server.py"]
