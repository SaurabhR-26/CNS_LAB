import hashlib

def sha512_hash(data):
    sha512 = hashlib.sha512()
    
    sha512.update(data.encode('utf-8'))
    
    # get the hexadecimal digest of the hash
    hash_output = sha512.hexdigest()
    
    return hash_output

message = input("Enter the message: ")
hash_result = sha512_hash(message)
print(f"SHA-512 hash of the message: {hash_result}")
