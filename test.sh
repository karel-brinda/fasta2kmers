#! /usr/bin/env bash

set -e
set -o pipefail
set -u

./fasta2kmers ../01_simple_query/yeast.illumina-0.00.fra 1
