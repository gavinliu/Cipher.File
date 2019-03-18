# Cipher.File

### Download

```bash
git clone git@github.com:gavinliu/Cipher.File.git
git submodule init
git submodule update
```

### Compile

```bash
gcc tiny-AES-c/aes.c file_aes.c file_aes_encrypter.c -o file_aes_encrypter
gcc tiny-AES-c/aes.c file_aes.c file_aes_decrypter.c -o file_aes_decrypter
```

### Usage

```bash
./file_aes_encrypter -i <file> -o <file> -k <keycode>
./file_aes_decrypter -i <file> -o <file> -k <keycode>
```

### License

The Unlicense
