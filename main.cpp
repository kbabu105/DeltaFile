//
//  main.cpp
//  Proj4
//
//  Created by Krishna on 5/29/16.
//  Copyright © 2016 Krishna. All rights reserved.
//

#include <iostream>
#include <string>
#include <sstream>
#include <queue>
#include <stack>

#include <cassert>
#include <fstream>

#include "hash.h"
//#include <fstream>

using namespace std;

const int N = 8;

// createDelta: This function takes the contents of two files, A and A', and produces a delta containing instructions for converting A into A'. Each day, Small-Mart will use this function at their corporate headquarters to create a new delta file that they will then send to all the devices.
void createDelta(istream& oldf, istream& newf, ostream& deltaf);
    string readFile(istream& f);
// applyDelta: This function takes the content of a file A and a delta file, and will apply the instructions in the delta file to produce a new file A'. Each day, every device will use this function to update the previous day's inventory file.
bool applyDelta(istream& oldf, istream& deltaf, ostream& newf);
    bool getInt(istream& inf, int& n);
    bool getCommand(istream& inf, char& cmd, int& length, int& offset);


//void runtest(string oldtext, string newtext)
//{
//    istringstream oldfile(oldtext);
//    istringstream newfile(newtext);
//    ostringstream deltafile;
//    createDelta(oldfile, newfile, deltafile);
//    string result = deltafile.str();
//    cout << "The delta length is " << result.size()
//    << " and its text is " << endl;
//    cout << result << endl;
//    
//    oldfile.clear();   // clear the end of file condition
//    oldfile.seekg(0);  // reset back to beginning of the stream
//    istringstream deltafile2(result);
//    ostringstream newfile2;
//    assert(applyDelta(oldfile, deltafile2, newfile2));
//    assert(newtext == newfile2.str());
//    
//    string result2 = newfile2.str();
//    cout << "The new length is " << result2.size()
//    << " and its text is " << endl;
//    cout << result2 << endl << endl;
//
//}
//
//int main()
//{
//    runtest("There's a bathroom on the right.",
//            "There's a bad moon on the rise.");
//    runtest("ABCDEFGHIJBLAHPQRSTUVPQRSTUV",
//            "XYABCDEFGHIJBLETCHPQRSTUVPQRSTQQELF");
//    cout << "All tests passed" << endl;
//}

bool runtest(string oldname, string newname, string deltaname, string newname2)
{
    ifstream oldfile(oldname);
    if (!oldfile)
    {
        cerr << "Cannot open " << oldname << endl;
        return false;
    }
    ifstream newfile(newname);
    if (!newfile)
    {
        cerr << "Cannot open " << newname << endl;
        return false;
    }
    ofstream deltafile(deltaname); //** use ostringstream to print deltafile
    if (!deltafile)
    {
        cerr << "Cannot create " << deltaname << endl;
        return false;
    }
    createDelta(oldfile, newfile, deltafile);
//    
//    string result = deltafile.str();    //**  add into code to print deltafile
//    cerr << "The delta length is " << result.size()
//    << " and its text is " << endl;
//    cerr << result << endl;
    
    deltafile.close();    //** comment out to print deltafile
    
    oldfile.clear();   // clear the end of file condition
    oldfile.seekg(0);  // reset back to beginning of the file
    ifstream deltafile2(deltaname);
    if (!deltafile2)
    {
        cerr << "Cannot read the " << deltaname << " that was just created!" << endl;
        return false;
    }
    ofstream newfile2(newname2);
    if (!newfile2)
    {
        cerr << "Cannot create " << newname2 << endl;
        return false;
    }
    
    assert(applyDelta(oldfile, deltafile2, newfile2));
    cout << "You must compare " << newname << " and " << newname2 << endl;
    cout << "If they are not identical, you failed this test." << endl;
    return true;
}

