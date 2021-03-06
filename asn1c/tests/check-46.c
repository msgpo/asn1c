#undef	NDEBUG
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <assert.h>

#include <T.h>

uint8_t buf1[] = {
	32 | ((2 << 6) + 3),	/* [3], constructed */
	5,
	((2 << 6) + 5),	/* [5], primitive */
	3,	/* L */
  'a',
  'b',
  'c',
};

static void
check(uint8_t *buf, int size, size_t consumed) {
	T_t t, *tp;
	asn_dec_rval_t rval;

	tp = memset(&t, 0, sizeof(t));

	fprintf(stderr, "Buf %p\n", buf);
	rval = ber_decode(0, &asn_DEF_T, (void **)&tp, buf, size);
	fprintf(stderr, "Returned code %d, consumed %d\n",
		(int)rval.code, (int)rval.consumed);

	assert(rval.code == RC_OK);
	assert(rval.consumed == consumed);
}

int
main(int ac, char **av) {

	(void)ac;	/* Unused argument */
	(void)av;	/* Unused argument */

	check(buf1, sizeof(buf1), sizeof(buf1));

	return 0;
}

