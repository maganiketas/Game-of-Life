#include "automaton.h"
#include <QDebug>

Automaton::Automaton(int w, int h)
{
    width = w;
    height = h;

    oldWorld = new bool*[width];
    newWorld = new bool*[width];
    for(int i = 0; i < width; i++)
    {
        oldWorld[i] = new bool[height];
        newWorld[i] = new bool[height];
    }

    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            oldWorld[i][j] = false;
            newWorld[i][j] = false;
        }
    }
}

Automaton::~Automaton()
{
    for(int i = 0; i < width; i++)
        delete [] oldWorld[i];
    delete [] oldWorld;
    oldWorld = nullptr;

    for(int i = 0; i < width; i++)
        delete [] newWorld[i];
    delete [] newWorld;
    newWorld = nullptr;
}

void Automaton::clearTable()
{
    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            oldWorld[i][j] = false;

            newWorld[i][j] = false;
        }
    }
}

int Automaton::getNeighborhood(int x, int y)
{
    int left = (x - 1 + width)%width;
    int top = (y - 1 + height)%height;

    int k = 0;

    for(int i = left; i < left + 3; i++)
    {
        for(int j = top; j < top + 3; j++)
        {
            int currX = (i + width)%width;
            int currY = (j + height)%height;

            if(oldWorld[currX][currY] && (currX != x || currY != y))
                k++;
        }
    }

    return k;
}

void Automaton::calcNewWorld()
{
    int i, j, k;
    for(i = 0; i < width; i++)
    {
        for(j = 0; j < height; j++)
        {
            k = getNeighborhood(i, j);
            if(oldWorld[i][j])
                if(k == 2 || k == 3)
                    newWorld[i][j] = true;
                else
                    newWorld[i][j] = false;
            else
                if(k == 3)
                    newWorld[i][j] = true;
        }
    }
    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            oldWorld[i][j] = newWorld[i][j];
        }
    }
}




