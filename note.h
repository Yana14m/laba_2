#pragma once 
#include "Route.h"

class Note {
    Route** route;
    int count;
public:
    Note();
    Note(Route** r, int c);
    Note(const Note& other);
    ~Note();

    void add(Route* item, int index);
    void remove(int index);
    void showAll() const;
    void edit(int index);
    void sort();
    void find(int num);
    void saveToFile(const std::string& file) const;
    void loadToFile(const std::string& file);

    Note& operator=(const Note& other);
};
