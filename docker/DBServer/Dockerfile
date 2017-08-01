FROM ubuntu:16.04

RUN apt-get update && apt-get install -y libzdb-dev g++

COPY . /bango
WORKDIR /bango
RUN ./BUILD
WORKDIR /bango/bin

# sleep to wait for mysql to become ready
CMD sleep 10 && ./DBServer
