========================================================================
    CONSOLE APPLICATION : Search for duplicate files
========================================================================
Summary: 
I chose level three because I wanted to challenge my own programming skills. This is my first
time working with directories and files in this manner and I found it quite fun to do this
assignment. I started with level 1 and when I was done I did not find it difficult to complete the
next levels. I have used the Boost library to complete this task.

Goal: 
The goal was for the program to take an directory location from user input and generate a 
textfile wich contains the duplicate files and their folders. In this case a duplicate file
has the same size and the same filename. If multiple files in the same folder they will be 
grouped together in the text file.  


Functionality:
This application needs two parameters in order to work. First of all it needs a path
to the desired location, the second parameter needed is a userdefined structure called 'File'.
The structure consists of a filename(string), a vector of paths and a filesize(long long).
 
The user types in a location wich the application will search through. The application 
checks wheter the directory exsits and prints an errormesage if not. If the user types in
'search' the program will search in the chosen directory. Its not possible to search directory unless 
a valid path is chosen. 

When the user find the desired directory and enter search the program will execute a function 
that searches the folder. This function will search all floders located in the desired 
directory and look for filenames. When a file is found the function will store the filename 
and the path in a vector. If a file with same name as a previous file is found and the size is different 
then only the path will be stored. This results that only files with the same content will be regarded as
equal files.
EDIT: The new code uses a map to search for equal filenames instead for a for loop. This makes the 
"searchDirectory" fuction a lot faster than the previous code. 

After the application is done searching it enters a new function that only returns elements which are
duplicated. The same function will also sort the folder vector alphabeticaly. 

Before writing the filenames and paths to the file application will group the files that contains
the same paths. This is done by searching through the vector of File and comparing the path vector
to check wether they are equal. The searching algorithm I thought of myself, so there might be more
efficient ways to do this. But basically it loops through a vector of type File comparing it with the 
next elements. If a set of paths are found, the element(i) will be skipped so it dont handle the same 
element twice.

At last the application creates a file and prints out the group of files. 

Limitations: 
If the user wish to exit the program without searching, this is not possible. 

If the path vector is not sorted in the same manner the program will not be able to detect a group 
of files. 

The memorymanagement may not be optimal, but it does not leak any. 
/////////////////////////////////////////////////////////////////////////////
Other standard files:
StdAfx.h, StdAfx.cpp
/////////////////////////////////////////////////////////////////////////////
Other notes:
Boost library is needed in order for this program to work

/////////////////////////////////////////////////////////////////////////////
