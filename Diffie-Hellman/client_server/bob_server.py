# Server (Bob)
import random
import socket
from sympy import randprime, primitive_root, is_primitive_root

def generate_large_prime(bits=1024):
    return randprime(2**(bits-1), 2**bits)

def mod_pow(base, exponent, modulus): 
    result = 1
    while exponent > 0:
        if exponent & 1:
            result = (result * base) % modulus
        exponent = exponent >> 1
        base = (base * base) % modulus
    return result

# Bob's server-side Diffie-Hellman implementation
def bob_diffie_hellman():
    # Step 1: Generate a large prime number p and primitive root alpha
    print("Bob Program Started")
    p = generate_large_prime(1024)
    with open("prime.txt", "w") as f:
        f.write(str(p))
    p = int(input("Enter the prime number:"))
    # print("Generated large prime")
    
    numbers = [2, 3, 5, 6, 7, 8, 10, 11, 12, 13, 14, 15]
    alpha = 2
# Check if each number is a primitive root modulo p
    # for number in numbers:
    #     print(f"Checking for primitive root {number} \n")
    #     if is_primitive_root(number, p):
    #         print(f"{number} is a primitive root of {p}")
    #         alpha = number
    #         break
    # print(f"Found primitive root {alpha} \n")

    # Step 2: Generate Bob's private key
    bob_private = random.randint(2, p-2)

    # Step 3: Compute Bob's public key
    bob_public = mod_pow(alpha, bob_private, p)

    # Step 4: Set up server to listen for Alice
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(('localhost', 12345))
    server_socket.listen(1)
    print("Bob is waiting for Alice to connect...")

    conn, addr = server_socket.accept()
    print(f"Connected to Alice at {addr} \n")

    # Step 5: Send prime, alpha, and Bob's public key to Alice
    conn.send(f"{p},{alpha},{bob_public}".encode())

    # Step 6: Receive Alice's public key
    alice_public = int(conn.recv(1024).decode())
    print(f"\nBob received Alice's public key: {alice_public} \n")

    # Step 7: Compute the shared secret
    bob_shared_secret = mod_pow(alice_public, bob_private, p)
    print(f"\nBob's shared secret: {bob_shared_secret} \n")

    conn.close()
    server_socket.close()

if __name__ == "__main__":
    bob_diffie_hellman()
