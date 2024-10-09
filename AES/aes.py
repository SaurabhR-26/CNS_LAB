from Crypto.Cipher import AES
from Crypto.Util.Padding import pad, unpad
from Crypto.Random import get_random_bytes
import os
import sys

KEY_FILE = 'aes_encryption_key.bin'

def get_or_create_key():
    if os.path.exists(KEY_FILE):
        with open(KEY_FILE, 'rb') as file:
            return file.read()
    else:
        key = get_random_bytes(16)  # AES-128 
        with open(KEY_FILE, 'wb') as file:
            file.write(key)
        return key

key = get_or_create_key()

def encrypt(msg):
    cipher = AES.new(key, AES.MODE_ECB)
    padded_msg = pad(msg.encode('utf-8'), AES.block_size)
    return cipher.encrypt(padded_msg)

def decrypt(ciphertext):
    cipher = AES.new(key, AES.MODE_ECB)
    padded_msg = cipher.decrypt(ciphertext)
    try:
        return unpad(padded_msg, AES.block_size).decode('utf-8')
    except ValueError as e:
        print(f"Decryption error: {e}")
        return False

def perform_encryption():
    try:
        with open('plaintext.txt', 'r', encoding='utf-8') as file:
            message = file.read()

        ciphertext = encrypt(message)

        with open('ciphertext.txt', 'wb') as file:
            file.write(ciphertext)

        print(f'Encrypted message written to ciphertext.txt')
        print(f'Ciphertext length: {len(ciphertext)} bytes')

    except Exception as e:
        print(f"Encryption error: {e}")

def perform_decryption():
    try:
        with open('ciphertext.txt', 'rb') as file:
            ciphertext = file.read()

        print(f'Read ciphertext length: {len(ciphertext)} bytes')

        plaintext = decrypt(ciphertext)

        if not plaintext:
            print('Decryption failed!')
        else:
            with open('decryption.txt', 'w', encoding='utf-8') as file:
                file.write(plaintext)
            print(f'Decrypted message written to decryption.txt')
            print(f'Decrypted message length: {len(plaintext)} characters')

    except Exception as e:
        print(f"Decryption error: {e}")

if __name__ == "__main__":
    if len(sys.argv) != 2 or sys.argv[1] not in ['encrypt', 'decrypt']:
        print("Usage: python script.py [encrypt|decrypt]")
        sys.exit(1)

    print(f"Key used (hex): {key.hex()}")

    if sys.argv[1] == 'encrypt':
        perform_encryption()
    else:
        perform_decryption()