import socket

def generate_fibonacci_sequence(start, count):
    sequence = [0, 1] if start == 1 else [1, 1]
    for _ in range(2, count):
        sequence.append(sequence[-1] + sequence[-2])
    return sequence

def udp_fibonacci_server():
    server_address = ('localhost', 11235)

    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as server_socket:
        server_socket.bind(server_address)
        print(f"UDP Fibonacci Server is listening on {server_address}")

        while True:
            data, client_address = server_socket.recvfrom(1024)
            n = int(data.decode())

            if n < 0:
                break

            fibonacci_sequence = generate_fibonacci_sequence(n, 5)
            response = ', '.join(map(str, fibonacci_sequence))

            server_socket.sendto(response.encode(), client_address)

if __name__ == "__main__":
    udp_fibonacci_server()
