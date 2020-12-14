#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>


class Agent
{
public:
    Agent()
    {
        this->org = "generic";
        // this->next = nullptr;
    }
    // Agent(int i, int j, std::string org, Agent* next = nullptr)
    Agent(int i, int j, std::string org)
    {
        this->i = i;
        this->j = j;
        this->org = org;
        // this->next = next;
    }

    void print_me()
    {
        std::cout << "Organism: " << this->org << std::endl;
        std::cout << "Location: " << this->i << "_" << this->j << std::endl;
    }

    void set_i(int i)
    {
        this->i = i;
    }
    void set_j(int j)
    {
        this->j = j;
    }
    void set_org(std::string org)
    {
        this->org = org;
    }

    int get_i()
    {
        return this->i;
    }
    int get_j()
    {
        return this->j;
    }
    std::string get_org()
    {
        return this->org;
    }
    // Agent* get_next()
    // {
    //     return this->next;
    // }

    int i;
    int j;
    std::string org;
    // Agent* next;
};

// class Virus
// {
// public:
//     Virus()
//     {
//         this->org = "virus";
//         this->next = nullptr;
//     }
//     Virus(int i, int j, std::string org, Virus* next = nullptr)
//     {
//         this->i = i;
//         this->j = j;
//         this->org = org;
//         this->next = next;
//     }
//
//     void print_me()
//     {
//         std::cout << "Organism: " << this->org << std::endl;
//         std::cout << "Location: " << this->i << "_" << this->j << std::endl;
//     }
//
//     void set_i(int i)
//     {
//         this->i = i;
//     }
//     void set_j(int j)
//     {
//         this->j = j;
//     }
//     void set_org(std::string org)
//     {
//         this->org = org;
//     }
//
//     int get_i()
//     {
//         return this->i;
//     }
//     int get_j()
//     {
//         return this->j;
//     }
//     std::string get_org()
//     {
//         return this->org;
//     }
//     Virus* get_next()
//     {
//         return this->next;
//     }
//
// private:
//     int i;
//     int j;
//     std::string org;
//     Virus* next;
// };
//
// class Virus_list
// {
// public:
//     Virus_list()
//     {
//         this->length = 0;
//         this->first = nullptr;
//         this->last = nullptr;
//     }
//
//     void print_list()
//     {
//         for(Virus* element = this->first; element != nullptr; element = element->get_next())
//         {
//             element->print_me();
//         }
//     }
//
//     void add_Virus(int i, int j, int num);
//     void delete_Virus(int target_position);
//     void destroy_list();
//
// private:
//     int length;
//     Virus* first;
//     Virus* last;
// };

class Ecoli: public Agent
{
public:
    Ecoli()
    {
        // this->org = "Ecoli";
        this->phage_resistant = false;
        this->bacteriovorus_resistant = false;
        // this->next = nullptr;
    }
    // Ecoli(int i, int j, std::string org, bool phage_resistant, bool bacteriovorus_resistant, Ecoli* next = nullptr)
    Ecoli(int i, int j, std::string org, bool phage_resistant, bool bacteriovorus_resistant)
    {
        // this->i = i;
        // this->j = j;
        this->org = org;
        this->phage_resistant = phage_resistant;
        this->bacteriovorus_resistant = bacteriovorus_resistant;
        // this->next = next;
    }

    void print_me()
    {
        // std::cout << "here2.1.1.1" << std::endl;
        std::cout << "Organism: " << this->org << std::endl;
        // std::cout << "here2.1.1.2" << std::endl;
        std::cout << "Location: " << this->i << "_" << this->j << std::endl;
        std::cout << "Phage resistant: " << this->phage_resistant << std::endl;
        std::cout << "Bacteriovorus resistant: " << this->bacteriovorus_resistant << std::endl;
        std::cout << "##########################################################################" << std::endl;
    }

    // void set_i(int i)
    // {
    //     this->i = i;
    // }
    // void set_j(int j)
    // {
    //     this->j = j;
    // }
    // void set_org(std::string org)
    // {
    //     this->org = org;
    // }
    void set_phage_resistant(bool phage_resistant)
    {
        this->phage_resistant = phage_resistant;
    }
    void set_bacteriovorus_resistant(bool bacteriovorus_resistant)
    {
        this->bacteriovorus_resistant = bacteriovorus_resistant;
    }
    // void set_next(Ecoli* next)
    // {
    //     this->next = next;
    // }

    // int get_i()
    // {
    //     return this->i;
    // }
    // int get_j()
    // {
    //     return this->j;
    // }
    // std::string get_org()
    // {
    //     return this->org;
    // }
    bool get_phage_resistant()
    {
        return this->phage_resistant;
    }
    bool get_bacteriovorus_resistant()
    {
        return this->bacteriovorus_resistant;
    }
    // Ecoli* get_next()
    // {
    //     return this->next;
    // }


private:
    // int i;
    // int j;
    // std::string org;
    bool phage_resistant;
    bool bacteriovorus_resistant;
    // Ecoli* next;
    // Agent* next;
};

