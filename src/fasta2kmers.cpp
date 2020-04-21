#include <errno.h>
#include <stdio.h>
#include <zlib.h>

#include "kseq.h"

KSEQ_INIT(gzFile, gzread)

void split_seq(char *name, char *seq, int l, int k)
{
    char buffer[k + 1];
    buffer[k] = 0;
    for (int i = 0; i < l - k + 1; i++)
    {
        memcpy(buffer, seq + i, k * sizeof(char));
        printf(">%d@%s\n%s\n", i+1, name, buffer);
    }
}

int main(int argc, char *argv[])
{
    gzFile fp;
    kseq_t *seq;
    int l;
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <in.seq> <k>\n", argv[0]);
        return 1;
    }

    int k = atoi(argv[2]);
    char *fn = argv[1];
    fp = gzopen(fn, "r");
    if (fp == nullptr)
    {
        fprintf(stderr, "Couldn't open %s : %s\n", fn, errno ? strerror(errno) : "Out of memory");
        return 1;
    }

    seq = kseq_init(fp);
    while ((l = kseq_read(seq)) >= 0)
    {
        split_seq(seq->name.s, seq->seq.s, l, k);
    }
    kseq_destroy(seq);
    gzclose(fp);
    return 0;
}
