========================================================================
    WIN32 APPLICATION : Win32Project15 Project Overview
========================================================================

AppWizard has created this Win32Project15 application for you.

This file contains a summary of what you will find in each of the files that
make up your Win32Project15 application.


Win32Project15.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

Win32Project15.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

Win32Project15.cpp
    This is the main application source file.

/////////////////////////////////////////////////////////////////////////////
AppWizard has created the following resources:

Win32Project15.rc
    This is a listing of all of the Microsoft Windows resources that the
    program uses.  It includes the icons, bitmaps, and cursors that are stored
    in the RES subdirectory.  This file can be directly edited in Microsoft
    Visual C++.

Resource.h
    This is the standard header file, which defines new resource IDs.
    Microsoft Visual C++ reads and updates this file.

Win32Project15.ico
    This is an icon file, which is used as the application's icon (32x32).
    This icon is included by the main resource file Win32Project15.rc.

small.ico
    This is an icon file, which contains a smaller version (16x16)
    of the application's icon. This icon is included by the main resource
    file Win32Project15.rc.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named Win32Project15.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" comments to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////


























#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

char ***mat;
int n = 0;
FILE *g = fopen("nume.out", "w");

void creare(char ****mat)
{
    
    char sir[5000],sir1[5000];
    char *p;
    FILE *f = fopen("nume.in", "r");
    

    while (!feof(f))
    {

        (*mat) = (char***)realloc((*mat),(n+1)*sizeof(char**));
        (*mat)[n] = NULL;
        (*mat)[n] = (char**)realloc((*mat)[n], (n + 1)*sizeof(char*)+1);

        fgets(sir, 5000, f);
        strcpy(sir1, sir);

        p = strtok(sir, "*");

        (*mat)[n][0] = NULL;
        (*mat)[n][1] = NULL;

        (*mat)[n][0] = (char*)malloc(sizeof(char)*(strlen(p) + 1));

        (*mat)[n][1] = (char*)malloc(sizeof(char)*(strlen(sir1) + 1));

        strcpy((*mat)[n][0], p);
        strcpy((*mat)[n][1], sir1);

        n++;


    }

}

int binarySearch(char ****mat,int l, int r)
{
    if (l>r)    
        return -1;

    int m = (l + r) / 2;
    


    if (strcmp((*mat)[m][0], "debita") == 0)
    {
        fprintf(g, "%s", (*mat)[m][1]);
        return -1;
    }

    if (strcmp((*mat)[m][0], "debita") <0)
        return  binarySearch(mat, m + 1, r);
    else
        return  binarySearch(mat, l, m);
}

        





void afisare(char ****mat)
{
    for (int i = 1; i < n; i++)
        printf("%s\n", (*mat)[i][1]);
    _getch();

}



void main()
{
    creare(&mat);
    binarySearch(&mat, 0, n - 1);
    _getch();
}