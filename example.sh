#! /usr/bin/env bash

set -e
set -o pipefail
set -u

./fasta2kmers <(curl -L "http://www.ncbi.nlm.nih.gov/sviewer/viewer.fcgi?db=nuccore&dopt=fasta&val=NC_001133") 31
