/*	This function pads the text to encrypt <txt> with NULL system (0)
 * 
 * 	Parameters:
 * 	txt: plain text
 * 	len: <txt> length (to assign)
 */
char *adj_str(const char *txt, int *len)
{
	char *adj;
	int pad, i;
	pad = strlen(txt);
	*len = (pad / 8 + (pad % 8) ? (1) : (0))) * 8;
	adj = (char*) calloc(*len, sizeof(char));
	strncpy(adj, txt, strlen(txt));
	for (i = pad; i < *len; i++) adj[i] = 0;
	return adj;
}

/*	This function returns the string <txt> converted to 64 bits block
 * 	from <pos> to <pos> + 8
 * 
 * 	Parameters:
 * 	txt: text to convert
 * 	pos: starting position
 */
block setblock(char *txt, int pos)
{
	block b = 0;
	int i;
	pos = pos * 8;
	for (i = pos; i < pos + 8; i++)
		to_bit(&b, (txt[i] >= 0) ? (txt[i]) : (256 + txt[i]), 8, (i - pos) * 8);
	return b;
}

/*	This function returns the block <to_perm> permuted with <pt> matrix
 * 	composed of <rows> rows and <cols> cols
 * 
 * 	Parameters:
 * 	to_perm: block of data
 * 	rows:	 number of rows
 * 	cols:	 number of columns
 * 	pt:		 permutation table
 */
block block_perm(block to_perm, int rows, int cols, short int pt[rows][cols])
{
	block pblock = 0;
	int i, j;
	for (i = 0; i < rows; i++)
		for (j = 0; j < cols; j++)
			set(&pblock, i * cols + j, get(to_perm, pt[i][j] - 1));
	return pblock;
}

/*	This function splits the 64 bits block <b64> into two sub-blocks
 * 	(32 bits each) <l> and <r>
 * 	
 * 	Parameters:
 * 	b64: starting block
 * 	l:	 left block
 * 	r:	 right block
 */
void split_block(block b64, block *l, block *r)
{
	*l = b64;
	*r = b64 << 32;
}
