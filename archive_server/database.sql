CREATE DATABASE IF NOT EXISTS archive_db;

USE archive_db;

CREATE TABLE users (
    id INT PRIMARY KEY AUTO_INCREMENT,
    username VARCHAR(255) UNIQUE NOT NULL,
    password_hash VARCHAR(255) NOT NULL,
    2fa_secret VARCHAR(255) NOT NULL,
    clearance ENUM('Alice', 'Beta', 'Delta', 'Guest') DEFAULT 'Guest'
);

CREATE TABLE archive (
    id INT PRIMARY KEY AUTO_INCREMENT,
    user_id INT,
    file_path TEXT,
    clearance ENUM('Alice', 'Beta', 'Delta', 'Guest') DEFAULT 'Guest',
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    encrypted_file_path TEXT,
    FOREIGN KEY (user_id) REFERENCES users(id)
);

CREATE TABLE login_attempts (
    id INT PRIMARY KEY AUTO_INCREMENT,
    user_id INT,
    attempted_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    status ENUM('SUCCESS', 'FAILURE'),
    FOREIGN KEY (user_id) REFERENCES users(id)
);