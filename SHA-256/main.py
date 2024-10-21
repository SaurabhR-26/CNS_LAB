import hashlib

def sha256_hash(data):
    sha256 = hashlib.sha256()
    
    sha256.update(data.encode('utf-8'))
    
    # get the hexadecimal digest of the hash
    hash_output = sha256.hexdigest()
    
    return hash_output

message = input("Enter the message: ")
hash_result = sha256_hash(message)
print(f"SHA-256 hash of the message: {hash_result}") #256 bits (64 hex characters)
