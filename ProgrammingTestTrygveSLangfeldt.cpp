// ProgrammingTestTrygveSLangfeldt.cpp :
//
//Level 3



#include "stdafx.h"
#include <boost\filesystem.hpp>
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <map>

using namespace std;
using namespace boost::filesystem;

struct File
{
	string fileName;
	vector<path> folder;
	long long size;
};

typedef std::map<string, File> mapTree;

void searchDirectoy(path pathToDir,mapTree &searchTree);
void writeToFile(vector<File> myFile, string newFilename);
vector<File> getDuplicates(mapTree &searchTree);
vector<File> groupFiles(vector<File> dupFiles);

int main()
{
	//Empty vector for types of files
	
	path P = current_path();
	string directory = P.string();
	cout << "*************************************************************************" << endl
		<< "Find your directory and enter 'search' when ready " << endl
		<< "*************************************************************************" << endl;

	cout << "Current folder: " << endl << P.string() << endl;
	while (true)
	{

		cin >> directory;

		if (directory == "search")
		{
			if (!exists(P))
			{
				cout << "No such file or directory" << endl;
			}
			else {
				break;
			}
		}
		else
		{
			P = directory;
			if (!exists(P))
			{
				cout << "No such file or directory" << endl;
			}
		}

		
	}

	cout << "Searching in directory: " << endl << P << endl << endl;
	mapTree searchTree;

	//Search whole directory for files
	searchDirectoy(P, searchTree);
	
	//Get duplicate files sorted
	vector <File> myDuplicateFiles = getDuplicates(searchTree);

	//Group identical set of files
	myDuplicateFiles = groupFiles(myDuplicateFiles);
	
	//Writing to new file
	writeToFile(myDuplicateFiles, "Bin.txt");


}
void searchDirectoy(path pathToDir, mapTree &searchTree)
{
	cout << "Now searching in: " << pathToDir.string() << endl;
	//Iterator that loops through directory
	directory_iterator content{ pathToDir };
	while (content != directory_iterator{})
	{
//Search throgh the allocated directory for files or subfolder. If a subfolder is found 
//the function will be called recursively.
if (is_directory(*content))
{
	searchDirectoy(content->path(), searchTree);
}

else
{
	//If detected a file extract nececcary information from the iterator 
	path pathToFile = content->path();
	path thisFilename = pathToFile.filename();

	/*EDIT: searching for a equal filename with a map iterator instead of a for-loop. 
	This part is a lot more efficient than the original code I made. 
	It has log_2(N) iterations instead for N iterations. 
	*/
	map<string, File>::iterator it = searchTree.find(thisFilename.string());
	

	if (it != searchTree.end() && it->second.size == file_size(pathToFile))
	{
		it->second.folder.push_back(pathToDir);
	}
	else {
		File temp;
		temp.fileName = thisFilename.string();
		temp.folder.push_back(pathToDir);
		temp.size = file_size(pathToFile);
		searchTree.insert(pair<string, File>(temp.fileName, temp));
	}
	/*
	*************** OLD CODE ****************************
	for (int i = 0; i<files.size(); i++)
	{
		//Loops through the already known files and check if the current filename is among them, also checks wether the
		//files have the same size(content)
		if (files[i].fileName == thisFilename.string() && files[i].size == file_size(pathToFile))
		{
			fileFound = true;
			files[i].folder.push_back(pathToDir);
			break; // I decided to put a break; here, scince two files cannot have the same name this is possible.
		}

	}

	if (!fileFound)
	{
		//If the filename is not found a temporary object (of type File) is made and pushed bakc into vector containing
		//the rest of the filenames

		files.push_back(temp);

	}

}
	*********************************************************
*/

}
*content++;
	}

}

void writeToFile(vector<File> fileContent, string newFilename)
{
	std::ofstream newFile;
	newFile.open(newFilename);

	if (newFile.is_open()) {

		for (auto x : fileContent)
		{
			if (x.folder.size() >= 2) {
				newFile << "Filename: " << x.fileName << endl; //<< "\t Size: " << x.size << endl;

				for (auto y : x.folder) newFile << "\t" << y << endl;
				newFile << endl << endl;

			}
		}
	}
	newFile.close();

}


vector<File> getDuplicates(mapTree &searchTree)
{	
	//Temporary vector(return statement)
	cout << "Extracting duplicates" << endl;
	vector<File> temp;
	/*
	This part is why I waited so long to submit the assginment, I wanted to see if I could find an algorithm or method that could sort the map in folder.size(). I did not accomlish this so I used this for loop that checks each element whether the folder.size() is equal or larger than 2(two).
	*/

	for (auto it = searchTree.begin(); it != searchTree.end(); it++)
	{
		if (it->second.folder.size() >= 2)
		{
			temp.push_back(it->second);
		}
	}
	return temp;
}

vector<File> groupFiles(vector<File> dupFiles)
{
	/*
	This function takes a vector as an argument and searches throgh the vector looking for equal folders.
	In order for this function to work its important that the folder vector has been sorted.
	*/
	vector<File> newVec;
	File temp;

	vector<int> skipElement;
	bool skip = false;
	for (int i = 0; i <dupFiles.size(); i++)
		// Search through the whole vector and stores the information in a temporary variable
	{
		// Skips i when the i is an element in skipElement scince this element already has been handeled
		for (auto X : skipElement) skip = X == i;
		if (skip) continue;


		temp.fileName = dupFiles[i].fileName;
		temp.folder = dupFiles[i].folder;
		temp.size = dupFiles[i].size;
		for (int j = i + 1; j<dupFiles.size(); j++)
		{
			// Loop from i+1 so it doesnt compare the equal element or the same element twice
			if (dupFiles[i].folder == dupFiles[j].folder)
			{
				//If the duplicates exists in multiple folders the name will be modified

				temp.fileName.append(", ");
				temp.fileName.append(dupFiles[j].fileName);
				skipElement.push_back(j);//Adds an elemet that will be skipped later 
			}
		}
		newVec.push_back(temp);
	}
	return newVec;
}

