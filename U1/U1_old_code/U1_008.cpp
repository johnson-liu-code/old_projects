#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <typeinfo>
#include <iostream>
#include <complex>
#include <vector>
#include <string>
using namespace std;


// Returns a vector with the dimension lengths.
vector<int> user_dimensions(string L)
{
    string delim = "x";

    vector<int> dimension_lengths;
    int index = 0;

    int start = 0U;
    int end = L.find(delim);
    
    while (end != string::npos)
    {
        dimension_lengths.push_back(stoi(L.substr(start, end - start)));
        start = end + delim.length();
        end = L.find(delim, start);
        index++;
    }
    dimension_lengths.push_back(stoi(L.substr(start, end - start)));

    return dimension_lengths;
}

// Represents a site that contains links.
struct site
{
    vector<double> link;
};

// Initialize lattice.
void initialize_lattice(site lattice[], int lattice_size, int number_of_dimensions, double init_angle)
{
    int i = 1;
    for (int s = 0; s < lattice_size; s++)
    {
        for (int l = 0; l < number_of_dimensions; l++)
        {
            lattice[s].link.push_back(1);
            i++;
//            lattice[s].link.push_back(init_angle);
        }
    }
}

// Print out links of the lattice.
void print_lattice(site lattice[], int lattice_size, int number_of_dimensions)
{
    for (int i = 0; i < lattice_size; i++)
    {
        for (int l = 0; l < number_of_dimensions; l++)
        {
            cout << "link: " << i << ", angle: " << lattice[i].link[l] << endl;
            cout << "++++++++++++++++++++++++++++++" << endl;
        }
    }
}

// Go forward in one direction.
int looper_forward(int index, vector<int> dimension_lengths, int direction)
{
    int divisor = 1;
    int multiple = 1;
    
    for (int i = 0; i <= direction; i++)
        {
            divisor = divisor * dimension_lengths[i];
        }
    for (int i = 0; i < direction; i++)
        {
            multiple = multiple * dimension_lengths[i];
        }
    
    if (direction == 0)
    {
        if ( index % dimension_lengths[direction] == 0 )
        {
            index = index - (dimension_lengths[direction] - 1);
        }
        else
        {
            index = index + 1;
        }
    }
    else
    {
        if ( (index % divisor > (dimension_lengths[direction] - 1 ) * multiple) || (index % divisor == 0) )
        {
            index = index - (dimension_lengths[direction] - 1) * multiple;
        }
        else
        {
            index = index + multiple;
        }
    }

    return index;
}

// Go backwards in one direction.
int looper_backward(int index, vector<int> dimension_lengths, int direction)
{
    int divisor = 1;
    int multiple = 1;

    for (int i = 0; i <= direction; i++)
        {
            divisor = divisor * dimension_lengths[i];
        }
    for (int i = 0; i < direction; i++)
        {
            multiple = multiple * dimension_lengths[i];
        }
    if (direction == 0)
    {
        if ( ( (index - 1) % dimension_lengths[direction] ) == 0 )
        {
            index = index + (dimension_lengths[direction] - 1);
        }
        else
        {
            index = index - 1;
        }
    }
    else
    {
        if ( index % divisor <= multiple && index % divisor != 0 )
        {
            index = index + (dimension_lengths[direction] - 1) * multiple;
        }
        else
        {
            index = index - multiple;
        }
    }

    return index;
}

