# OCPP Embedded Client  
### Brief Description
This is an STM32 Arduino implementation of an OCPP-1.6 client. Websocket communication is delegated to a VCON device (https://vcon.io/), which is providing a transparent  serial-websocket bridge. JSON RPC handling is done using the mjson library from Cesanta (https://github.com/cesanta/mjson). 

This program's architecture is using two well known patterns - "Chain of Responsibility", used for handling requests and "State/Context" for dealing with device states.

This code has been tested on an STM32F091RC with 32K RAM of which 15K are statically allocated. Flash memory occupied is ~64K.

Some C++ STL components are used such as map and vector.

### Known Issues

There is a problem related to memory management when creating and deleting message handlers.
