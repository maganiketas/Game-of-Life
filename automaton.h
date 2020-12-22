#ifndef AUTOMATON_H
#define AUTOMATON_H


class Automaton
{
    bool **oldWorld;
    bool **newWorld;
    int width, height;
public:
    Automaton(int w, int h);
    ~Automaton();
    void setCell(int x, int y, bool value) { oldWorld[x][y] = value; }
    bool operator()(int i, int j){ return oldWorld[i][j]; }
    void clearTable();
    int getNeighborhood(int x, int y);
    void calcNewWorld();
};

#endif // AUTOMATON_H
