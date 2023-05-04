FROM gcc:latest
WORKDIR /root/ramium
RUN apt update
RUN apt -y upgrade
RUN apt -y dist-upgrade
RUN apt -y install libcrypto++-dev libcrypto++-doc libcrypto++-utils
ENTRYPOINT tail -f /dev/null