// class Ecoli_list
// {
// public:
//     Ecoli_list()
//     {
//         this->length = 0;
//         this->first = nullptr;
//         this->last = nullptr;
//     }
//
//     void print_list()
//     {
//         // for(Ecoli* element = this->first; element != nullptr; element = element->get_next())
//         for(Agent* element = this->first; element != nullptr; element = element->get_next())
//         {
//             // std::cout << "here2.1.1" << std::endl;
//             element->print_me();
//             // std::cout << "here2.1.2" << std::endl;
//         }
//     }
//
//     void add_Ecoli(int i, int j, int num);
//     void delete_Ecoli(int target_position);
//     void destroy_list();
//
// private:
//     int length;
//     Ecoli* first;
//     Ecoli* last;
// };

// void Ecoli_list::destroy_list()
// {
//     // Ecoli* temp_ptr = nullptr;
//
//
//     int count = 0;
//
//     while (this->first != nullptr)
//     {
//         temp_ptr = this->first;
//         this->first = this->first->get_next();
//         if (temp_ptr != nullptr)
//         {
//             // std::cout << "count: " << count << std::endl;
//             delete temp_ptr;
//             count++;
//         }
//     }
// }

// void Ecoli_list::add_Ecoli(int i, int j, int num = 0)
// {
//     Ecoli* newNode = new Ecoli;
//     newNode->set_org("Ecoli_" + std::to_string(i) + "_" + std::to_string(j) + "_" + std::to_string(num));
//     newNode->set_i(i);
//     newNode->set_j(j);
//     newNode->set_next(nullptr);
//
//     if (this->first == nullptr)
//     {
//         this->first = newNode;
//     }
//     else
//     {
//         this->last->set_next(newNode);
//     }
//
//     this->last = newNode;
//
//     this->length++;
// }

// void Ecoli_list::delete_Ecoli(int target_position)
// {
//
//     if (this->length == 0)
//     {
//         return;
//     }
//
//     if ( (this->length == 1) || (target_position == 0) )
//     {
//         Ecoli* temp_ptr = nullptr;
//         temp_ptr = this->first;
//         this->first = nullptr;
//         delete temp_ptr;
//     }
//     else
//     {
//         Ecoli* previous_position = nullptr;
//         Ecoli* current_position = nullptr;
//         current_position = this->first;
//
//         for(int i = 0; i < target_position; i++)
//         {
//             previous_position = current_position;
//             current_position = current_position->get_next();
//         }
//         previous_position->set_next(current_position->get_next());
//
//         delete current_position;
//     }
//
//     this->length--;
// }

class location
{
public:
    location()
    {

    }

    location(int i, int j, int num_ecoli)
    {
        for (int x = 0; x < i; x++)
        {
            for (int y = 0; y < j; y++)
            {
                Ecoli ecoli = Ecoli();
                ecoli.set_org()
                // ecoli_list.push_back();
            }

        }
    }

    // location(int i, int j, int num_ecoli)
    // {
    //     this->num_ecoli = num_ecoli;
    //     for(int n = 0; n < this->num_ecoli; n++)
    //     {
    //         // std::cout << "here3" << std::endl;
    //         this->ecoli_list.add_Ecoli(i, j, n);
    //     }
    // }

    // Ecoli_list get_ecoli_list()
    // {
    //     return this->ecoli_list;
    // }
    //
    // void print_ecoli_list()
    // {
    //     // std::cout << "here2.1" << std::endl;
    //     this->ecoli_list.print_list();
    // }
    //
    // void destroy_ecoli_list()
    // {
    //     this->ecoli_list.destroy_list();
    // }

private:
    int num_ecoli;
    std::vector<Ecoli> ecoli_list;
    // Ecoli_list ecoli_list;
    // Virus_list virus_list;
};


int main()
{
    int x_len = 2;
    int y_len = 2;

    location field[x_len][y_len];

    int init_ecoli_in_cell = 4;
    int init_virus_in_cell = 3;

    // Ecoli_list ecoli_list;
    // ecoli_list.add_Ecoli(0);
    // ecoli_list.add_Ecoli(1);
    // ecoli_list.add_Ecoli(2);
    // ecoli_list.print_list();

    // std::cout << "########################################################" << std::endl;
    // ecoli_list.delete_Ecoli(2);
    // ecoli_list.delete_Ecoli(1);
    // ecoli_list.delete_Ecoli(0);
    // ecoli_list.print_list();

    // ecoli_list.~Ecoli_list();

    // std::cout << "here1" << std::endl;

    for (int i = 0; i < x_len; i++)
    {
        for (int j = 0; j < y_len; j++)
        {
            field[i][j] = location(i, j, init_ecoli_in_cell);
            // std::cout << "here2" << std::endl;
            // field[i][j].print_ecoli_list();
            // std::cout << "here4" << std::endl;
            // field[i][j].get_ecoli_list().print_list();
        }
    }

    // std::cout << "here4" << std::endl;

    for (int i = 0; i < x_len; i++)
    {
        for (int j = 0; j < y_len; j++)
       {
           // field[i][j].print_ecoli_list();
           // std::cout << "here4.1" << std::endl;
           // field[i][j].destroy_ecoli_list();
           // std::cout << "here4.2" << std::endl;
           // field[i][j].destroy_ecoli_list();
           // std::cout << "here4.3" << std::endl;
       }
    }

    // std::cout << "here5" << std::endl;


}
