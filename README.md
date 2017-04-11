# ititviti_dev

Developer Coding Exercise

To install:

<code>

$ mkdir build 

$ cd build;

$ cmake ..

$ make

</code>

First it is required to stat the echo server, In terminal 1 run:
<code>

./server_start 127.0.0.1 \<port>

</code>

Where port should be replaced by listening port

Start additional terminal, (terminal 2) and run:

<code>

$ ./client_start 127.0.0.1 \<port> \<num-requests>

</code>

Where \<port\> should be replaced by port specified in the first terminal
\<num-request\> which is the number of request the client is issued should be specified.
 
 For example:
 <code>
 $ ./client_start 127.0.0.1 4174 20

RT = 0.141874 millis

RT = 0.165283 millis

RT = 0.168535 millis

RT = 0.172627 millis

RT = 0.177263 millis

RT = 0.186348 millis

RT = 0.197138 millis

RT = 0.206887 millis

RT = 0.211436 millis

RT = 0.220602 millis

RT = 0.230359 millis

RT = 0.234077 millis

RT = 0.243516 millis

RT = 0.234839 millis

RT = 0.244032 millis

RT = 0.253762 millis

RT = 0.263422 millis

RT = 0.273165 millis

RT = 0.282394 millis

RT = 0.293377 millis

Avg: 0.220047 millis
</code>






