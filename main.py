import socket

HOST = "127.0.0.1"
PORT = 12346

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind((HOST, PORT))
server.listen()

print(f"Сервер запущен на {HOST}:{PORT}")

while True:
    client_socket, client_address = server.accept()
    print(f"[+] Клиент подключился: {client_address}")

    try:
        while True:
            data = client_socket.recv(1024)

            if not data:
                print(f"[-] Клиент отключился: {client_address}")
                break

            print(f"Получено {len(data)} байт: {data[:30]}...")

            #client_socket.sendall(b"OK")

    except ConnectionResetError:
        print(f"[!] Соединение разорвано клиентом: {client_address}")

    except Exception as e:
        print(f"[!] Ошибка: {e}")

    finally:
        client_socket.close()
        print("[i] Сокет клиента закрыт\n")
