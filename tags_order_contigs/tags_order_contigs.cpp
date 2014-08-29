//tags_order_contigs
//Author: Sarah P. Flanagan, sflanagan@bio.tamu.edu
//Date: 27 August 2014
//
//Purpose of this program:
//to take aligned RAD tags (output = *.sam format) that have been sorted and ordered
//into linkage groups and order the relevant contigs from a genome.

//Required information: (1) a .sam file and 
//(2) a file with two columns listing the markers with the linkage groups
//The list file should have a header, and the first column should be the LG number 
//(an integer) and the second column the rad marker (also an integer)

//Usage:
//use ordered rad-tags from a denovo stacks run to order contigs from a reference genome (after aligning and getting .sam files) 
//-s: *.sam (alignment) file (including path)
//-l: list of markers and associated linkage groups (column 1 = LG, column 2 = marker number)
//-o: output file name (including path). Default: ordered_contigs.txt
//-h: Prints help message
//no arguments: interactive mode (as opposed to passing arguments to the program)

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

bool FileTest(ifstream& file, string filename)
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
	return true;
}

class marker{
public:
	int tag, LG, pos;
	string scaffold;

	//constructor
	marker()
	{
		tag = LG = pos = 0;
		scaffold = "";
	}
};

int main(int argc, char* argv[])
{
	int end, count, i, loc_id, linecounter, num_LGs;
	stringstream ss1, ss2;
	int two, four, five, eight, nine, a, b;
	string one, three, six, seven, ten, eleven, line, dump1, dump2;
	string ord_tags_name, tags_align_name, output_name, last_scaffold;
	ifstream ord_tags, tags_align;
	ofstream output;
	vector <marker> markers;
	istringstream lin;
	bool interactivemode = false;
	string tempstring1, tempstring2, query;

	ord_tags_name = "default";
	tags_align_name = "default";
	output_name = "ordered_contigs.txt";

	if (argc == 1)
	{
		cout << "\n(I)nteractive or (H)elp?\n";
		cin >> query;
		if (query == "H" || query == "h")
		{
			cout << "\ntags_order_contigs:\n";
			cout << "use ordered rad-tags from a denovo stacks run to order contigs from a reference genome (after aligning and getting .sam files)  \n";
			cout << "-s:\t*.sam (alignment) file (including path)\n";
			cout << "-l:\tlist of markers and associated linkage groups (column 1 = LG, column 2 = marker number)\n";
			cout << "-o:\toutput file name (including path). Default: ordered_contigs.txt\n";
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
			cout << "\ntags_order_contigs:\n";
			cout << "use ordered rad-tags from a denovo stacks run to order contigs from a reference genome (after aligning and getting .sam files)  \n";
			cout << "-s:\t*.sam (alignment) file (including path)\n";
			cout << "-l:\tlist of markers and associated linkage groups (column 1 = LG, column 2 = marker number)\n";
			cout << "-o:\toutput file name (including path). Default: ordered_contigs.txt\n";
			cout << "-h:\tPrints this message\n";
			cout << "no arguments:\tinteractive mode\n";
			return 0;
		}
	}

	for (i = 1; i < argc - 1; i++)
	{
		tempstring1 = argv[i];
		tempstring2 = argv[i + 1];
		if (tempstring1 == "-s")
			tags_align_name = tempstring2;
		if (tempstring1 == "-l")
			ord_tags_name = tempstring2;
		if (tempstring1 == "-o")
			output_name = tempstring2;
	}

	if (tags_align_name == "default")
	{
		cout << "Input *.sam (alignment) file name (including path):\n";
		cin >> tags_align_name;
		interactivemode = true;
	}

	if (ord_tags_name == "default")
	{
		cout << "\nInput list of markers and associated linkage groups (column 1 = LG, column 2 = marker number):\n";
		cin >> ord_tags_name;
		interactivemode = true;
	}

	if (output_name == "ordered_contigs.txt")
	{
		cout << "\nProvide output file name (including path)? Default is ordered_contigs.txt in this directory. If that is ok, enter 'y':\n";
		cin >> output_name;
		if (output_name == "y" || output_name == "Y")
			output_name = "ordered_contigs.txt";
		interactivemode = true;
	}

	cout << "\n\n*sam File:\t" << tags_align_name;
	cout << "\nList File:\t" << ord_tags_name;
	cout << "\nOutput File:\t" << output_name;

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

	ord_tags.open(ord_tags_name);
	interactivemode = FileTest(ord_tags, ord_tags_name);
	count = linecounter = 0;
	num_LGs = 0;
	cout << "\nReading " << ord_tags_name << ".\n";
	while (getline(ord_tags, line, '\n'))
	{
		lin.clear();
		lin.str(line);
		if (linecounter != 0)//there's a header
		{
			if (lin >> a >> b)
			{
				markers.push_back(marker());
				markers[count].LG = a;
				markers[count].tag = b;
				count++;
				if (a > num_LGs)
					num_LGs = a;
			}//end of if(lin)
			else
			{
				cout << "WARNING: failed to decode line " << count << "\n";
			}
		}//end of linecounter
		linecounter++;
	}//end of while
	ord_tags.close();
	cout << "\nFound " << count << " ordered markers.\n";

	//read in the alignment info
	tags_align.open(tags_align_name);
	interactivemode = FileTest(tags_align, tags_align_name);
	cout << "\nReading " << tags_align_name << " and ordering alignments.\n";
	linecounter = 0;
	while (getline(tags_align, line, '\n'))
	{
		lin.clear();
		lin.str(line);
		if (lin >> one >> two >> three >> four >> five >> six >> seven >> eight >> nine >> ten >> eleven)
		{
			ss1 << one;
			getline(ss1, dump1, '_');
			getline(ss1, dump2);
			ss2 << dump2;
			ss2 >> loc_id;
			for (i = 0; i < count; i++)
			{
				if (loc_id == markers[i].tag)
				{
					markers[i].scaffold = three;
					markers[i].pos = four;
				}
			}//end for(i)
			ss1.str("");
			ss1.clear();
			ss2.str("");
			ss2.clear();
		}//end of if(lin)	
		else
		{
			cout << "WARNING: failed to decode line " << count << "\n";
		}
		linecounter++;
		if (linecounter % 10000 == 0)
			cout << "Locus " << linecounter << " done!\n";
	}//end of while	
	tags_align.close();

	last_scaffold = "";
	output.open(output_name);
	for (i = 0; i < count; i++)
	{
		if (markers[i].scaffold != "*")
		{
			if (markers[i].scaffold != last_scaffold)
			{
				output << '\n' << markers[i].LG << '\t' << markers[i].scaffold << '\t' << markers[i].tag;
				last_scaffold = markers[i].scaffold;
			}
			else
			{
				output << ", " << markers[i].tag;
			}
		}//end if *	
	}

	output.close();

	if (interactivemode)
	{
		cout << "\nDone! Input integer to quit.\n";
		cin >> end;
	}
	return 0;
}
