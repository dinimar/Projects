#include "cd.h"
#include <cstring>
#include <iostream>

Cd::Cd(char * sPerformers, char * sLabel, int n, double x): selections(n), playtime(x)
{
    performers = new char[std::strlen(sPerformers)+1];
    label = new char[std::strlen(sLabel)+1];

    std::strcpy(performers, sPerformers);
    std::strcpy(label, sLabel);
}

Cd::Cd():  selections(0), playtime(0)
{
    performers = new char[14];
    label = new char[8];

    std::strcpy(performers, "No performers");
    std::strcpy(label, "No label");
}

Cd::Cd(const Cd & cd): selections(cd.selections), playtime(cd.playtime)
{
    delete[] performers;
    delete[] label;

    performers = new char[std::strlen(cd.performers)+1];
    label = new char[std::strlen(cd.label)+1];

    std::strcpy(performers, cd.performers);
    std::strcpy(label, cd.label);
}


Cd & Cd::operator=(const Cd &cd)
{
    if (this != &cd)
    {
        delete[] performers;
        delete[] label;

        performers = new char[std::strlen(cd.performers)+1];
        label = new char[std::strlen(cd.label)+1];

        std::strcpy(performers, cd.performers);
        std::strcpy(label, cd.label);

        selections = cd.selections;
        playtime = cd.playtime;
    }

    return *this;
}

void Cd::Report() const
{
    std::cout << "Performers: " << performers << std::endl;
    std::cout << "Label: " << label << std::endl;
    std::cout << "Selections: " << selections << std::endl;
    std::cout << "Playtime: " << playtime << std::endl << std::endl;
}
