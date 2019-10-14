---------------------
CSCE 121H - Fall 2019
Project 5 - Genomics
due: Mon, Oct 14, 8:00am
---------------------

The objective of this assignment is to write a C++ program for
analyzing the genome of bacterial organisms.  Example files, included
the genome sequence (*.fasta) and annotation (*.prot_table) will be
provided on the course web page.  This project will give you practice
reading and processing datafiles in C++, as well as using structs and
stringstreams.

The assignment has 3 stages.

Stage 1 - working with genome sequences.
-------

Write a function called read_genome() that takes a filename as argument
and returns a string representing the genome sequence (see format below).
Then write a function analyze_genome() that calculates some basic statistics,
including genome length and GC content (percentage of G and Cs).

Genome sequences have a complex structure.  Most genes have random-looking
nucleotide sequences. However, some parts
of a genome might be considered "low-complexity", with short repeats of 1-3
nucleotides.  As an example, identify the longest homopolymer (repeat of the
same nucleotide) in the genome sequence.  You probably want this function
to return 2 values: the location (coordinate) and the length of the homopolymer.

> genomics Mycobacterium_tuberculosis.fasta
reading: NC_000962.3 Mycobacterium tuberculosis H37Rv, complete genome
length = 4411532 bp
GC content = 65.6%
longest homopolymer: CCCCCCCCC (len=9 bp) at coord 854252


Stage 2 - working with gene annotations (prot_tables).
-------

Next, write a function read_genes() that reads in the annotation of a genome
(in the format of a "prot_table", see below).  The prot_tables contains
information on each gene.  You will probably want to define a struct (Gene)
that holds this information.  Then you reader function can return a vector of
Genes, with a signature like this:

vector<Gene> read_prot_table(char* fname);

After reading in the prot_table, print out some statistics on the genes,
including number of genes, smallest and largest, and mean gene size in bp.
(length of nucleotide sequences is measured in 'bp', which is base pairs).
Also, calculate the "genome fraction", which is the ratio of the sum of the
gene lengths to the total genome size.  Most bacteria are fairly compact,
meaning that most of the genome sequence is occupied by coding regions.  For
the intergenic regions (nucleotides sequences between successive genes),
determine the largest "gap" (occasionally, these contain structural RNAs,
which are not translated into proteins).  Identify the genes surrounding the
largest gap.  (Report the same info for the shortest gap, which is sometimes
negative, because genes occasionally overlap.)

> genomics Mycobacterium_tuberculosis.fasta Mycobacterium_tuberculosis.prot_table 
reading: NC_000962.3 Mycobacterium tuberculosis H37Rv, complete genome
length = 4411532 bp
GC content = 65.6%
longest homopolymer: CCCCCCCCC (len=9 bp) at coord 854252
num genes: 3906
gene sizes: [90,12456], mean=1013.4 bp, stdev=796.4
coding fraction: 89.7%
mean size of intergenic regions: 116.0 bp
largest intergenic region: 5558 bp (after Rv1315/murA)
smallest intergenic region: -444 bp (after Rv2943A/-)
longest homopolymer: CCCCCCCCC (len=9 bp) at coord 854252, after Rv0759c/-
                                                           ^^^^^^^^^^^^^^^

Finally, now that you have both the genome and the annotation, write a wrapper
around your function for calculating the longest homopolymer sequence, and
identify which gene it occurs in, or the surrounding genes if it occurs in an
intergenic region, as shown above.  


Stage 3 - Translating genes into amino acid sequences.
-------

If the user includes a 3rd argument on the command line, either the name or id
of a gene, then print out the nucleotide sequence of the gene and its
translation into an amino acid sequence.

First, you will want to write a simple utility function called print_seq()
that prints out a sequence of arbitrary length, in lines of a fixed width
(e.g. 70 bp), along with a counter.

Recall that genes are transcribed from the genome as mRNA transcripts
(typically 1-10kb long, effectively copying the information, but with
U substituted for T), and are then translated into proteins at
ribosomes.  The ribosome reads the sequence 3 nucleotides at a time as
codons (non-overlapping), and then selects one of the 20 standard
amino acids to append onto the growing polypeptide chain (download
codons.txt from course web site and link in into your project).  The
standard start codons are ATG, GTG, and TTG, (Met, Val, and Leu), and
the standard stop codons are TAG, TGA, and TTA.  You can extract the
sequence for the target gene based on its coordinates (start and end)
in the Gene struct from the prot_table.  Finally, genes that occur on
the '-' strand of the genome must be reverse-complemented before
translating them. (reverse the sequence, and substitute A->T, T->A,
G->C, C->G).  You can check your amino acid translations on Uniprot
(here is the example for Rv0018c:
https://www.uniprot.org/uniprot/P9WHW5).  (Note that the first amino
acid is always changed to M (methionine) by the bacteria, regardless
of the start codon.)

