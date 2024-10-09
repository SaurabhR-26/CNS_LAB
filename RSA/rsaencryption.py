import rsa

# to generate the public and private key (not needed everytime)
'''try:
    public_key, private_key = rsa.newkeys(1024)

    with open("public.pem", "wb") as f:
        f.write(public_key.save_pkcs1("PEM"))

    with open("private.pem", "wb") as f:
        f.write(private_key.save_pkcs1("PEM"))
    
    print("Keys generated and saved successfully.")
except Exception as e:
    print(f"An error occurred: {e}")'''


with open("public.pem", "rb") as f:
    public_key = rsa.PublicKey.load_pkcs1(f.read())

with open("private.pem", "rb") as f:
    private_key = rsa.PrivateKey.load_pkcs1(f.read())


message = open("plaintext.txt", "r").read() # plaintext

encrypted_message = rsa.encrypt(message.encode(), public_key)

print("Encrypted message: ")
print(encrypted_message)

with open("encrypted.message", "wb") as f:
    f.write(encrypted_message)

decrypted_message = rsa.decrypt(encrypted_message, private_key) 

with open("decrypted.txt", "w") as f:
    f.write(decrypted_message.decode())

print("\nDecrypted message: \n" + decrypted_message.decode())