int main()
{
    //greeneggs
    //assert(runtest("/Users/Kiwi/Desktop/Xcode/CS 32/Proj4/Proj4/Proj4/greeneggs1.txt", "/Users/Kiwi/Desktop/Xcode/CS 32/Proj4/Proj4/Proj4/greeneggs2.txt", "/Users/Kiwi/Desktop/Xcode/CS 32/Proj4/Proj4/Proj4/GRmydeltafile.txt", "/Users/Kiwi/Desktop/Xcode/CS 32/Proj4/Proj4/Proj4/GRmynewfile2.txt"));
    
    //smallmart
    //assert(runtest("/Users/Kiwi/Desktop/Xcode/CS 32/Proj4/Proj4/Proj4/smallmart1.txt", "/Users/Kiwi/Desktop/Xcode/CS 32/Proj4/Proj4/Proj4/smallmart2.txt", "/Users/Kiwi/Desktop/Xcode/CS 32/Proj4/Proj4/Proj4/SMmydeltafile.txt", "/Users/Kiwi/Desktop/Xcode/CS 32/Proj4/Proj4/Proj4/SMmynewfile2.txt"));
    
        //SMmynewfile2.txt NOT CORRECT
    
    //strange
    assert(runtest("/Users/Kiwi/Desktop/Xcode/CS 32/Proj4/Proj4/Proj4/strange1.txt", "/Users/Kiwi/Desktop/Xcode/CS 32/Proj4/Proj4/Proj4/strange2.txt", "/Users/Kiwi/Desktop/Xcode/CS 32/Proj4/Proj4/Proj4/STmydeltafile.txt", "/Users/Kiwi/Desktop/Xcode/CS 32/Proj4/Proj4/Proj4/STmynewfile2.txt"));
    
    //war and peace
    //assert(runtest("/Users/Kiwi/Desktop/Xcode/CS 32/Proj4/Proj4/Proj4/warandpeace1.txt", "/Users/Kiwi/Desktop/Xcode/CS 32/Proj4/Proj4/Proj4/warandpeace2.txt", "/Users/Kiwi/Desktop/Xcode/CS 32/Proj4/Proj4/Proj4/WAmydeltafile.txt", "/Users/Kiwi/Desktop/Xcode/CS 32/Proj4/Proj4/Proj4/WAmynewfile2.txt"));
}






//*** Notice that the type named in the parameter declaration is ostream, not ofstream, and that the parameter is passed by reference. An ostream reference can refer to any kind of output stream: to cout or to any ofstream attached to a file. (This is because ostream is a base class of ofstream.) Here's an example:


//CREATEDELTA: Of course, this delta approach can be used to update all types of files, not just inventory files. For instance, consider the following two files A and A', where A' is a derived version of A.
//Here's a general, high-level algorithm that can be used to build a delta file. It's not ideal, however, and you'll have to come up with improvements of your own to make it work well:
//
//Read in the entire contents of the old file into a string. Read the entire contents of the new file into another string.
//For all consecutive N-character sequences in the old file's string, insert that N-character sequence and the offset F where it was found in the old file's string, into a table (e.g. hash table or binary search tree). You might use 8 for N, or maybe 16.
//Once you have filled up your table with all N-byte sequences from the source file, start processing the new file's string, starting from offset j=0, until j reaches the end of the string.
//Look up the N-byte sequence which starts at offset j ([j,j+N-1]) in the new file's string in the table you created from the old file's string.
//If you find this sequence in the table, you know that that sequence is present in both the old and new versions of the file.
//Determine how long the match goes on (it might be just N bytes long, or it might extend past the first N matching bytes to be many bytes longer).
//Once you have determined how long the match is (call this L), write a Copy instruction to the delta file to copy L bytes from offset F from the source file.
//Go back to step 3a, continuing at offset j = j + L in the new file's string.
//If you don't find the current sequence (new file's string [j,j+N-1]) in the table you created, you know that the first version of the file doesn't contain the current N byte sequence.
//Write an instruction to the delta file to Add the current character.
//Increment j by one to continue past the character used in the add instruction.
//Go back to step 3a, where we'll try to find the next N-byte sequence in our table.
//
//Of course, this is a simple version of the algorithm, and many improvements are possible. For example, this version of the algorithm will result in only single-character add instructions: If the new file contains the new text BLAH (not present in the old text), then the above algorithm would produce four Add instructions (A1:BA1:LA1:AA1:H) instead of a single (and more compact) Add instruction that adds all four new characters at once (A4:BLAH).
//
//To obtain the highest score possible and create the smallest delta files, you'll have to improve on the algorithm substantially. Be creative! In addition, this naïve algorithm also has troubles with certain types of files (such as the strange*.txt sample files that we provide). You'll have to figure out why and make sure this doesn't cause problems in your solution.

