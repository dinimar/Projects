#include "cd.h"
#include <cstring>
#include <iostream>

void Cd::InitCharArrays()
{
    for(size_t i=0; i<49; ++i)
        performers[i]='0';
    performers[49] = '\0';


    for(size_t i=0; i<19; ++i)
        label[i]='0';
    label[19] = '\0';
}

void Cd::CopyString(char * dest, char * src)
{
    // check that length of src string
    // equal or less to length of dest string
    // not including the null terminator
    if (std::strlen(src) <= std::strlen(dest))
    {
        std::strcpy(dest, src);
    }
    else if (std::strlen(src) > std::strlen(dest))
    {
        std::strncpy(dest, src, std::strlen(dest)-1);       // copy characters
        dest[std::strlen(dest)-1] = '\0';                   // the null terminator
    }
}

Cd::Cd(char * sPerformers, char * sLabel, int n, double x): selections(n), playtime(x)
{
    InitCharArrays();

    CopyString(performers, sPerformers);
    CopyString(label, sLabel);
}

Cd::Cd(): performers("No performers"), label("No label"), selections(0), playtime(0)
{}

// Cd::Cd(const Cd & cd)
// {
//     strcpy(performers, cd.performers);
//     strcpy(label, cd.label);
//     selections = cd.selections;
//     playtime = cd.playtime;
// }

void Cd::Report() const
{
    std::cout << "Performers: " << performers << std::endl;
    std::cout << "Label: " << label << std::endl;
    std::cout << "Selections: " << selections << std::endl;
    std::cout << "Playtime: " << playtime << std::endl << std::endl;
}
