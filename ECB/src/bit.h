/*	This function returns the <pos>-th bit in the block <n>
 * 
 *	Parameters:
 * 	b64: 64 bits block
 * 	pos: the position of bit interested
 */
int get(block b64, int pos)
{
	return (b64 >> (63 - pos)) & 1U;
}

/*	This function sets the <pos>-th bit in the block <n> with the value <val>
 * 
 *	Parameters:
 * 	b64: 64 bits block
 * 	pos: the position of bit interested
 * 	val: value
 */
void set(block *b64, int pos, int val)
{
	if (val)
		*b64 |= 1UL << (63 - pos);
	else
		*b64 &= ~(1UL << (63 - pos));
}

/*	This function converts the value <val> to binary and puts it in
 * 	<dest> starting from position <pos> with dimension <dim>
 * 
 *	Parameters:
 * 	dest: 64 bits block
 * 	val:  value
 * 	dim:  dimension
 * 	pos:  starting position
 */
void to_bit(block *dest, int val, int dim, int pos)
{
	int i;
	for (i = 0; i < dim; i++)
		if (val - pow(2, dim - 1 - i) >= 0)
		{
			val -= pow(2, dim - 1 - i);
			set(dest, pos + i, 1);
		}
}

/*	This function converts the <dim> bit, starting from <pos>, of <from>
 * 	to int and returns it
 * 
 *	Parameters:
 * 	from: 64 bits block
 * 	dim:  dimension
 * 	pos:  starting position
 */
int to_int(block from, int dim, int pos)
{
	int i, res = 0;
	for (i = 0; i < dim; i++)
		res += get(from, pos + i) * pow(2, dim - 1 - i);
	return res;
}