string readFile(istream& f)
{
    ostringstream stringF;
    if(f)
    {
        while(f.peek() != EOF)
        {
            stringF << (char) f.get();  //whether it's a letter, blank, newline, or whatever, cast as char and add to string
        }
        
        f.clear();
        f.seekg(0);
    }
    return stringF.str();
}


void createDelta(istream& oldf, istream& newf, ostream& deltaf)
{
//1: make oldf and newf into strings
    string oldfString = readFile(oldf);             //translates files into long single strings
    string newfString = readFile(newf);
    
//2: store all N-bit seq of oldf in hash table of approp size (store L-L in sorted orders)
   
    //2b: housekeeping/vars
    bool lastWasAdd = false;
    size_t nChars = oldfString.size();              //#chars in oldfString --> #buckets
    //queue<char> temp;
    string oldAddText;

    //2a: approp size hash table 4 less collisions (same string collisions unavoidable/necessary)
    Unordered_MultiMap<string, int> index(nChars*2);    //N seq, offset; construct hash table to approp size
    //index.changeSize(nChars);                       //resize hash table to approp size
    
    for(int i = 0; i <= oldfString.size() - N; i++)  //to insert all N-bit sequences for all offsets
    {
        string NSeqOld;
        for(int j = i; j < i+N; j++)             //make N-bit seq string at that offset, renew for new offsets
        {
            NSeqOld += oldfString[j];
        }
        
        index.insert(pair<string,int>(NSeqOld, i));    //then store N-bit seq and offset
    }
    
//    list<int> values = index.get("Green Eg");	//should print keys of all "abcdef"'s
//    for(int v: values)
//        cerr << v << " ";
    
//3: Look up N-byte sequence of new in hash table till newf's end       (newf > oldf OR newf < oldf)
    
    for(size_t i = 0; i < newfString.size();)  //to check all chars in newfString;inc as approp in resp. cases
    {
        //3a: IF i > size-N: add in [i to size)
        
        if(i > newfString.size() - N)       //if using not findable i (i > newfString.size()-N)
        {
            //make N-bit seq string at that offset, store get
            string NSeqNew; //in scope of this if loop ONLY
            for(size_t j = i; j < newfString.size(); j++)
            {
                NSeqNew += newfString[j];
            }
            
            //ADD in the string as Alen:txt

            //case 1:
            if(!oldAddText.empty()) //if Add cmd leftover in oldAddText string --> join remaining chars and oldAddText and ADD in string
            {
                deltaf << "A" << (oldAddText.size() + NSeqNew.size()) << ":" << oldAddText + NSeqNew;   //string concatenation
                
                oldAddText = "";
            }
            
            //case 2:
            else
            {deltaf << "A" << NSeqNew.size() << ":" << NSeqNew;}
            
            lastWasAdd = true;
            i = newfString.size();
            break;  //can use break here appropriately because it'll leave the for loop
        }
        
        //3b+3c PRIMER:
        //Look up the N-byte sequence which starts at offset j ([j,j+N-1]) in the new file's string in the table you created from the old file's string.
        
        //make N-bit seq string at that offset (only if valid to go to i+N), store get
        string NSeqNew1;
        for(size_t j = i; j < i + N; j++)
        {
            NSeqNew1 += newfString[j];
        }
        
        //find offset values (1+) stored along with unique string
        list<int> values = index.get(NSeqNew1);

        
        
        //3b: IF FOUND: keep comparing and check all keys that match            //like strange.txt?
        //*traverse LL (ALL have same key and hashed index) until list end
                                                                                //what if alot of elements?
        //*find LENGTH of match for each and store in variable AND store OFFSET (maybe in stack of 1)
        //*update length and offset to be that of highest length instance       //hope 2 fix strange problem
        //*use that for Clen,off when writing into delta file (if all same length just use earliest offset)
        
        //*if(!temp.empty()) {lastWasAdd = false;print and empty temp queue/string in order from front to back b4 copy cmd}
        
        //*inc offset by length
        //*recheck N-byte seq from #3
        
        
        if(i <= newfString.size() - N && !values.empty())  //if using findable i and had 1+ matches too COPY
        //If you find this sequence in the table, you know that that sequence is present in both the old and new versions of the file.
        {
            size_t F(*(values.begin())), L(N);  //offset is set as first offset value found; length set as N
            stack<size_t> FcorrespondingOffset;
                FcorrespondingOffset.push(F);
            stack<size_t> LmaxMatch;
                LmaxMatch.push(L);
            // Determine how long the match goes on (it might be just N bytes long, or it might extend past the first N matching bytes to be many bytes longer).
            for(int oldfOffset : values) //for each int/offset in values
            {
                //find max match and store in string; will tell us length with .size() & offset is v
                    //--> if needing saving it will go into the if loop
                
                size_t oldPastN = oldfOffset+N;
                size_t iPastN = i+N;
                F = oldfOffset; //offset stays at the current offset being checked, only pushed onto F stack if L > any previous L value (top of L stack)
                L = N;  //only changed if match is longer and only pushed if larger than top of L stack
                
                while((oldfString[oldPastN] == newfString[iPastN]) && oldPastN < oldfString.size() && iPastN < newfString.size()) //as long as strings keep matching
                    //what if it matches past newfString.size() - N... cap indices at shorter string
                {
                    L ++;   //inc length by one each time one char matches
                    
                    oldPastN++; //inc indices of each
                    iPastN++;
                }
                
                
                if(L > LmaxMatch.top())
                        //only if matched string size is large than previously matched string size
                {
                    LmaxMatch.pop();
                    LmaxMatch.push(L);      //push on new longer size
                    
                    FcorrespondingOffset.pop();
                    FcorrespondingOffset.push(F);   //push on new offset at which longer size occurs
                }
            }
            
            //First stream out the remanent Add text and cmd if any
            if(!oldAddText.empty())
            {
                deltaf << "A" << oldAddText.size() << ":" << oldAddText;
                
                oldAddText = "";
                lastWasAdd = false;
            }
            
            //Then stream out Copy cmd
            // Once you have determined how long the match is (call this L), write a Copy instruction to the delta file to copy L bytes from offset F from the source file.
            
            deltaf << "C" << LmaxMatch.top() << "," << FcorrespondingOffset.top();
            
            i = i + LmaxMatch.top();  // Go back to step 3a, continuing at offset i = i + L in the new file's string.
        }
        
        
        //3c: IF NOT FOUND: add it into delta file manually
        //*IF NOT IN TABLE: push char onto queue OR write into string temp            //hope 2 fix mult. one char additions
        //push onto temp queue or string & lastWasAdd = true
        //*inc offset by 1
        //recheck N-byte sequence from #3
        else if(i <= newfString.size() - N && values.empty()) //if using findable i and not found in table ADD
        {
            oldAddText += NSeqNew1[0];
            lastWasAdd = true;
            
            i += 1;     // Go back to step 3a, where we'll try to find the next N-byte sequence in our table at i += 1.
        }
    }
    
    
//4: After 3b and after 3 loop housekeeping
    
    //4a: print what's left in newfString's string AFTER printing any last cmds that were add commands that never got popped off
        //*if(!temp.empty()) {print temp};
    
}


