///MUSIC PLAYER APPLICATION beta 1.0
///Created by Anjum Rashid and Aparna Das
///Department of CSE, Jahangirnagar University

#include<iostream>
#include<Windows.h>
#include<MMSystem.h>
#include<graphics.h>
#include<iomanip>
#include<cstdio>
#include<cstring>
#include<stdlib.h>
#include<ctime>
#include<fstream>

using namespace std;

class Track
{
public:

    char title[50];
    char artist[20];
    char cover_title[50];
    int ID;

public:
    static int counter;  ///counter variable to initialize ID
    Track()              ///constructor
    {
        ID=++counter;
    }
    void getinput(char *text1,char *name,char *text2)
    {
        strcpy(title,text1);
        strcpy(artist,name);
        strcpy(cover_title,text2);
    }

    char* getdata_title()
    {
        return title;
    }

    int getdata_id()
    {
        return ID;
    }

    void DisplayCoverArt()  ///function for individual cover art display
    {
        char directory_str[60]="Album Covers\\";

        strcat(directory_str,cover_title);

        readimagefile(directory_str,0,0,500,500); ///links the image file with library
    }

    void PlayTrack() ///function to play individual track
    {
        char directory_str[60]="Audio Library\\";

        strcat(directory_str,title);    ///directory string to specify track directory

        cout<<"Now playing ... "<<title<<" by "<<artist<<endl;

        PlaySound(TEXT(directory_str),NULL,SND_SYNC); ///windows library function to play audio file, Text(directory) links the audio data with library
        // system("pause");
    }

    friend void DisplayInfo(class Track x);    ///DisplayInfo() can access private data
};

int Track::counter=0;  ///initializing static variable

class Audio_Library
{
public:
    Track t[50];  ///collection of tracks
} AudLib;         ///declaring global variable

class Favourites: public Track
{
private:
    int trackid;
    bool IsFavourite;
public:

    Favourites():trackid(0),IsFavourite(0) {}

    void AssignFavourites()
    {
        cout<<"Enter track id that you want to make favourite...";

        cin>>trackid;

        IsFavourite=1;
        cout<<"\nTrack "<<trackid<<" marked favourite!\n"<<endl;
    }

    void DisplayFavourites();

    friend void DisplayInfo(class Track,int&);

} f[15];    ///global objects of favourite class

void DisplayInfo(class Track x,int& markid)
{
    cout<<left<<setw(4)<<x.ID;
    cout<<left<<setw(25)<<x.title;
    cout<<left<<setw(17)<<x.artist;
    cout<<left<<setw(28)<<x.cover_title;

    for(int j=0; j<markid; j++)  ///display marked favourite tracks
    {
        if(x.ID == f[j].trackid)
        {
            cout<<"YES";
            break;
        }
    }
    cout<<endl;
}

void SearchID(int n,int& id) ///searches the track using ID and plays it
{
    initwindow(500,500,"***Music Player***");  ///display console initiate
    Sleep(500);
    for(int i=0; i<id; i++)   ///linear search
    {
        if(n == AudLib.t[i].getdata_id())
        {
            AudLib.t[i].DisplayCoverArt();
            AudLib.t[i].PlayTrack();
        }
    }
    closegraph(); ///terminates initwindow console
}

void Shuffle(int trackid)  ///function to shuffle and play all the tracks
{
    int num_of_tracks,random_id;  ///Max number of tracks in the library

    num_of_tracks=trackid;

    srand(time(NULL)); ///srand() seeds the random function with system time

    while(num_of_tracks>0)
    {
        //srand(time(NULL));

        random_id=(rand()%trackid)+1; ///random track id generated

        SearchID(random_id,trackid);
        --num_of_tracks;
    }
}

void AddTrack(int& trackid)  ///for custom track addition by user
{
    char temp1[30],temp2[30],temp3[30];
    getchar();                     ///to avoid unnecessary input

    cout<<"Enter Track Name: ";
    cin.getline(temp1,30);
    cout<<"Enter Artist Name: ";
    cin.getline(temp2,30);
    cout<<"Enter Cover Title: ";
    cin.getline(temp3,30);

    AudLib.t[trackid].getinput(temp1,temp2,temp3);
    trackid++;
    cout<<"\nNew track added in library!!"<<endl;
}

void ReadFromFile(int& trackid)       ///function to read track info
{
    char temp1[30],temp2[30],temp3[30];

    ifstream ReadInfo;              ///Readinfo object to read file from input stream
    ReadInfo.open("TrackInfo.txt");   ///File open

    if(ReadInfo.fail())                   ///File Error check
    {
        cerr<<"Error opening file!"<<endl;    ///Error message
        exit(1);
    }

    trackid=0;

    while(!ReadInfo.eof())
    {
        ReadInfo.getline(temp1,30,',');   ///track title
        ReadInfo.getline(temp2,30,',');   ///artist name
        ReadInfo.getline(temp3,30);       ///cover art

        AudLib.t[trackid].getinput(temp1,temp2,temp3);

        trackid++;
    }

    ReadInfo.close();  ///File close
}

void ASCII_ART()  ///Display ascii art in the console
{
   ifstream ArtIn;
   string s;
   ArtIn.open("ascii art.txt");

    if(ArtIn.fail())                   ///File Error check
    {
        cerr<<"Error opening image file!"<<endl;    ///Error message
        exit(1);
    }

    while(!ArtIn.eof())
    {
        getline(ArtIn,s,'$');
        cout<<s;
    }

}
int main()
{
    int choice,x,j;
    static int trackID;  ///trackID contains value of total number of tracks in the library


    ReadFromFile(trackID); ///Reads trackinfo
    printf("\a");           ///rings a bell
    ASCII_ART();    ///ascii art display
    cout<<endl;

    while(1)
    {
        system("color F4");
        cout<<"\nOperations -\n 1.Display Audio Library\n 2.Play Track\n 3.Shuffle & Play\n 4.Add Track\n 5.Mark Favourites\n 6.Exit"<<endl;

        cout<<"Enter Choice: ";
        cin>>choice;
        if(choice == 1)
        {
            cout<<"\n-----------------------A U D I O------------L I B R A R Y---------------------\n"<<endl;

            cout<<left<<setw(4)<<"ID"<<setw(25)<<"TITLE"<<setw(17)<<"ARTIST"<<setw(24)<<"COVER TITLE"<<setw(10)<<"FAVOURITE"<<endl<<endl;

            for(int i=0; i<trackID; i++)
            {
                DisplayInfo(AudLib.t[i],trackID);

            }
            cout<<endl;
        }
        else if(choice == 2)
        {
            cout<<"Enter track ID: ";
            cin>>x;
            if(x>trackID) cout<<"ID does not exist!\n"<<endl;
            else SearchID(x,trackID);
            Sleep(400);
            system("cls");       /// clears screen buffer

            ASCII_ART();
            cout<<endl;
        }
        else if(choice == 3)
        {
            cout<<"\nShuffling All Tracks ..."<<endl;
            Shuffle(trackID);
            system("cls");

            ASCII_ART();
             cout<<endl;
        }
        else if(choice == 4)
        {
            AddTrack(trackID);
        }
        else if(choice == 5)    ///Mark Favourites
        {
            char ch;
            j=0;
            while(j<trackID)
            {
                f[j].AssignFavourites();
                j++;

                cout<<"Do you want to assign another?(Y/N)"<<endl;
                cin>>ch;

                if(ch=='N' || ch=='n') break;
                else if(ch=='Y' || ch=='y') continue;
            }
        }
        else if(choice == 6) break;
        else cout<<"Invalid Operation!"<<endl;
    }
    return 0;
}
