#include <stdio.h>
#include <zlib.h>

#include "kseq.h"


KSEQ_INIT(gzFile, gzread)


void split_seq(char *name, char *seq, int l, int k)
{
	char buffer[k+1];
	buffer[k]=0;
	for (int i=0; i< l-k+1; i++) {
		memcpy(buffer, seq+i, k*sizeof(char));
		printf(">%d.%s\n%s\n", i, name, buffer);
	}
}

int main(int argc, char *argv[])
{
	gzFile fp;
	kseq_t *seq;
	int l;
	if (argc != 3) {
		fprintf(stderr, "Usage: %s <in.seq> <k>\n", argv[0]);
		return 1;
	}
	int k=atoi(argv[2]);
	fp = gzopen(argv[1], "r");
	seq = kseq_init(fp);

	while ((l = kseq_read(seq)) >= 0) { // STEP 4: read sequence
		split_seq(seq->name.s, seq->seq.s, l, k);
	}
	kseq_destroy(seq);
	gzclose(fp);
	return 0;
}