//APPLYDELTA:  The function returns true if the operation succeeds. If it fails because the delta file is malformed (e.g., there's a character other than an A or C where a command is expected, or an offset or length is invalid), the function returns false. If the function returns false, the caller can make no assumption about what may or may not have been written to the output destination (so you're free to, for example, just return false as soon as you detect an error, without regard to what you may have already written).
// Other than the output required to be written to its third parameter, neither function may write to any destination other than cerr (presumably for debugging purposes). Our testing program will ignore anything you write to cerr.

// applyDelta: This function takes the content of a file A and a delta file, and will apply the instructions in the delta file to produce a new file A'. Each day, every device will use this function to update the previous day's inventory file.


bool getInt(istream& inf, int& n)   //sets n (offset)
{
    char ch;
    if (!inf.get(ch)  ||  !isascii(ch)  ||  !isdigit(ch))   //check it first
        return false;
    inf.unget();    //then get it to store into n
    inf >> n;
    
    if(n < 0)
        return false;   //only want 0+ lengths/offsets
    return true;
}

bool getCommand(istream& inf, char& cmd, int& length, int& offset)  //sets length/offset/cmd for you
{
    if (!inf.get(cmd)  ||  (cmd == '\n'  &&  !inf.get(cmd)) )   //sets cmd's char to whatever is next in input stream
        //current char DNE OR char is \n and value after DNE
    {
        cmd = 'x';  // signals end of file
        return true;
    }
    char ch;
    switch (cmd) //if cmd's char is A or C
    {
        case 'A':
            return getInt(inf, length) && inf.get(ch) && ch == ':';
        case 'C':
            return getInt(inf, length) && inf.get(ch) && ch == ',' && getInt(inf, offset);  //calls to getInt DOES alter the input stream
    }
    return false; //else cmd is invalid
}