// Collect the angles of staples.
double collect_angles(int index, vector<int> dimension_lengths, int direction, site lattice[])
{
    double staples = 0;

    for (int dir = 0; dir < dimension_lengths.size(); dir++)
    {
        if (dir != direction)
        {
            
            // Top staple.
//            cout << "*********TOP*********" << endl;
            int index_top = index;

            double b1 = -lattice[index_top-1].link[dir];
//            cout << "b1: " << b1 << endl;
            staples += b1;

            index_top = looper_forward(index_top, dimension_lengths, direction);
//            cout << "index top: " << index_top << endl;
            
            double c1 = lattice[index_top-1].link[dir];
//            cout << "c1: " << c1 << endl;
            staples += c1;

            index_top = looper_backward(index_top, dimension_lengths, direction);
            index_top = looper_forward(index_top, dimension_lengths, dir);
            double d1 = -lattice[index_top-1].link[direction];
//            cout << "d1: " << d1 << endl;
            staples += d1;

            // Bottom.
//            cout << "*********BOT*********" << endl;

            int index_bot = index;
            index_bot = looper_backward(index_bot, dimension_lengths, dir);
            double b2 = lattice[index_bot-1].link[dir];
//            cout << "b2: " << b2 << endl;
            staples += b2;
            
            double c2 = -lattice[index_bot-1].link[direction];
//            cout << "c2: " << c2 << endl;
            staples += c2;
            
            index_bot = looper_forward(index_bot, dimension_lengths, direction);
            double d2 = -lattice[index_bot-1].link[dir];
//            cout << "d2: " << d2 << endl;
            staples += d2;
        }
    }

    return staples;
}

double update(double U_angle, double staples, double beta, double scale)
{
    double theta = scale * 2 * ( drand48()-.5 );
    cout << "theta: " << theta << endl;
    double new_U_angle = fmod(U_angle + theta, 2*M_PI);

//    double new_U_angle = U_angle + theta;

//    while (abs(new_U_angle) > M_PI)
//    {
//        if (new_U_angle < -M_PI)
//        {
//            new_U_angle += 2*M_PI;
//        }
//        else if (new_U_angle > M_PI)
//        {
//            new_U_angle -= 2*M_PI;
//        }
//    }

    double old_action = cos(U_angle + staples);
    double new_action = cos(new_U_angle + staples);

//    cout << "old action: " << old_action << endl;
//    cout << "new action: " << new_action << endl;
//    cout << "exponential: " << exp(beta * (new_action - old_action)) << endl;

    if (new_action > old_action)
    {
        U_angle = new_U_angle;
//        cout << "accept new_action > old_action" << endl;
    }
    else
    {
        double r = drand48();

        if (r < exp(beta * (new_action - old_action)))
        {
            U_angle = new_U_angle;
//            cout << "accept r < exp(beta * (new - old))" << endl;
        }
        else
        {
//            cout << "reject exp: " << exp(beta * (new_action - old_action)) << endl;
        }
    }
    
    return U_angle;

}

double compute_plaquettes_at_site(int index, vector<int> dimension_lengths, int direction, site lattice[])
{
    int index_loop = index;
    double real_plaquettes_at_site = 0;
    
    for (int second_direction = direction + 1; second_direction < dimension_lengths.size(); second_direction++)
    {
        double a = lattice[index_loop-1].link[direction];
        double b = -lattice[index_loop-1].link[second_direction]; // minus
    
        index_loop = looper_forward(index_loop, dimension_lengths, direction);
//        cout << "next site: " << index_loop << endl;
        double c = lattice[index_loop-1].link[second_direction];
    
        index_loop = looper_backward(index_loop, dimension_lengths, direction);
//        cout << "next site: " << index_loop << endl;
    
        index_loop = looper_forward(index_loop, dimension_lengths, second_direction);
//        cout << "next site: " << index_loop << endl;
        double d = -lattice[index_loop-1].link[direction]; // minus

        real_plaquettes_at_site += cos(a+b+c+d);
    }

//    cout << "real plaquette: " << real_plaquettes_at_site << endl;

    return real_plaquettes_at_site;
}

