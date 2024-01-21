import socket

def udp_time_client():
    server_address = ('localhost', 22000)

    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as client_socket:
        client_socket.sendto('get_time'.encode(), server_address)
        data, _ = client_socket.recvfrom(1024)
        server_time = data.decode()
        print(f"Server Time: {server_time}")

if __name__ == "__main__":
    udp_time_client()
