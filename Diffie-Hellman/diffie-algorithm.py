import random
from sympy import randprime, primitive_root

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

def diffie_hellman():
    # Generate a large prime number p
    p = generate_large_prime(1024)
    
    # Choose a primitive root alpha
    alpha = primitive_root(p)  # 2, 3, 7 are good choices for alpha
    
    # Alice generates her private key
    alice_private = random.randint(2, p-2)
    
    # Bob generates his private key
    bob_private = random.randint(2, p-2)
    
    # Alice computes her public key
    alice_public = mod_pow(alpha, alice_private, p)
    
    # Bob computes his public key
    bob_public = mod_pow(alpha, bob_private, p)
    
    # Alice computes the shared secret
    alice_shared_secret = mod_pow(bob_public, alice_private, p)
    
    # Bob computes the shared secret
    bob_shared_secret = mod_pow(alice_public, bob_private, p)
    
    return {
        'prime': p,
        'primitive_root': alpha,
        'alice_private': alice_private,
        'alice_public': alice_public,
        'bob_private': bob_private,
        'bob_public': bob_public,
        'alice_shared_secret': alice_shared_secret,
        'bob_shared_secret': bob_shared_secret
    }

# Run the algorithm
result = diffie_hellman()

# Print the results
print(f"Prime (p): {result['prime']}")
print(f"Primitive Root (Generator) (alpha): {result['primitive_root']}")
print(f"Alice's private key: {result['alice_private']}")
print(f"Alice's public key: {result['alice_public']}")
print(f"Bob's private key: {result['bob_private']}")
print(f"Bob's public key: {result['bob_public']}")
print(f"Alice's shared secret: {result['alice_shared_secret']}")
print(f"Bob's shared secret: {result['bob_shared_secret']}")

# Verify that both shared secrets are the same
print(f"Shared secrets match: {result['alice_shared_secret'] == result['bob_shared_secret']}")