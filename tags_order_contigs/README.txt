README
tags_order_contigs

Contact Sarah Flanagan (sflanagan@bio.tamu.edu) for more information.

This program orders contigs of a reference genome using a de novo linkage map of RAD-tags.
What must be done before running this program:
1. Run your data through Stacks using denovo_map.pl and genotypes.
2. Use OneMap (or another mapping program) to order your RAD-tags.
3. Convert your RAD-tags to fasta format and map them to a reference genome (e.g. with bowtie2)

What it requires:
1. *.sam file describing alignments between RAD-tags and the reference genome.
2. A file with two columns listing the markers with the linkage groups. This file should have a header, and the first column must be the LG number (an integer) and teh second column the RAD-tag marker number (also an integer)

What it outputs:
1. A file with two columns: the linkage group in the first column and the scaffold/contig label in the second column, ordered according to the linkage map.

Installation and Usage:
Windows:
Put the executable (tags_order_contigs.exe) in a useful folder. It is easiest (the path you must provide is shortest) if you put it in your desired output directory.

Ubuntu:
Put the executable in a useful folder. It is easiest (the path you must provide is shortest) if you put it in your desired output directory.
**You may need to alter file permissions for it to run:
chmod u+x tags_order_contigs

To run the file in interactive mode: 
./tags_order_contigs

To run the file with arguments:
./tags_order_contigs -s alignment.sam -l marker_list.txt -o output.txt

For help:
./tags_order_contigs -h 

Other operating systems:
Compile the source code using the g++ compiler.
For example:
g++ tags_order_contigs.cpp -o tags_order_contigs -std=c++0x


Arguments:
-s: *.sam (alignment) file (including path)

-l: list of markers and associated linkage groups (column 1 = LG, column 2 = marker number)

-o: output file name (including path). Default: ordered_contigs.txt

-h: Prints help message

no arguments: interactive mode (as opposed to passing arguments to the program)