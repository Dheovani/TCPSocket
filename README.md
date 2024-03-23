# My TCP Socket in C
This is a simple example of a TCP server in C using the Winsock library on Windows.

## What does it do?
- Accepts client connections on a specific port
- Receives messages from clients and prints them
- Sends a fixed "Hello, World!" response message to clients

## Try it out
1. Clone this repository:
```
git clone https://github.com/Dheovani/TCPSocket.git
```
1. Compile the source code:
    - Open the command prompt
    - Navigate to the project directory
    - Run the compilation command, for example:
```
gcc main.c -o socket.exe -lws2_32
```
1. Run the server
1. Connect to the server using a TCP client, such as your internet browser:


## License
This project is licensed under the [MIT License](LICENSE.txt).