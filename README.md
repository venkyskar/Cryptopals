# Cryptopals
All the 7 steps of cryptopals website in different programming languages. 

## Step 1 
### Challenge 1: Convert Hex to Base64
  + Parse hex string into binary bytes.
  +  Encode them into base64.
  +   Avoiding buffer overflow.
  +   Ensuring only hex is accepted.
### Challenge 2: Fixed XOR
  + Takes two equal-length buffers (binary byte arrays).
  + Produces a third buffer where each byte is the XOR of the corresponding bytes in the two inputs.
  + Checks all buffers are of same length.
### Challenge 3: Single byte XOR cipher
  + Convert hex to raw bytes
  + For all possible values of the key (00 to FF)
      + XOR each byte of cipher text with key
      + check if it is matches to English characters
  + Score each result based on frequency of English letters
  + Return best looking key and plaintext
### Challenge 4: Detect single-character XOR 
  + Read the file
  + Convert hex to raw bytes
  + For all possible values of the key (00 to FF)
      + XOR each byte of cipher text with key
      + check if it is matches to English characters
  + Score each result based on frequency of English letters
  + Return best looking key and plaintext
### Challenge 5: Implementing Repeating key XOR
  + Read the file
  + Define a fixed key. In this case "ICE"
  + Iterate over each byte of plaintext
  + XOR each byte with key byte (cycled)
  + print/save the resutl in hex string
    + here max input length is considered to be 1024 to have control over the bytes we would like to read.
### Challenge 6: Breaking Repeating key XOR
  + Read the file
  + Decode base64 input
  + Guess the size
     + for all the key size fron 2 to 40
     + take the bytes from file equivalent to keysize
     + Compute the normalized hamming distance between those blocks (distance/Keysize)
     + the lowest normalised distance is the keysize
  + break the text into blocks
  + solve each block with single byte XOR attack using the scoring method from challenge 3
  + Reconstruct the full key
  + Decrypt the ciphertext
### Challenge 7: AES in ECB mode
              **TBD**
### Challenge 8: Detect AES-ECB
  + Read the file
  + Convert Hex to bytes
  + Divide into 16byte blocks
  + Count repeating blocks
       + ECB mode lacks randomization or chaining.
       + So it leaks structure: repeated plaintext leads to repeated ciphertext.
       + Detecting repeated 16-byte ciphertext blocks is a reliable ECB fingerprint.
  + Track Max repeats

## Step 2
### Challenge 9: Implement PKCS#7 padding
  + Determine how many bytes are needed to reach the next multiple of the block size. (N)
  + Append N bytes, all set to value N
  + Max padding  equal to block size. 
### Challenge 2: Fixed XOR
  + Takes two equal-length buffers (binary byte arrays).
  + Produces a third buffer where each byte is the XOR of the corresponding bytes in the two inputs.
  + Checks all buffers are of same length.
### Challenge 3: Single byte XOR cipher
  + Convert hex to raw bytes
  + For all possible values of the key (00 to FF)
      + XOR each byte of cipher text with key
      + check if it is matches to English characters
  + Score each result based on frequency of English letters
  + Return best looking key and plaintext
### Challenge 4: Detect single-character XOR 
  + Read the file
  + Convert hex to raw bytes
  + For all possible values of the key (00 to FF)
      + XOR each byte of cipher text with key
      + check if it is matches to English characters
  + Score each result based on frequency of English letters
  + Return best looking key and plaintext
### Challenge 5: Implementing Repeating key XOR
  + Read the file
  + Define a fixed key. In this case "ICE"
  + Iterate over each byte of plaintext
  + XOR each byte with key byte (cycled)
  + print/save the resutl in hex string
    + here max input length is considered to be 1024 to have control over the bytes we would like to read.
### Challenge 6: Breaking Repeating key XOR
  + Read the file
  + Decode base64 input
  + Guess the size
     + for all the key size fron 2 to 40
     + take the bytes from file equivalent to keysize
     + Compute the normalized hamming distance between those blocks (distance/Keysize)
     + the lowest normalised distance is the keysize
  + break the text into blocks
  + solve each block with single byte XOR attack using the scoring method from challenge 3
  + Reconstruct the full key
  + Decrypt the ciphertext
### Challenge 7: AES in ECB mode
              **TBD**
### Challenge 8: Detect AES-ECB
  + Read the file
  + Convert Hex to bytes
  + Divide into 16byte blocks
  + Count repeating blocks
       + ECB mode lacks randomization or chaining.
       + So it leaks structure: repeated plaintext leads to repeated ciphertext.
       + Detecting repeated 16-byte ciphertext blocks is a reliable ECB fingerprint.
  + Track Max repeats

