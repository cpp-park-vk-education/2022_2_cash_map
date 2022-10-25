FROM ubuntu:20.04
ENV DEBIAN_FRONTEND noninteractive
WORKDIR cash_map
COPY . .
RUN apt -y update && \
    apt -y install python3 cppcheck clang-tidy make git gcovr python3-pip libgtest-dev && \
    pip3 install cpplint && \
    pip3 install --upgrade cmake && \
    apt clean && \
    rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*