> genomics Mycobacterium_tuberculosis.fasta Mycobacterium_tuberculosis.prot_table Rv0018c
reading: NC_000962.3 Mycobacterium tuberculosis H37Rv, complete genome
length = 4411532 bp
GC content = 65.6%
longest homopolymer: CCCCCCCCC (len=9 bp) at coord 854252
num genes: 3906
gene sizes: [90,12456], mean=1013.4 bp, stdev=796.4
coding fraction: 89.7%
mean size of intergenic regions: 116.0 bp
largest intergenic region: 5558 bp (after Rv1315/murA)
smallest intergenic region: -444 bp (after Rv2943A/-)
longest homopolymer: CCCCCCCCC (len=9 bp) at coord 854252, after Rv0759c/-
      1 GTGGCGCGCGTGACCCTGGTCCTGCGATACGCGGCGCGCAGCGATCGCGGCTTGGTACGCGCCAACAACG
     71 AAGACTCGGTCTACGCTGGGGCACGGCTATTGGCCCTGGCCGACGGCATGGGTGGGCATGCGGCCGGCGA
    141 GGTGGCGTCCCAGTTGGTGATTGCCGCATTGGCCCATCTCGATGACGACGAGCCCGGTGGCGATCTGCTG
    211 GCCAAGCTGGATGCCGCGGTGCGCGCCGGCAACTCGGCTATCGCAGCGCAAGTCGAGATGGAGCCCGATC
    281 TCGAAGGCATGGGTACCACGCTCACCGCAATCCTGTTCGCGGGCAACCGGCTCGGCCTGGTGCATATCGG
    351 TGACTCGCGCGGTTACCTGCTGCGCGACGGTGAGCTGACGCAGATCACCAAGGACGACACGTTTGTCCAA
    421 ACGCTGGTCGACGAAGGCCGGATCACCCCGGAGGAGGCGCACAGCCACCCGCAACGCTCGTTGATCATGC
    491 GGGCGTTGACCGGCCATGAGGTCGAACCGACGCTGACCATGCGAGAAGCCCGCGCCGGTGATCGTTACCT
    561 GCTGTGCTCGGACGGGTTGTCCGATCCGGTTAGCGATGAAACTATCCTCGAGGCCCTGCAGATCCCCGAG
    631 GTTGCCGAGAGCGCTCACCGCCTCATTGAACTGGCGCTGCGCGGCGGCGGCCCCGACAACGTCACTGTCG
    701 TCGTCGCCGACGTCGTCGACTACGACTACGGCCAGACCCAACCGATTCTGGCCGGGGCGGTCTCAGGCGA
    771 CGACGACCAACTGACCCTGCCCAACACCGCCGCCGGCCGGGCCTCTGCCATCAGCCAGCGCAAGGAGATC
    841 GTTAAACGCGTTCCGCCACAGGCCGATACATTCAGTCGGCCACGGTGGTCGGGCCGACGGCTAGCATTCG
    911 TTGTCGCACTGGTGACCGTGCTGATGACTGCGGGCCTGCTCATTGGTCGCGCGATCATCCGCAGCAACTA
    981 CTACGTAGCGGACTACGCCGGCAGCGTGTCCATCATGCGGGGGATTCAAGGGTCGCTACTGGGCATGTCC
   1051 CTGCACCAGCCTTACCTGATGGGCTGCCTCAGCCCGCGTAACGAGCTGTCGCAGATCAGCTACGGACAGT
   1121 CTGGGGGCCCTCTCGACTGCCATCTGATGAAACTGGAGGATCTGCGACCGCCGGAGCGCGCACAGGTTCG
   1191 GGCCGGTCTCCCGGCCGGCACTCTCGATGACGCCATCGGGCAGTTGCGCGAACTGGCGGCCAACTCCCTG
   1261 CTGCCGCCTTGCCCGGCGCCGCGTGCCACGTCCCCGCCCGGGCGCCCGGCCCCACCCACCACCAGCGAGA
   1331 CAACCGAACCAAACGTCACCTCCTCGCCAGCCTCTCCATCACCCACCACCTCCGCGCCGGCCCCCACCGG
   1401 AACTACTCCTGCCATCCCCACGAGTGCCTCCCCGGCAGCGCCCGCGTCGCCGCCGACGCCTTGGCCCGTC
   1471 ACCAGCTCGCCGACGATGGCCGCACTTCCGCCACCCCCGCCTCAGCCGGGCATCGACTGCCGGGCGGCGG
   1541 CATGA

      1 VARVTLVLRYAARSDRGLVRANNEDSVYAGARLLALADGMGGHAAGEVASQLVIAALAHLDDDEPGGDLL
     71 AKLDAAVRAGNSAIAAQVEMEPDLEGMGTTLTAILFAGNRLGLVHIGDSRGYLLRDGELTQITKDDTFVQ
    141 TLVDEGRITPEEAHSHPQRSLIMRALTGHEVEPTLTMREARAGDRYLLCSDGLSDPVSDETILEALQIPE
    211 VAESAHRLIELALRGGGPDNVTVVVADVVDYDYGQTQPILAGAVSGDDDQLTLPNTAAGRASAISQRKEI
    281 VKRVPPQADTFSRPRWSGRRLAFVVALVTVLMTAGLLIGRAIIRSNYYVADYAGSVSIMRGIQGSLLGMS
    351 LHQPYLMGCLSPRNELSQISYGQSGGPLDCHLMKLEDLRPPERAQVRAGLPAGTLDDAIGQLRELAANSL
    421 LPPCPAPRATSPPGRPAPPTTSETTEPNVTSSPASPSPTTSAPAPTGTTPAIPTSASPAAPASPPTPWPV
    491 TSSPTMAALPPPPPQPGIDCRAAA*



