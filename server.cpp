#include <iostream>
#include <string>
#include <vector>
#include <winsock2.h>

#include "Question.h"

using namespace std;

#pragma comment(lib, "ws2_32.lib")

int main()
{
    WSADATA wsa;

    // Start Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        cout << "Winsock startup failed!" << endl;
        return 1;
    }

    // Create server socket
    SOCKET serverSocket = socket(
        AF_INET,
        SOCK_STREAM,
        0
    );

    if (serverSocket == INVALID_SOCKET)
    {
        cout << "Socket creation failed!" << endl;

        WSACleanup();

        return 1;
    }

    // Allow address reuse
    int opt = 1;

    setsockopt(
        serverSocket,
        SOL_SOCKET,
        SO_REUSEADDR,
        (char*)&opt,
        sizeof(opt)
    );

    // Server address
    sockaddr_in serverAddress{};

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(8080);

    // Bind
    if (bind(
        serverSocket,
        (sockaddr*)&serverAddress,
        sizeof(serverAddress)
    ) == SOCKET_ERROR)
    {
        cout << "Bind failed!" << endl;
        cout << "Error: " << WSAGetLastError() << endl;

        closesocket(serverSocket);
        WSACleanup();

        return 1;
    }

    // Listen
    if (listen(serverSocket, 5) == SOCKET_ERROR)
    {
        cout << "Listen failed!" << endl;

        closesocket(serverSocket);
        WSACleanup();

        return 1;
    }

    // Create Question objects
    vector<Question> questions;

    questions.push_back(
        Question(
            "Which programming language is used for OOP?",
            "JAVA",
            "Programming"
        )
    );

    questions.push_back(
        Question(
            "Which language is known for web page structure?",
            "HTML",
            "Web Development"
        )
    );

    questions.push_back(
        Question(
            "Which operating system is open source?",
            "LINUX",
            "Operating System"
        )
    );

    questions.push_back(
        Question(
            "What is used to store multiple values in C++?",
            "ARRAY",
            "Programming"
        )
    );

    questions.push_back(
        Question(
            "Which language is popular for artificial intelligence?",
            "PYTHON",
            "Artificial Intelligence"
        )
    );

    cout << endl;
    cout << "========================================" << endl;
    cout << "       C++ HANGMAN QUIZ BACKEND        " << endl;
    cout << "========================================" << endl;

    cout << "Server running at:" << endl;
    cout << "http://127.0.0.1:8080" << endl;

    cout << "========================================" << endl;
    cout << "Waiting for browser..." << endl;

    // Server loop
    while (true)
    {
        SOCKET clientSocket = accept(
            serverSocket,
            NULL,
            NULL
        );

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

            string request(buffer);

            cout << endl;
            cout << "Browser request received!" << endl;

            string responseBody;

            // ==========================
            // GET /questions
            // ==========================

            if (request.find("GET /questions") != string::npos)
            {
                responseBody =
                    "{\"status\":\"success\",\"questions\":[";

                for (int i = 0; i < questions.size(); i++)
                {
                    responseBody +=
                        "{\"question\":\"" +
                        questions[i].getQuestion() +
                        "\",\"answer\":\"" +
                        questions[i].getAnswer() +
                        "\",\"category\":\"" +
                        questions[i].getCategory() +
                        "\"}";

                    if (i < questions.size() - 1)
                    {
                        responseBody += ",";
                    }
                }

                responseBody += "]}";
            }

            // ==========================
            // GET /
            // ==========================

            else
            {
                responseBody =
                    "{\"status\":\"success\","
                    "\"message\":\"C++ Backend Connected!\","
                    "\"question\":\"" +
                    questions[0].getQuestion() +
                    "\","
                    "\"category\":\"" +
                    questions[0].getCategory() +
                    "\","
                    "\"lives\":5,"
                    "\"score\":0}";
            }

            // HTTP Response
            string response =
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: application/json\r\n"
                "Access-Control-Allow-Origin: *\r\n"
                "Access-Control-Allow-Methods: GET, POST, OPTIONS\r\n"
                "Access-Control-Allow-Headers: Content-Type\r\n"
                "Content-Length: " +
                to_string(responseBody.length()) +
                "\r\n"
                "Connection: close\r\n"
                "\r\n" +
                responseBody;

            send(
                clientSocket,
                response.c_str(),
                (int)response.length(),
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