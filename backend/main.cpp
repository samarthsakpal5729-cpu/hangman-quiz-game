#include <iostream>
#include <string>
#include <winsock2.h>
#include "Game.h"

using namespace std;

int main()
{
    WSADATA wsa;

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        cout << "Winsock startup failed!" << endl;
        return 1;
    }

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket == INVALID_SOCKET)
    {
        cout << "Socket creation failed!" << endl;
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddress;

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(8080);

    if (bind(
        serverSocket,
        (sockaddr*)&serverAddress,
        sizeof(serverAddress)
    ) == SOCKET_ERROR)
    {
        cout << "Bind failed!" << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    if (listen(serverSocket, 5) == SOCKET_ERROR)
    {
        cout << "Listen failed!" << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    cout << "======================================" << endl;
    cout << "       C++ HANGMAN BACKEND            " << endl;
    cout << "======================================" << endl;
    cout << "Server running at:" << endl;
    cout << "http://127.0.0.1:8080" << endl;
    cout << "Waiting for browser..." << endl;

    while (true)
    {
        SOCKET clientSocket = accept(serverSocket, NULL, NULL);

        if (clientSocket == INVALID_SOCKET)
        {
            cout << "Client connection failed!" << endl;
            continue;
        }

        char buffer[4096];

        int bytesReceived = recv(
            clientSocket,
            buffer,
            sizeof(buffer) - 1,
            0
        );

        if (bytesReceived > 0)
        {
            buffer[bytesReceived] = '\0';

            cout << "\nBrowser request received!" << endl;

            Question question(
                "Which programming language is used for OOP?",
                "JAVA",
                "Programming"
            );

            string responseBody =
                "{\"status\":\"success\","
                "\"message\":\"C++ Backend Connected!\","
                "\"question\":\"" + question.getQuestion() + "\","
                "\"category\":\"" + question.getCategory() + "\","
                "\"lives\":5,"
                "\"score\":0}";

            string response =
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: application/json\r\n"
                "Access-Control-Allow-Origin: *\r\n"
                "Content-Length: " +
                to_string(responseBody.length()) +
                "\r\n"
                "Connection: close\r\n"
                "\r\n" +
                responseBody;

            send(
                clientSocket,
                response.c_str(),
                response.length(),
                0
            );
        }

        closesocket(clientSocket);

        cout << "Browser connection completed!" << endl;
        cout << "Waiting for browser..." << endl;
    }

    closesocket(serverSocket);
    WSACleanup();

    return 0;
}