void compute_polyakov_loop(site lattice[], vector<int> dimension_lengths, int lattice_size)
{
    int direction = 0;
    int time_length = dimension_lengths[0];
    int number_of_loops = 1;
    
    for (int d = 1; d < dimension_lengths.size(); d++)
    {
        number_of_loops *= dimension_lengths[d];
    }
    
    double sum_cos = 0;
    double sum_sin = 0;
    
    double sum_angle;
    int s;
    
    for (int n = 0; n < number_of_loops; n++)
    {
        s = (n*time_length) + 1;
        sum_angle = 0;
        for (int t = 1; t <= time_length; t++)
        {
            sum_angle += lattice[s].link[0];
            s = looper_forward(s, dimension_lengths, direction);
        }
        sum_cos += cos(sum_angle);
        sum_sin += sin(sum_angle);
    }

    double avg_real_polyakov = sum_cos/number_of_loops;
    double avg_imag_polyakov = sum_sin/number_of_loops;
    
//    cout << "avg real Polyakov: " << avg_real_polyakov << endl;
//    cout << "avg imag Polyakov: " << avg_imag_polyakov << endl;
}

int choose(int n, int k)
{
    if (k == 0)
    {
        return 1;
    }
    else
    {
        return (n * choose(n - 1, k - 1)) / k;
    }
}


int main(int argc, char* argv[])
{
    if (argc < 5)
    {
        cout << "Wrong number of arguments." << endl;
        return 1;
    }

    string L = argv[1];
    double beta = atof(argv[2]);
    double scale = atof(argv[3]);
    int traj_length = atof(argv[4]);
    
    double init_angle = 0;

//    srand48(time(NULL));

    vector<int> dimension_lengths = user_dimensions(L);
    int number_of_dimensions = dimension_lengths.size();    
    
    int lattice_size = 1;
    
    for (int i = 0; i < number_of_dimensions; i++)
    {
        lattice_size = lattice_size * dimension_lengths[i];
    }

    site lattice[lattice_size];
    initialize_lattice(lattice, lattice_size, number_of_dimensions, init_angle);

    double real_plaquettes_at_site;
    double number_of_plaquettes = choose(number_of_dimensions, 2) * lattice_size;

//    print_lattice(lattice, lattice_size, number_of_dimensions);

    double total_real_plaquettes = 0;

    for (int direction = 0; direction < number_of_dimensions; direction++)
    {
        // Iterate over sites.
        for (int s = 1; s <= lattice_size; s++)
        {
            if (direction < dimension_lengths.size() - 1)
            {
                real_plaquettes_at_site = compute_plaquettes_at_site(s, dimension_lengths, direction, lattice);
            }
            else
            {
                real_plaquettes_at_site = 0;
            }

            total_real_plaquettes += real_plaquettes_at_site;
        }
    }
        
    double avg_real_plaquettes = total_real_plaquettes / number_of_plaquettes;
        
    cout << "avg real plaquettes: " << avg_real_plaquettes << endl;
    cout << "*******************************************" << endl;

    // Iterate over number of frames.
    for (int traj = 1; traj <= traj_length; traj++)
    {
        double total_real_plaquettes = 0;

        // Iterate over directions.
        for (int direction = 0; direction < number_of_dimensions; direction++)
        {
            // Iterate over sites.
            for (int s = 1; s <= lattice_size; s++)
            {
                double staples = collect_angles(s, dimension_lengths, direction, lattice);
                
//                cout << "site: " << s << ", staples: " << staples << endl;
                
                double U_angle = lattice[s-1].link[direction];
//                cout << "angle: " << U_angle << endl;

                U_angle = update(U_angle, staples, beta, scale);

//                cout << U_angle << endl;
                
                lattice[s-1].link[direction] = U_angle;
            }
        }
        
        for (int direction = 0; direction < number_of_dimensions; direction++)
        {
            // Iterate over sites.
            for (int s = 1; s <= lattice_size; s++)
            {
                if (direction < dimension_lengths.size() - 1)
                {
                    real_plaquettes_at_site = compute_plaquettes_at_site(s, dimension_lengths, direction, lattice);
                }
                else
                {
                    real_plaquettes_at_site = 0;
                }

                total_real_plaquettes += real_plaquettes_at_site;
            }
        }
        
        double avg_real_plaquettes = total_real_plaquettes / number_of_plaquettes;

        cout << "avg real plaquettes: " << avg_real_plaquettes << endl;
                
        cout << "*******************************************" << endl;
    }
    
    return 0;
}