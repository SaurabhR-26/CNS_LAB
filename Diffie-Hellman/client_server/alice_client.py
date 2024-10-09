# Client (Alice)
import random
import socket

def mod_pow(base, exponent, modulus): 
    result = 1
    while exponent > 0:
        if exponent & 1:
            result = (result * base) % modulus
        exponent = exponent >> 1
        base = (base * base) % modulus
    return result

# Alice's client-side Diffie-Hellman implementation
def alice_diffie_hellman():
    # Step 1: Connect to Bob's server
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect(('localhost', 12345))
    
    # Step 2: Receive the prime, alpha, and Bob's public key from Bob
    data = client_socket.recv(1024).decode()
    p, alpha, bob_public = map(int, data.split(','))
    print(f"\nAlice received p: {p}, alpha: {alpha}, Bob's public key: {bob_public} \n")

    # Step 3: Generate Alice's private key
    alice_private = random.randint(2, p-2)

    # Step 4: Compute Alice's public key
    alice_public = mod_pow(alpha, alice_private, p)

    # Step 5: Send Alice's public key to Bob
    client_socket.send(str(alice_public).encode())

    # Step 6: Compute the shared secret
    alice_shared_secret = mod_pow(bob_public, alice_private, p)
    print(f"\nAlice's shared secret: {alice_shared_secret} \n")

    client_socket.close()

if __name__ == "__main__":
    alice_diffie_hellman()
