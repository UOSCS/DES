# DES

The main function in `main.c` has a `plaintext` variable and a `key` variable.

```c
int main(void)
{
    bits_64 plaintext = 0x0123456789ABCDEF;
    bits_64 key = 0x85E813540F0AB405;
    ...
}
```

Put the values you want in the variables above. However, the length must be 64 bits.

<br>

In the directory where `Makefile` is located,

```c
$ make
```

<br>

Finally, let's run the executable file created from the `Makefile`.

```c
$ ./DES
```

<br>

Output Example:

```c
Cipher Text: E5A951F59B3160C0
```