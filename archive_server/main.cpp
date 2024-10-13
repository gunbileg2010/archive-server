#include <crow.h>
#include <iostream>
#include <string>
#include <mysql/mysql.h>
#include "bcrypt/BCrypt.hpp"
#include "secrets.hpp"
#include "encryption.hpp"

// Securely encrypt files
bool encrypt_file(const std::string& filepath, const std::string& secret_key) {
    // Encrypt using AES from `encryption.cpp`
    return aes_encrypt(filepath, secret_key);
}

// Database interaction (create_user, verify_user) functions...

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/register").methods("POST"_method)([](const crow::request& req) {
        auto body = crow::json::load(req.body);
        std::string username = body["username"].s();
        std::string password = body["password"].s();
        std::string clearance = body["clearance"].s();

        std::string secret = generate_secret();
        create_user(username, password, secret, clearance);

        return crow::response(200, "User created");
    });

    CROW_ROUTE(app, "/login").methods("POST"_method)([](const crow::request& req) {
        auto body = crow::json::load(req.body);
        std::string username = body["username"].s();
        std::string password = body["password"].s();

        if (verify_user(username, password)) {
            return crow::response(200, "Login successful");
        } else {
            return crow::response(401, "Invalid credentials");
        }
    });

    CROW_ROUTE(app, "/upload").methods("POST"_method)([](const crow::request& req) {
        auto body = crow::json::load(req.body);
        std::string file_path = body["file_path"].s();
        std::string clearance = body["clearance"].s();

        // Encrypt the file and save it
        std::string secret_key = "YOUR_ENCRYPTION_KEY";  // Get or generate an encryption key
        encrypt_file(file_path, secret_key);

        return crow::response(200, "File uploaded and encrypted");
    });

    app.port(8080).multithreaded().run();
}