Genomic file formats
--------------------

Fasta files:

Fasta files store the nucleotide sequence of genomes.  The first line
is always a header, starting with '>' and following by identifying
information, such as strain name and Genbank accession number.  The
sequence is split over multiple lines of arbitrary length, but should
be concatenated.  Also, most geneomes are implicitly circular (so then
end connects to the beginning), but we treat them as linear (usually
starting at the origin of replication) for simplicity.  The sequence
usually contains only A,G,C,T, but occasionally other characters
like N, or lower-case (a,g,c,t).

We only have to represent the sequence on the + strand of the
double-helix, because the sequence on the negative strand can be
derived by complementarity (base-pairing).


Prot_tables:

These represent the "annotation" of a genome in terms of genes
(specifically, coding sequences that get translated into proteins).
Prot_tables are based on an older Genbank format that is not used
frequently (has been replaced by .gff files).  I generated these
prot_tables by extracting the information from .gb files, which
contain a lot more information (including rRNAs and tRNAs).

Genes are also known as ORFs (open reading frames), which refers to
regions of nucleotides not interrupted by a stop codon.  ORFs start
with start codon and end with a stop codon.  ORFs can occur on either
the + or - strand.  Typically ORFs do not overlap, although
occasionally they might overlap by a few nucleotides.  For genes
on the negative strand, you must reverse-complement them before
translating into amino acids.  The regions between ORFs are known as
intergenic regions (IGRs).  While IGRs are often non-functional, they
sometimes contain motifs that regulate the expression of genes
(e.g. promotors and transcripton factor binding sites).

Every ORF has a unique id, like Rv0018c or SACOL_1423.  Some ORFs have
gene names, if we know what they do, like "gyrA" (DNA gyrase, subunit
A) or "rpoB" (RNA polymerase, subunit B).  But if not, gene name is
just "-".

The format of prot_tables is 9 tab-separated columns:

A) description of gene function
B) start coord
C) end coord
D) strand (+ or -)
E) size of protein product (in amino acids)
F) (don't care)
G) (don't care)
H) gene name
I) orfid

The coordinates give positions in the nucleotide sequence.  By
convention, the first nucleotide in the genome has coordinate 1.
Also, the end coordinate of a gene is the last nucleotide *included*
in the gene.  For genes on the + strand, it is the last nuc of the
stop codon.  For genes on the - strand, it is the first nuc of the
start codon.