2. Set Permissions: Make the setup script executable.run

chmod +x setup.sh
./setup.sh


3. Run the Application: After the setup, run the compiled application.

./archive_server


5. User Registration: Modify the register_user function in the C++ code to allow new users to register and generate a 2FA secret using a library (e.g., libtotp).
