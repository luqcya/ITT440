import socket
from datetime import datetime

def udp_time_server():
    server_address = ('localhost', 22000)

    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as server_socket:
        server_socket.bind(server_address)
        print(f"UDP Time Server is listening on {server_address}")

        while True:
            data, client_address = server_socket.recvfrom(1024)
            if data.decode().lower() == 'get_time':
                current_time = str(datetime.now())
                server_socket.sendto(current_time.encode(), client_address)

if __name__ == "__main__":
    udp_time_server()
