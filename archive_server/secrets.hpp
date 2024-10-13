#ifndef SECRETS_HPP
#define SECRETS_HPP

#include <string>
#include <random>

std::string generate_secret() {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::string result;
    result.resize(32);

    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<> dist(0, sizeof(charset) - 2);

    for (auto& ch : result) {
        ch = charset[dist(engine)];
    }

    return result;
}

#endif