# DES

This is an implementation in C of DES (Data Encryption Standard), a broken cipher.
DES is a symmetric-key algorithm for the encryption. 
I implemented it with a padding system made of 0.


## Mode of operation

DES is a block cipher, this means that if a bit were to change, the whole block will change.
The DES mode of operation are:
- ECB (Electronic Code Book)
- CBC (Chain Block Coding)
- CFB (Cipher FeedBack)

I would implement all the mode of operation available for DES.
Now, I've implemented:
- [ECB mode](ECB)


## Other resources

If you want to learn something else about DES, you can consult:
- https://en.wikipedia.org/wiki/Data_Encryption_Standard
- http://page.math.tu-berlin.de/~kant/teaching/hess/krypto-ws2006/des.htm


## Check results

If you're not sure of the results, you can check them here http://des.online-domain-tools.com/.
