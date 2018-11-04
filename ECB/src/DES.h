#include <stdlib.h>		/* calloc(), free() */
#include <stdbool.h>	/* Only for using 'bool' type */
#include <string.h>		/* strlen(), strncpy() */
#include <assert.h>		/* assert() */
#include <math.h>		/* pow() */

typedef long long unsigned int block;
typedef enum option_tmp {ENCRYPT = true, DECRYPT = false} option;

#include "bit.h"			// allows bits control
#include "matrix.h"			// gives some matrices helpful
#include "support.h"		// contains some generic functions
#include "mangler.h"		// contains all needed to execute mangler function
#include "key_schedule.h"	// contains all needed for scheduling the 16 keys

/*	This function executes DES algorithm on single block <b64> of 64 bits
 * 
 * 	Parameters:
 *	b64: block of 64 bits to encrypt / decrypt
 * 	mat: vector that contains the 16 keys
 * 	opt: ENCRYPT -> encrypt
 * 		 DECRYPT -> decrypt 
 */
block des_ecb_on_block(block b64, block *keys, option opt)
{
	block l, r, com;
	int round, step;
	b64 = block_perm(b64, 8, 8, ip_example);		// Initial Permutation
	split_block(b64, &l, &r);						// B (64 bits) = L (32 bits) + R (32 bits)
	// If we encrypt, the rounds will go from 1 to 16, otherwise from 16 to 1, so:
	step = opt ? 1 : -1;
	for (round = opt ? 0 : 15; (opt) ? (round < 16) : (round >= 0); round += step)
	{
		com = r;
		r = mangler(r, keys[round]) ^ l;			// R = Mangler(R(i), K(i + 1)) XOR L(i)
		l = com;									// L(i + 1) = R(i)
	}
	l = r + (l >> 32);								// Switching LR into RL
	l = block_perm(l, 8, 8, inv_ip_example);		// Final Permutation
	return l;
}

/*	This function controls if it's possible to execute DES with
 * 	given parameters <txt>, <key>
 * 	Parameters:
 *	txt: plain text to encrypt
 * 	key: cipher key
 * 	opt: ENCRYPT -> encrypt
 * 		 DECRYPT -> decrypt 
 */
int check(char *txt, char *key, option opt)
{
	int len;
	assert(strlen(key) == 8);
	if (opt)
	{
		txt = adj_str(txt, &len);			// Padding
		assert(len % 8 == 0);				// I don't trust the functions I write .-.
	}
	else
	{
		assert(strlen(txt) % 8 == 0);		// Check text lenght
		len = strlen(txt);
	}
	//assert(parity_check(setblock(key, 0))); Check the key, not necessary 
	return len;
}


/*	This function inizializes <keyblock> (<key> from string to 'block' type)
 * 	and <mat>, the matrix that contains all the 16 keys for the 16 rounds
 * 
 * 	Parameters:
 * 	keyblock: a pointer to store the key
 * 	mat:	  a vector to store all 16 keys
 * 	key:	  cipher key
 */
void init(block *keyblock, block **mat, char *key)
{
	*keyblock = setblock(key, 0);	// Set key
	*mat = gen_keys(*keyblock);		// Set matrix of 16 keys
}

/*	This function split text in blocks of 64 bits each and store result
 * 
 * 	Parameters:
 * 	txt: plain text to encrypt
 *  len: <txt> length
 * 	mat: matrix of 16 keys
 * 	opt: ENCRYPT -> encrypt
 * 		 DECRYPT -> decrypt 
 */
char *execute_des_ecb(char *txt, int len, block *mat, option opt)
{
	int i, j;
	block b;
	char *res;
	res = (char*) calloc(len + 1, sizeof(char));
	res[len] = 0;
	for (i = 0; i < len / 8; i++)							// Split text in block of 8 bytes (64 bits)
	{
		b = setblock(txt, i);								// Set current block
		b = des_ecb_on_block(b, mat, opt);					// Execute DES on current block
		for (j = 0; j < 8; j++)
			res[i * 8 + j] = (char) to_int(b, 8, j * 8);	// Store result
	}
	free(mat);
	return res;
}

/*	This function calls all functions needed to execute DES
 * 
 * 	Parameters:
 *	txt: plain text to encrypt
 * 	key: cipher key
 * 	opt: ENCRYPT -> encrypt
 * 		 DECRYPT -> decrypt 
 */
char *des_ecb(char *txt, char *key, option opt)
{
	block keyblock, *mat;
	int len;
	len = check(txt, key, opt);
	init(&keyblock, &mat, key);
	return execute_des_ecb(txt, len, mat, opt);
}

