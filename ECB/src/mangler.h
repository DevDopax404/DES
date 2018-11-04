/*	This function returns the 32 bits block expanded into a 48 bits block
 * 
 *	Parameter:
 * 	b32: 32 bits block
 */
block expand(block b32)
{
	return block_perm(b32, 8, 6, exp_example);
}

/*	This function returns the correct starting 6 bits S-BOX value
 * 
 *	Parameters:
 * 	b48:  48 bits block
 * 	pos:  start position of 6 bits
 * 	sbox: i-th sbox
 */
short int get_sbox(block b48, int pos, short int sbox[4][16])
{
	int row, col;
	row = get(b48, pos) * 2 + get(b48, pos + 5);
	col = to_int(b48, 4, pos + 1);
	return sbox[row][col];
}

/*	This function returns the result of mangler function applied on
 * 	the n-th r, n-th l, (n + 1)-th scheduled key
 * 
 *	Parameters:
 * 	b32: 32 bits block
 * 	k:   i-th key
 */
block mangler(block b32, block k)
{
	int i;
	block man = 0, b48;
	b48 = expand(b32);
	b48 = b48 ^ k;
	for (i = 0; i < 8; i++)
		to_bit(&man, get_sbox(b48, i * 6, sbox_example[i]), 4, i * 4);
	man = block_perm(man, 8, 4, mangler_permutation_example);
	return man;
}
