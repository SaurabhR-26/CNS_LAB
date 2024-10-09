-------------------------- AES Modes of Operation --------------------------

1. ECB (Electronic Codebook) Mode:

    Simplest mode of operation
    Each block of plaintext is encrypted independently using the same key
    Advantages:

    Simple to implement
    Parallelizable (each block can be encrypted/decrypted independently)


    Disadvantages:

    Not secure for most applications
    Patterns in the plaintext are visible in the ciphertext


    Use case: Generally not recommended for secure communications


2. CBC (Cipher Block Chaining) Mode:

    Each block of plaintext is XORed with the previous ciphertext block before being encrypted
    Uses an Initialization Vector (IV) for the first block
    Advantages:

    Hides patterns in the plaintext
    A small change in the plaintext affects all following ciphertext blocks


    Disadvantages:

    Encryption cannot be parallelized
    Prone to padding oracle attacks if not implemented correctly


    Use case: General-purpose encryption, especially for data at rest


3. GCM (Galois/Counter Mode):

    Combines Counter mode for encryption with Galois mode for authentication
    Provides both confidentiality and authenticity
    Uses a nonce (similar to IV) and can include Additional Authenticated Data (AAD)
    Advantages:

    Provides encryption and authentication in one pass
    Can be parallelized for better performance
    Secure against several types of attacks


    Disadvantages:

    More complex to implement correctly
    Catastrophic loss of security if nonce is reused


    Use case: Recommended for most modern applications, especially for data in transit



- Comparison:

    Security:

        ECB < CBC < GCM
        ECB is considered insecure for most applications
        CBC is secure but can be vulnerable to certain attacks if not implemented correctly
        GCM provides the highest level of security among these three


    Performance:

        ECB > GCM > CBC
        ECB is fastest but at the cost of security
        GCM can be parallelized and is generally faster than CBC
        CBC is sequential, which can make it slower for large amounts of data


    Complexity:

        ECB < CBC < GCM
        ECB is simplest to implement
        CBC requires proper IV handling
        GCM is most complex, requiring careful nonce management and additional authenticated data handling



In practice, GCM is often recommended for new applications due to its combination of security and 
performance. CBC is still widely used and considered secure when implemented correctly. 
ECB should generally be avoided except in very specific circumstances where its limitations 
are understood and accepted.