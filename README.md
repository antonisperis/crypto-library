# Cryptographic Library

A simple implementation of a cryptographic library written in C language.

## Features

- [One time pad.](#one-time-pad)
- [Ceasar cipher.](#ceasar-cipher)
- [Playfair cipher.](#playfair-cipher)
- [Affine cipher.](#affine-cipher)
- [Feistel cipher.](#feistel-cipher)


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

### Ceasar Cipher
For the encryption part a shifted array is used as a key, which contains all the digits and all the english alphabet characters, shifted based on the user's input (shift variable). Each one character of the plaintext corresponds to one array character.

```c
uint8_t *ceasar_encrypt(uint8_t *plaintext, unsigned short N, int size);
```

The reverse process is followed in order to extract the decyphered text.

```c
uint8_t *ceasar_decrypt(uint8_t *ciphertext, unsigned short N, int size);
```

### Playfair Cipher
The Playfair cipher encrypts pairs of letters (digraphs), instead of single letters as is the case with simpler substitution ciphers such as the Caesar Cipher. The key element of this cipher is a 5x5 grid that represents the key. In order to create the table, the letters of the key are placed in the grid, from left to right beginning from the first row. Then the rest of the alphabet’s letters are inserted in the grid alphabetically. Each letter is placed once in the grid. Since the 5x5 grid can only hold 25 characters J is usually omitted and treated as ‘I’.

```c
unsigned char **playfair_keymatrix(unsigned char *key);
```
```c
unsigned char *playfair_encrypt(unsigned char *plaintext, unsigned char **key);
```
The reverse process is followed in order to extract the decyphered text.
```c
unsigned char *playfair_decrypt(unsigned char *ciphertext, unsigned char **key);
```

### Affine Cipher
The affine cipher is a type of monoalphabetic substitution cipher where each letter is mapped to its numeric equivalent, encrypted using a simple mathematical function, and converted back to a letter. Each letter is encrypted with the function f(x) = (ax + b) mod m, where “a” is a constant, “b” is the magnitude of the shift and “x” is the letter to encrypt. The formula used, means that each letter encrypts to a single letter, thus, the cipher is essentially a standard substitution cipher with a rule governing which letter goes to which.

```c
uint8_t *affine_encrypt(uint8_t *plaintext, int size);
```

In order to decipher a letter affine cipher uses a function in the form of D(x) = a^-1 * (x - b) mod m, where a^-1 is the modular multiplicative inverse of a mod m. The multiplicative inverse of a only exists if a and m are coprime. Hence without the restriction on a, decryption might not be
possible. The letter x denotes the encrypted letter.

```c
uint8_t *affine_decrypt(uint8_t *ciphertext, int size);
```
