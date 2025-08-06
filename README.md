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
   
