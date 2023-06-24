# Cryptographic Library

A simple implementation of a cryptographic library written in C language.

## Features

- [One time pad.](#one-time-pad)
- [Ceasar's cipher.](#cesar's-cipher)
- [Playfair cipher.](#)
- [Affine cipher.](#)
- [Feistel cipher.](#)


## Compiling and running
A makefile is provided in the repo and can be run with the command:
```bash
make main
```


## API 
  
  
  
  
### One Time Pad
For the encryption part a random key is generated and every character in the plaintext is XORed with the key's corresponding character. 
```c
uint8_t *otp_encrypt(uint8_t *plaintext, uint8_t *key, int size);
```

The reverse process is followed in order to extract the decyphered text.

```c
uint8_t *otp_decrypt(uint8_t *ciphertext, uint8_t *key, int size);
```

### Ceasar's cipher
For the encryption part a shifted array is used as a key, which contains all the digits and all the english alphabet characters, shifted based on the user's input (shift variable). Each one character of the plaintext corresponds to one array character.

```c
uint8_t *ceasar_encrypt(uint8_t *plaintext, unsigned short N, int size);
```

The reverse process is followed in order to extract the decyphered text.


