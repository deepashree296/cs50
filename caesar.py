import sys
from cs50 import get_string

def main():
    # check for args length
    if len(sys.argv) != 2:
        print("Usage: ./caesar k")
        sys.exit(1)
    else:
        encrypt()


def encrypt():
        plaintext = get_string("plaintext: ")
        ciphertext = ""
        key = int(sys.argv[1])
        # encrypt only if letter
        for i in plaintext:
            if i.isalpha():
                # forming cipher string
                ciphertext += ciphervalue(i, key)
            else:
                ciphertext += i
        print("ciphertext: {}".format(ciphertext))


def ciphervalue(i, key):
    # encrypts each character to its cipher value
    if i.islower():
        letter = ord('a')
    else:
        letter = ord('A')
    cipherindex = (ord(i) - letter + key) % 26
    return chr(cipherindex + letter)


if __name__ == "__main__":
    main()