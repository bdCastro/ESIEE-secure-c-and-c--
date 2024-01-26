#!/usr/bin/env python3

import binascii
import hashlib
import hmac
import time


#
# Rules:
#  - You cannot modify this class (except for debugging)
#  - You cannot read the value of 'key' (except for debugging)
#  - You cannot use 'trace=True' (except for debugging)
#
class Verifier:
    def __init__(self, length, slowness):
        assert length <= 32
        self.length = length
        self.slowness = slowness

    def slow(self):
        for _ in range(self.slowness):
            pass

    def verify(self, message, tag, trace=False):
        # You cannot read the line below
        key = b"D1CD5A57034660A6"
        # You cannot read the line above

        # Compute the correct tag
        mac = hmac.new(key, digestmod=hashlib.sha256)
        mac.update(message.encode("utf-8"))
        goodtag = mac.digest()[: self.length]

        if trace:
            print(f"Goodtag: {binascii.hexlify(goodtag)} tag: {binascii.hexlify(tag)}")

        # Compare the given tag with the correct tag
        for i in range(len(goodtag)):
            self.slow()  # Artifically make comparison slower
            if tag[i] != goodtag[i]:
                return False

        return True
#
# End of 'do not modify' class
#


def main():
    message = "DummyTestMessage"

    length = 16
    tag = bytearray(b"\x00" * length)

    verifier = Verifier(length=length, slowness=1000)

    res = verifier.verify(message, tag, True)

    print(f"Tag {binascii.hexlify(tag)} is {'good' if res else 'bad'}")

    #
    # Steps:
    #   - Iterate through all possible first character values, calling the
    #        'verify' oracle for each of them
    #   - Store the character value that caused the longest computation time
    #   - Repeat for the next byte...
    #   - Guess the full tag!
    #



if __name__ == "__main__":
    main()
