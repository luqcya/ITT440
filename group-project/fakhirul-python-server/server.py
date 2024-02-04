import socket
import mysql.connector
from datetime import datetime
import time

db_config = {
    'host': 'mysql', 
    'user': 'root',
    'password': 'root123',
    'database': 'itt440'
}

def update_database(user, points):
    try:
        db_connection = mysql.connector.connect(**db_config)
        db_cursor = db_connection.cursor()

        check_user_query = "SELECT * FROM itt440 WHERE user = %s"
        db_cursor.execute(check_user_query, (user,))
        existing_user = db_cursor.fetchone()

        if existing_user:
            update_query = "UPDATE itt440 SET points = %s, datetime_stamp = NOW() WHERE user = %s"
            db_cursor.execute(update_query, (points, user))
        else:
            insert_query = "INSERT INTO itt440 (user, points, datetime_stamp) VALUES (%s, %s, NOW())"
            db_cursor.execute(insert_query, (user, points))

        db_cursor.execute("COMMIT")

    except Exception as e:
        print(f"Error updating database: {e}")

    finally:
        db_cursor.close()
        db_connection.close()

def main():
    try:
        server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server_socket.bind(('0.0.0.0', 8123))
        server_socket.listen(5)

        print("Python Server listening port 8123")

        while True:
            client_socket, addr = server_socket.accept()
            print(f"Accepted connection from {addr}")
            data = client_socket.recv(1024).decode('utf-8')
            user, action = data.split(',')

            if action == 'update':
                update_database(user, 1)
                print(f"Updated user {user}'s points.")

        time.sleep(30)

    except KeyboardInterrupt:
        pass

    finally:
        server_socket.close()

if __name__ == "__main__":
    main()