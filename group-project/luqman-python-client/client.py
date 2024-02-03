import socket
import time

def get_latest_points(user):
    try:
        client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

        server_address = ('luqman-python-server', 5002)

        client_socket.connect(server_address)

        request = f"{user},update"
        client_socket.send(request.encode('utf-8'))
        
        response = client_socket.recv(1024).decode('utf-8')
        print(f"Server response: {response}")

    except Exception as e:
        print(f"Error: {e}")

    finally:
        client_socket.close()

if __name__ == "__main__":
    while True:
        get_latest_points("luqman-python")
        time.sleep(30)
