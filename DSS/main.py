from cryptography.hazmat.primitives.asymmetric import dsa
from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.primitives.asymmetric.utils import Prehashed
from cryptography.exceptions import InvalidSignature

private_key = dsa.generate_private_key(key_size=1024)
public_key = private_key.public_key()

# Sign a message with the private key
def sign_message(message, private_key):
    # Hash the message and sign it
    signature = private_key.sign(
        message.encode('utf-8'),
        hashes.SHA256()  # Hash algorithm (can also use SHA1, SHA224, SHA384, SHA512)
    )
    return signature

# Verify the signature with the public key
def verify_signature(message, signature, public_key):
    try:
        public_key.verify(
            signature,
            message.encode('utf-8'),
            hashes.SHA256()
        )
        print("Signature is valid.")
        return True
    except InvalidSignature:
        print("Signature is invalid!")
        return False

message = "This is a secure message."
print("Original Message:", message)

signature = sign_message(message, private_key)
print("Signature:", signature)

is_valid = verify_signature(message, signature, public_key)
print("Verification Result:", is_valid)
