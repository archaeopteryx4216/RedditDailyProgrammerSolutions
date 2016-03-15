#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int currentYear = 2016;
const int georgeYear = 1732;

string nextString(string str, int start, char delim);
int split(string line, string *words, int max_size, char delim);
string trimLeadingSpaces(string str);

int main()
{
    ifstream fin;
    string fname, line;
    string words[50];
    string birthdate[10];
    string deathdate[10];
    int count, maxPres = 0;
    int years[currentYear - georgeYear];
    for (int i=0; i<currentYear - georgeYear; i++)
    {
        years[i] = 0;
    }
    cout << "Please enter the name of the .csv file containing the United States Presidents along with their birth and death dates." << endl;
    cin >> fname;
    fin.open(fname.c_str());
    if (fin.fail())
    {
        cerr << "Error opening file "
            << fname << ". Exit status 1."
            << endl;
        return 1;
    }
    getline(fin,line);// Discard the first line
    while (getline(fin,line))
    {
        split(line,words,50,',');
        split(trimLeadingSpaces(words[1]),birthdate,10,' ');
        count = split(trimLeadingSpaces(words[3]),deathdate,10,' ');
        if (count < 3) // Prfesident still alive in this case.
        {
            int birthYear;
            sscanf(birthdate[2].c_str(),"%d",&birthYear);
            for (int i = birthYear - georgeYear; i<currentYear - georgeYear; i++)
            {
                years[i]++;
            }
        }
        else
        {
            int birthYear;
            int deathYear;
            sscanf(birthdate[2].c_str(),"%d",&birthYear);
            sscanf(deathdate[2].c_str(),"%d",&deathYear);
            for (int i = birthYear - georgeYear; i<=deathYear - georgeYear; i++)
            {
                years[i]++;
            }
        }
    }
    for (int i=0; i<currentYear - georgeYear; i++)
    {
        if (years[i] > maxPres)
        {
            maxPres = years[i];
        }
    }
    for (int i=0; i<currentYear - georgeYear; i++)
    {
        if (years[i] == maxPres)
        {
            cout << "Year: " << i + georgeYear << endl;
        }
    }
    return 0;
}

// This function returns the substring from index start of str up until either the end of the string or the index of the next delimiter.
string nextString(string str, int start, char delim)
{
    string newStr = str.substr(start,str.length());
    int index = newStr.find(delim);
    if (index == string::npos)
    {
        return newStr;
    }
    else
    {
        return newStr.substr(0,index);
    }
}

// This function splits the string line into an array of strings called words, of size up to max)size, and split based on the character delim.
int split(string line, string *words, int max_size, char delim)
{
    int i,j;
    for (i=0, j=0; i<max_size-1; i++)
    {
        words[i] = nextString(line,j,delim);
        j += words[i].length()+1;
        if (j >= line.length())
        {
            break;
        }
    }
    return i+1;
}

// This function removes leading space characters from a string, then returns the cleaned string.
string trimLeadingSpaces(string str)
{
    string newStr = "";
    int length = str.length();
    int i;
    for (i=0; i<length; i++)
    {
        if (str[i] != ' ')
        {
            break;
        }
    }
    for (; i<length; i++)
    {
        newStr += str[i];
    }
    return newStr;
}
