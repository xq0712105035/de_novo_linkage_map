README
tags_to_fasta

Contact Sarah Flanagan (sflanagan@bio.tamu.edu) for more information.

This program converts the stacks *.catalog.tags.tsv output to fasta format

What it requires:
1. *.catalog.tags.tsv file from Stacks' cstacks program

What it outputs:
1. one fasta file, with the header lines recording the name of the rad tag locus

Installation and Usage:
Windows:
Put the executable (tags_to_fasta.exe) in a useful folder. It is easiest (the path you must provide is shortest) if you put it in your desired output directory.

Ubuntu:
Put the executable in a useful folder. It is easiest (the path you must provide is shortest) if you put it in your desired output directory.
**You may need to alter file permissions for it to run:
chmod u+x tags_to_fasta

To run the file in interactive mode: 
./tags_to_fasta

To run the file with arguments:
./tags_to_fasta -i batch_x.catalog.tags.tsv -o output.txt

For help:
./tags_to_fasta -h 

Other operating systems:
Compile the source code using the g++ compiler.
For example:
g++ tags_to_fasta.cpp -o tags_to_fasta -std=c++0x


Arguments:
-i: input filename (include path)
-o: output file name (include path)
-h: prints a help message
no arguments: interactive mode