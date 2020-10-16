#include <stdio.h>
#include <iostream>
#include <string>
#include <variant>
#include <vector>



class agent
{
public:
    void print_org_type()
    {
        std::cout << this->org_type << std::endl;
    }

    std::string org_type;
};

class bacteria: public agent
{
public:
    bacteria()
    {
        agent::org_type = "bacteria";
    }
};

class virus: public agent
{
public:
    virus()
    {
        agent::org_type = "virus";
    }
};

class Ecoli: public bacteria
{
public:
    Ecoli()
    {
        agent::org_type = "Ecoli";
    }
};

class bacteriovorus: public bacteria
{
public:
    bacteriovorus()
    {
        agent::org_type = "bacteriovorus";
    }
};


class location
{
public:
    location()
    {
    }

    void add( agent individual)
    {
        this->individual_list.push_back( individual );
    }

    void print_individuals()
    {
        for (int i = 0; i < individual_list.size(); i++)
        {
            individual_list[i].print_org_type();
        }
    }

private:
    std::vector< agent > individual_list;
};


int main()
{
    int x_len = 10;
    int y_len = 10;

    location field[x_len][y_len];

    for (int i = 0; i < x_len; i++)
    {
        for (int j = 0; j < y_len; j++)
        {
            virus virus_01;
            Ecoli Ecoli_01;
            bacteriovorus bact_01;
            bacteria bacteria_01;

            field[i][j].add( virus_01 );
            field[i][j].add( Ecoli_01 );
            field[i][j].add( bact_01 );
            field[i][j].add( bacteria_01 );

            field[i][j].print_individuals();
        }
    }

    for (int i = 0; i < x_len; i++)
    {
        for (int j = 0; j < y_len; j++)
       {
           //field[i][j].print_x();
           field[i][j].print_org_type();
       }
    }


}
