de_novo_linkage_map
===================

This repository contains code and programs to generate a de novo linkage map using RAD-tags and then use that
linkage map to order the contigs of a draft reference genome.

It contains several files, which should be implemented in this order:
1. denovo.sh
2. onemap_denovo
3. tags_to_fasta
[run bowtie2 or another aligner]
4. tags_order_fasta

denovo.sh and onemap_denovo must both be altered within the scripts to run on your data. denovo.sh calls stacks, so that must be installed properly on your machine for this pipeline to work. This pipeline also requires that some alignment program be installed on your machine (tested with bowtie2), and the aligner must output sam files.

This pipeline takes RAD data (processed by process_radtags), and runs denovo_map.pl on those radtags. The genotypes.pl component of stacks then outputs a file compatible with onemap. My R script then runs onemap (I recommend doing this bit by bit in the R interface, rather than submitting it as an R script: you want to optimize the commands for each linkage group and test out different LOD values as well). To order the RAD-tags produced by stacks' denovo pipeline, tags_to_fasta converts the stacks output to fasta, which can then be used as the reads that you map to your reference. Once the RAD-tags have been ordered by onemap and aligned to the genome with bowtie2 (or equivalent), all that remains is to sort the aligned contigs according to the order provided by the linkage map. tags_order_fasta does just that. At the end of the pipeline, you should have at least most of your contigs in the order provided by the linkage map of denovo-assebled RAD tags.

To install:
Copy denovo.sh and onemap_denovo.R into the directories you are working in. Modify their contents to suit your filenames, directory names, and other relevant information.

tags_to_fasta and tags_order_fasta are provided in several different download possibilites:
(a) source code (.cpp files), which you can compile using a c++ compiler 
(b) Windows executable file (.exe), which can be downloaded and then run as you would any other .exe file
(c) Linux executable file (no extension), which can be downloaded and run in the terminal.
(d) .zip file containing all three of those plus the README, which you can download and then extract and choose which files to use.
