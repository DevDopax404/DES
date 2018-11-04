/*	This function shifts the block <key> to left <shift> times
 * 
 * 	Parameters:
 * 	key:	block key
 * 	shifts:	number of shift
 */
block lshift(block key, short int shifts)
{
	int i, tmp_l, tmp_r;
	for (i = 0; i < shifts; i++)
	{
		tmp_l = get(key, 0);
		tmp_r = get(key, 28);
		key = key << 1;
		set(&key, 27, tmp_l);
		set(&key, 55, tmp_r);
	}
	return key;
}

/*	This function generates the 16 keys for the 16 rounds by the initial <key>
 * 
 * 	Parameter:
 * 	key: block key
 */
block *gen_keys(block key)
{	
	int i;
	block *mat;
	mat = (block*) calloc(16, sizeof(block));
	key = block_perm(key, 8, 7, pc1_example);
	for (i = 0; i < 16; i++)
	{
		key = lshift(key, shifts_example[i]);
		mat[i] = block_perm(key, 8, 6, pc2_example);
	}
	return mat;
}

/*	This function check the parity on the block <b64>
 * 
 * 	Parameter:
 * 	b64: block to check
 */
bool parity_check(block b64)
{
	int i, j;
	bool check;
	for (i = 0; i < 8; i++)
	{
		check = true;
		for (j = 0; j < 8; j++)
			if (get(b64, i * 8 + j))
				check = !check;
		if (!check)
			return false;
	}
	return true;
}
