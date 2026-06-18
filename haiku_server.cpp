#include <iostream> 
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0); 
    if (server_fd == -1) {
        std::cerr << "socket() failed\n"; 
        return 1; 
    }

    std::cout << "Socket created: fd = " << server_fd << "\n"; 

    sockaddr_in address; 
    address.sin_family = AF_INET;
    address.sin_port = htons(5575); 
    address.sin_addr.s_addr = INADDR_ANY; 

    if (bind(server_fd, (sockaddr*)&address, sizeof(address)) == -1) {
        std::cerr << "bind() failed\n"; 
    }

    std::cout << "Bound to port 5575\n"; 

    if (listen(server_fd, 5) == -1) {
        std::cerr << "listen() failed\n";
        return 1; 
    }
    std::cout << "Listening... waiting for a client\n"; 

    sockaddr_in client_address; 
    socklen_t client_len = sizeof(client_address); 

    int client_fd = accept(server_fd, (sockaddr*)&client_address, &client_len); 
    if (client_fd ==  -1) {
        std::cerr << "accept() failed\n"; 
        return 1; 
    }

    std::cout << "A client connected! client_fd = " << client_fd << "\n";
    
    const char* haiku[] = {
        "Silent socket waits\n", 
        "A client knocks, port wakes\n", 
        "Words flow, then goodbye\n" 
    };

    for(int i = 0; i < 3; i++) {
        write(client_fd, haiku[i], strlen(haiku[i])); 
    }

    close(client_fd); 
    close(server_fd);
    return 0; 
}