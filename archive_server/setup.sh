#!/bin/bash

# Update and install necessary packages
sudo apt-get update
sudo apt-get install -y mysql-server libmysqlclient-dev g++ cmake libbcrypt-dev libcrow-dev openssl

# Start MySQL service
sudo service mysql start

# Create the database and tables
mysql -u root -p <<EOF
CREATE DATABASE IF NOT EXISTS archive_db;
USE archive_db;
SOURCE database.sql;
EOF

# Compile the C++ code
mkdir -p build
cd build
cmake ..
make

echo "Setup complete. You can run the server with ./archive_server."