//tags_to_fasta
//Author: Sarah P. Flanagan, sflanagan@bio.tamu.edu
//Date: 27 August 2014
//This program converts the output from cstacks (part of the Stacks program's pipeline)
//(files named batch_x.catalog.tags.csv) to fasta format for alignment to a reference 
//genome or forother analyses. 
// Usage:
// -i:	Fastq Input Filename
// -o:	Output Filename 
// -h: Help
// no arguments: Interactive


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

void FileTest(ifstream& file, string filename)
{
	cout << filename;
	if (file.is_open())
		cout << " open\n";
	else
	{
		while (!file.is_open())
		{
			cout << " not open. Please re-enter filename: ";
			getline(cin, filename, '\n');
			file.open(filename);
		}
	}

}

int main( int argc, char* argv[])
{
	int end, count, i;
	int one, two, four, seven, ten,  eleven, twelve, thirteen;
	string three, five, six, eight, nine;
	string tags_name, fasta_name, line;
	ifstream tags_file;
	ofstream fasta_file;
	istringstream lin;
	bool interactivemode = false;

	string query;
	string tempstring1, tempstring2;
	fasta_name = tags_name = "default"; 

	if (argc == 1)
	{
		cout << "\n(I)nteractive or (H)elp?\n";
		cin >> query;
		if (query == "H" || query == "h")
		{
			cout << "\ntags_to_fasta:\n";
			cout << "converts stacks' batch_x.catalog.tags.tsv files to fasta format \n";
			cout << "-i:\tinput file (including path)\n";
			cout << "-o:\toutput file (including path)\n";
			cout << "-h:\tPrints this message\n";
			cout << "no arguments:\tinteractive mode\n";
			return 0;
		}
	}

	if (argc > 1)
	{
		tempstring1 = argv[1];
		if (tempstring1 == "-h")
		{
			cout << "\ntags_to_fasta:\n";
			cout << "converts stacks' batch_x.catalog.tags.tsv files to fasta format \n";
			cout << "-i:\tinput file (including path)\n";
			cout << "-o:\toutput file (including path)\n";
			cout << "-h:\tPrints this message\n";
			cout << "no arguments:\tinteractive mode\n";
			return 0;
		}
	}
		
	for (i = 1; i < argc-1; i++)
	{
		tempstring1 = argv[i];
		tempstring2 = argv[i+1];
		if (tempstring1 == "-i")
			tags_name = tempstring2;
		if (tempstring1 == "-o")
			fasta_name = tempstring2;
	}

	if (tags_name == "default")
	{
		cout << "Input Filename:\n";
		cin >> tags_name;	
		interactivemode = true;
	}

	if (fasta_name == "default")
	{
		cout << "\nOutput Filename:\n";
		cin >> fasta_name;
		interactivemode = true;
	}

	cout << "\n\nInput File:\t" << tags_name;
	cout << "\nOutput File:\t" << fasta_name;

	if (interactivemode)
	{
		cout << "\n\nProceed? (y to proceed)\n";
		cin >> query;

		if (query != "y" && query != "Y")
		{
			cout << "\n\nEnter an integer to exit!!\n";
			cin >> i;
			return 0;
		}
	}

	cout << "\n\nProceeding...\n";
	//tags_name = "/home/joneslab/Documents/Sarahs/LinkageMap/denovo/batch_1.catalog.tags.tsv";
	//fasta_name = "/home/joneslab/Documents/Sarahs/LinkageMap/catalog.tags.fa";
	tags_file.open(tags_name.c_str());
	FileTest(tags_file, tags_name.c_str());
	fasta_file.open(fasta_name);
	count = 0;

	while (getline(tags_file, line, '\n'))
	{
		lin.clear();
		lin.str(line);
		if(lin >> one >> two >> three >> four >> five >> six >> seven >> eight >> nine >> ten >> eleven >> twelve >> thirteen)
		{
			fasta_file << ">locus_" << three << '\n';
			fasta_file << nine << '\n';			
		}//end of if(lin)
		else
		{
			cout << "WARNING: failed to decode line " << count << "\n";
		}
		count++;
		if(count % 10000 == 0)
			cout << "Locus " << count << " done!\n";
	}
	tags_file.close();
	fasta_file.close();

	if(interactivemode)
	{
		cout << "\nDone! Enter integer to quit.";
		cin >> end;
	}
	return 0;

}