//if next char is : subtract A from addText string, if , subtract C. If none, do nothing.


bool applyDelta(istream& oldf, istream& deltaf, ostream& newf)
{
    string oldfString = readFile(oldf);             //translates files into long single strings
    char cmd;
    int length2(-1), offset2(-1);  //for 'x' condition at end
                            //not all cmds will start with A or C --> iterate thru while loop

   
    while(deltaf.get(cmd))  // To read the next character from the input, whether it's a letter, blank, newline, or whatever, that will be set to cmd (as long as not end of file yet, do following with character)
    {
        deltaf.unget();
        int length(-1), offset(-1);          //not all cmds will start with A or C --> iterate thru while loop
        if(getCommand(deltaf,cmd,length,offset))  //if char is A or C and followed by : and , respectively (or end of file char 'x')                 //has to be # after it, checked by being a true output for getCommand (in getInt fxn from getCommand fxn)

        {
            if(length == 0)
                return false;
            
            if(cmd == 'A')  //if Add command
            {
                char newChar;
                for(int i = 0; i < length; i++) //add for as long as you don't hit desired length
                {
                    if(deltaf.get(newChar))    //do get on deltaf after calling getCommand, then newChar will be first new char needing to be added manually!
                        {newf << newChar;}
                    else
                        goto END;            //if it can't get due to invalid offset or length, return false
                }

            }
                
            else if(cmd == 'C')  //if Copy command (C len,offset) //what if C len offset, offse
            {
                char copyChar;
                oldf.seekg(offset);            //copy chars from oldf to newf using offset and length
                for(int i = 0; i < length; i++)
                {
                    if(oldf.get(copyChar))  //get char from old file stream
                        {newf << copyChar;}
                    else
                        goto END;            //if it can't get due to invalid offset or length, return false
                }

            }
        }

    }
    
    //after while loop thru all cmds, end of file case: if passed thru all steps cmd was set to x
    if(getCommand(deltaf,cmd,length2,offset2) && cmd == 'x')  //if char is A or C and followed by : and , respectively (or end of file char 'x')
        {return true;}
    
    END:
    return false;   //if .get fails or
}

//read from old f only bits u need, sometimes 'stuff u need-garbage-stuff u need' --> 'garbage-stuff u need'
//then how to deal with old offset? do we unget the stuff we need..

//will offsets from L to R always be increasing? (will an old offset ever need to be used??)
// --> want to be able to use old offsets