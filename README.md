# Cipher.File

> This is encrypt & decrypt file tools based by AES

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

#### example

```bash
$ ./file_aes_encrypter -i README.md -o README.cipher.md -k 1234567890abcdef
```

```bash
$ ./file_aes_decrypter -i README.cipher.md -o README.new.md -k 1234567890abcdef
```

```bash
$ md5sum README.md
9b4cd1667aff53a90c1d66a2abfb4390  README.md

$ md5sum README.cipher.md
bf082373be67a2c719e66da35c3f30b3  README.cipher.md

$ md5sum README.new.md
9b4cd1667aff53a90c1d66a2abfb4390  README.new.md
```

### License

The Unlicense
