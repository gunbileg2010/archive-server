import os
import base64

def generate_secret():
    return base64.urlsafe_b64encode(os.urandom(10)).decode('utf-8')

if __name__ == "__main__":
    secret = generate_secret()
    with open("secret.h", "w") as f:
        f.write(f"#define TWO_FA_SECRET \"{secret}\"\n")