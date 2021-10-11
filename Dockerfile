FROM asneg/opcuastack:release-4

# Prepare workdir
ADD / /tmp
RUN mkdir /build
WORKDIR /build

# Build
RUN cmake -DOPTION_OPCUAPIXTENDSERVER_SPI="${SPI_DUMMY}" /tmp/src
RUN make
RUN make install

# Start OpcUaPiXtendServer
EXPOSE 8898 4840
CMD ["OpcUaServer4", "/etc/OpcUaStack/OpcUaPiXtendServer/OpcUaServer.xml"]
