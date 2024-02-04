import socket
import time

def get_latest_points(user):
    try:
        # Create a socket
        client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

        # Set up the server address
        server_address = ('azam-python-server', 8321)

        # Connect to the server
        client_socket.connect(server_address)

        # Send update request to the server
        request = f"{user},update"
        client_socket.send(request.encode('utf-8'))

        # Receive and print the server's response
        response = client_socket.recv(1024).decode('utf-8')
        print(f"Server response: {response}")

    except Exception as e:
        print(f"Error: {e}")

    finally:
        # Close the socket
        client_socket.close()

if __name__ == "__main__":
    while True:
        get_latest_points("azam-python")
        time.sleep(30)
