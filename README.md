# ititviti_dev

Developer Coding Exercise

#### Task

Client connect through a stream socket to a server and sends messages to the server which echos back the 
bytes received. The client receives and identifies the same message it sent.

The client sends *n* messages to the server and for each message it receives the client calculate the 
round trip time *RTT* for each message sent.
 
When the client have sent all the *n* messages the average *RTT* and and the throughput (*Bps*)
is calculated for all the messages which is displayed at the end before the client executable
ends.

#### Implementation details

The client writes *n* messages, which is specified as a argument when running the client.
For each message that is written to the server it associates the message with a timestamp *s* 
and store the pair in a *std::map*.
 
An additional thread is started to read all the messages echoed back from the server to the client on
the same socket. When the thread receives a message it finds the message in the map and calculates
the *RTT* for the specific message. This is done through a timestamp *e* when the whole message is 
received. A diff (*=e-s*) is calculated and displayed to standard out. 

The message has been chosen to be of type **uint64_t** which is guarantee to be 8 bytes in length on
all platforms.

##### The RTT and throughput calculation

A time stamp *start* is created before sending the first message to the server and time stamp *end* is
taken after *n* messages has been sent to the server. The difference is calculated *end - start* and divided
by the amount of bytes sent to the buffer.

Some assumptions has been made when calculating the RTT. The calculation has not taken into account the
following:

1. Time spend in the sending TCP buffer on the client.
 
2. Time spend in the receiving TCP buffer on the server side.
 
3. Time spend in the sending TCP buffer on the server side.

4. Time spend in the receiving TCP buffer on the client side.

5. Time inserted a entry in the *std::map*.

Some assumptions has been made when calculating the throughput. The calculation has not taken into account the
following:

1. The TCP/IP header size

#### Installation

##### Requirement

To compile and run the application the following is required:

1. cmake >= 3.5.1
2. GCC 5.4.0, C++ with std 11
  
##### build

```shell
$ mkdir build 
$ cd build
$ cmake ..
$ make
```
##### run

First it is required to start the echo server, in one terminal (1) run:

```shell
$ ./server_start 127.0.0.1 <port>
```
Where *\<port\>* should be replaced by chosen listening port.

Start additional terminal, (2) and run:

```shell
$ ./client_start 127.0.0.1 <port> <num-requests>
```

Where *\<port\>* should be replaced by the chosen port specified in the terminal (1).
The *\<num-request\>* is the number of request the client is issued to the server must be specified.
 
For example:
 ```shell
 $ ./client_start 127.0.0.1 4174 20
RT = 0.213776 millis
RT = 0.248452 millis
RT = 0.244865 millis
RT = 0.24318 millis
RT = 0.243838 millis
RT = 0.244774 millis
RT = 0.247349 millis
RT = 0.252281 millis
RT = 0.259425 millis
RT = 0.259754 millis
Avg: 0.245769 millis
Throughput: 529770 Bps
```






