#include <cstdio>
#include <cstdlib>

class ElectricChess
{
  private:
    char letters[8]={'A','B','C','D','E','F','G','H'};

  public:
    void Init();
    char* Quadrant2Char(int x, int y);
};

void ElectricChess::Init()
{
}

char* ElectricChess::Quadrant2Char(int x, int y)
{
    //x -> a-h
    //y -> 1-8
    char* str;
    sprintf(str,"%c%d",letters[x],y);
    return str;
}