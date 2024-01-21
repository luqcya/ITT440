import socket

def udp_fibonacci_client():
    server_address = ('localhost', 11235)

    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as client_socket:
        while True:
            n = int(input("Enter the term number (or -1 to quit): "))

            if n < 0:
                client_socket.sendto(str(n).encode(), server_address)
                break

            client_socket.sendto(str(n).encode(), server_address)
            data, _ = client_socket.recvfrom(1024)
            print(f"Fibonacci Sequence: {data.decode()}")

            choice = input("Do you want another five sequences? (yes/no): ").lower()
            if choice != 'yes':
                client_socket.sendto('-1'.encode(), server_address)
                break

if __name__ == "__main__":
    udp_fibonacci_client()
