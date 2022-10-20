FROM ubuntu:20.04
ENV DEBIAN_FRONTEND noninteractive
WORKDIR cash_map
COPY . .
RUN apt -y update && \
    apt -y install gcovr python3-pip && \
    pip3 install cpplint && \
    pip3 install --upgrade cmake && \
    apt clean && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*
