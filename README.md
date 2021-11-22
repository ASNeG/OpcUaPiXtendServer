Overview
--------
The OpcUaPiXtendServer provides an interface to access input channels and output channels of the PiXtend hardware via the OPC UA protocol. You can use the OpcUaPiXtendServer on an Linux PC (Ubuntu) or on a Raspberry Pi 4B (Raspbian).

The OpcUaPiXtendServer provides the following services.

- PiXtend V2S (Only Raspberry Pi)
  - Read/Write digital output channel RELAY0 - RELAY3
  - Read/Write digital output channel DO0 - DO3
  - Read digital input channel DI0 - DI7
  - Read/Write analog output channel AO0 - AO1
  - Read analog input channel AI0 - AI1
- PiXtend V2L (Only Raspberry Pi)
  - Read/Write digital output channel RELAY0 - RELAY3
  - Read/Write digital output channel DO0 - DO11
  - Read digital input channel DI0 - DI15
  - Read/Write analog output channel AO0 - AO1
  - Read analog input channel AI0 - AI5

Installation
------------
In order to compile and install the OpcUaPiXtendServer from the source code, you should meet the following requirements.
- Compile with C++17 support (we test only GCC)
- CMake >= 3.5
- Boost > 1.65
- OpenSSL >= 1.0.0

**Operation System** <br>
Rasbian is used as the operation system. You can download the base image of the operation system from the pixtend website. <br>  
https://www.pixtend.de/files/downloads/PiXtend_Image_Basic_V2_1_7_0.zip

**Install OpcUaStack:**
1. Intall the requirements using apt-get command. 
```
$ sudo apt-get install libboost-all-dev cmake libssl-dev  build-essential
```

2. Clone OpcUaStack repository and change to branch Release4
```
$ git clone https://github.com/ASNeG/OpcUaStack.git
$ cd OpcUaStack
$ git checkout origin/Release4 -b Release4
```

3. Build and Install OpcUaStack
```
$ sh build.sh -t local
```

The OPC UA Server has now installed in the directory ${HOME}/.ASNeG/


**Install OpcUaPiXtendServer:**
1. Clone OpcUaPiXtendServer repository
```
$ git clone https://github.com/ASNeG/OpcUaPiXtendServer.git
$ cd OpcUaPiXtendServer
```

2. Build OpcUaPiXtendServer
```
$ sh build.sh -t local -s ~/.ASNeG
```

The PiXtend Server Library has now installed in the directory ${HOME}/.ASNeG/

You can test the OpcUaPiXtendServer on the PC. In this case the SPI interface (for PiXtend V2S and PiXtend V2L access) is not available and the hardware access is replaced by a dummy server. Use the following command.
```
$ sh build.sh -t local -s ~/.ASNeG -a SPI_DUMMY
```
On the PC the modbus library is required. Use the following command for the installation:
```
$ sudo apt-get install libmodbus-dev
```

Hardware Configuration
----------------------

The used hardware module must be specified in the configuratuion file `${HOME}/.ASNeG/etc/OpcUaStack/OpcUaPiXtendServer/OpcUaPiXtendServer.xml`. The following hardware modules can be used.

- PiXtend V2L
- PiXtend V2S


**PiXtendV2S**

Example Configuration:
```
<?xml version="1.0" encoding="utf-8"?>
<OpcUaPiXtendServer Name="TestTags" xmlns="http://ASNeG/OpcUaPiXtendServer.xsd">
    <Modules>
        <Module Enable="1">
            <Name>PiXtendV2S</Name>
            <Type>V2S</Type>
        </Module>
    </Modules>
</OpcUaPiXtendServer>
```

The OPC UA Server provides the configured object in the information model as follows.
```
Root
 |- Object
      |- PiXtend
           |- PixTendV2S
              |- AI       (AI0-AI1 Read)
              |- AO       (AO0-AO1 Read/Write)
              |- DI       (DI0-DI7 Read)
              |- DO       (DO0-DO3 Read/Write)
              |- RELAY    (RELAY0-RELAY4 Read/Write)
```

**PiXtend V2L**

Example Configuration:
```
<?xml version="1.0" encoding="utf-8"?>
<OpcUaPiXtendServer Name="TestTags" xmlns="http://ASNeG/OpcUaPiXtendServer.xsd">
    <Modules>
        <Module Enable="1">
            <Name>PiXtendV2L</Name>
            <Type>V2L</Type>
        </Module>
    </Modules>
</OpcUaPiXtendServer>
```

The OPC UA Server provides the configured object in the information model as follows.
```
Root
 |- Object
      |- PiXtend
           |- PixTendV2L
              |- AI       (AI0-AI5 Read)
              |- AO       (AO0-AO1 Read/Write)
              |- DI       (DI0-DI15 Read)
              |- DO       (DO0-DO11 Read/Write)
              |- RELAY    (RELAY0-RELAY4 Read/Write)
```

OPC UA Server Configuration
---------------------------

The OPC UA configuration is in the file `${HOME}/.ASNeG/etc/OpcUaStack/OpcUaPiXtendServer/OpcUaServer.xml`.


Start OPC UA Server 
-------------------

To start the OPC UA Server, the following commands must be executed.
```
$ export PATH=${PATH}:${HOME}/.ASNeG/usr/bin
$ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${HOME}/.ASNeG/usr/lib
$ OpcUaServer4 ${HOME}/.ASNeG/etc/OpcUaStack/OpcUaPiXtendServer/OpcUaServer.xml
```

The OPC UA Server opens the port 8898. To connect to the OPC UA Server by a OPC UA Client the client must used the Endpoint Url opc.tcp://<HOSTNAME>:8898.


