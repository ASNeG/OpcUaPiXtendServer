FROM asneg/opcuastack:release-4

# Install dependencies
RUN apt-get update&& apt-get install -y git autoconf

# Prepare workdir
ADD / /tmp
RUN mkdir /build
WORKDIR /build

# Build libmodbus library
RUN git clone https://github.com/ASNeG/libmodbus.git
RUN cd libmodbus \
      && ./autogen.sh \
      && ./configure \
      && make install

# Build opc ua pixtend server
RUN cmake -DOPTION_OPCUAPIXTENDSERVER_SPI="SPI_DUMMY" /tmp/src
RUN make
RUN make install

# Start OpcUaPiXtendServer
EXPOSE 8898 4840
CMD ["OpcUaServer4", "/etc/OpcUaStack/OpcUaPiXtendServer/OpcUaServer.xml"]
