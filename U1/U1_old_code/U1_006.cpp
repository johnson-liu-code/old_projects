#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <typeinfo>
#include <iostream>
#include <complex>
#include <vector>
#include <string>
using namespace std;


int k = pow(7, 5);
int m = pow(2, 31) - 1;

double q = m/k;
int r = (m % k);
double r1;


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
    for (int i = 0; i < lattice_size; i++)
    {
        for (int l = 0; l < number_of_dimensions; l++)
        {
//            lattice[i].link.push_back(index);
//            lattice[i].link.push_back(init_angle*l);
//            lattice[i].link.push_back(2.0*M_PI*(drand48() - .5));
            lattice[i].link.push_back(init_angle);
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
vector< vector<double> > collect_angles(int index, vector<int> dimension_lengths, int direction, site lattice[])
{
    vector< vector<double> > staples;
    
    double a = lattice[index-1].link[direction];

    vector<double> common;
    common.push_back(a);

    staples.push_back(common);

    for (int dir = 0; dir < dimension_lengths.size(); dir++)
    {
        if (dir != direction)
        {
            // Top staple.
//            cout << "*********TOP*********" << endl;
//            cout << a << endl;
                
            vector<double> top_staple;
            
            int index_top = index;

            double b1 = -lattice[index_top-1].link[dir];
//            cout << b1 << endl;
            top_staple.push_back(b1);
    
            index_top = looper_forward(index_top, dimension_lengths, direction);
            double c1 = lattice[index_top-1].link[dir];
//            cout << c1 << endl;
            top_staple.push_back(c1);

            index_top = looper_backward(index_top, dimension_lengths, direction);
            index_top = looper_forward(index_top, dimension_lengths, dir);
            double d1 = -lattice[index_top-1].link[direction];
//            cout << d1 << endl;
            top_staple.push_back(d1);

    
            // Bottom.
//            cout << "*********BOT*********" << endl;
//            cout << a << endl;

            vector<double> bot_staple;
        
            int index_bot = index;
            index_bot = looper_backward(index_bot, dimension_lengths, dir);
            double b2 = lattice[index_bot-1].link[dir];
//            cout << b2 << endl;
            bot_staple.push_back(b2);
    
            double c2 = -lattice[index_bot-1].link[direction];
//            cout << c2 << endl;
            bot_staple.push_back(c2);
    
            index_bot = looper_forward(index_bot, dimension_lengths, direction);
            double d2 = -lattice[index_bot-1].link[dir];
//            cout << d2 << endl;
            bot_staple.push_back(d2);

            staples.push_back(top_staple);
            staples.push_back(bot_staple);
        }
    }
    
    return staples;
}

double update(vector< vector<double> > staples, double beta, double scale)
{    
    vector<double> accept_reject_result;
    
    double common = staples[0][0];
    double theta = scale * 2 * (drand48()-.5);
    double new_common = fmod(common + theta, M_PI/4);
//    cout << "new common: " << new_common << endl;
    
    double staple_angle_sum = 0;
    
    for (int i = 1; i < staples.size(); i++)
    {
        for (int j = 0; j < staples[i].size(); j++)
        {
            staple_angle_sum += staples[i][j];
        }
    }
        
    double old_action = cos(common + staple_angle_sum);
    double new_action = cos(new_common + staple_angle_sum);

    if (new_action > old_action)
    {
        common = new_common;
    }
    else
    {
        r = drand48();
    
        if (r < exp(beta * (new_action - old_action)))
        {
            common = new_common;
        }
    }

    return common;

}

double compute_plaquettes_at_site(int index, vector<int> dimension_lengths, int direction, site lattice[])
{
    int index_save = index;
    double real_plaquettes_at_site = 0;
    
    for (int second_direction = direction + 1; second_direction < dimension_lengths.size(); second_direction++)
    {
        double a = lattice[index_save-1].link[direction];
        double b = -lattice[index_save-1].link[second_direction]; // minus
    
        index_save = looper_forward(index_save, dimension_lengths, direction);
//        cout << "next site: " << index_save << endl;
        double c = lattice[index_save-1].link[second_direction];
    
        index_save = looper_backward(index_save, dimension_lengths, direction);
//        cout << "next site: " << index_save << endl;
    
        index_save = looper_forward(index_save, dimension_lengths, second_direction);
//        cout << "next site: " << index_save << endl;
        double d = -lattice[index_save-1].link[direction]; // minus
    
//        double real_plaquette = cos(a + b + c + d);
//        double imag_plaquette = sin(a + b + c + d);
    
//        vector<double> plaquette;
//        plaquette.push_back(real_plaquette);
//        plaquette.push_back(imag_plaquette);

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
    
    double common;
    double x1 = 19940910;
    double x2 = 1904991;
    vector<double> accept_reject_result;

    double init_angle = 0;

    srand48(time(NULL));

    vector<int> dimension_lengths = user_dimensions(L);
    int number_of_dimensions = dimension_lengths.size();    
    
    int lattice_size = 1;
    
    for (int i = 0; i < number_of_dimensions; i++)
    {
        lattice_size = lattice_size * dimension_lengths[i];
    }

    site lattice[lattice_size];
    initialize_lattice(lattice, lattice_size, number_of_dimensions, init_angle);

    vector< vector<double> > staples;
    double real_plaquettes_at_site;
    double number_of_plaquettes = choose(number_of_dimensions, 2) * lattice_size;

    // Iterate over number of frames.
    for (int traj = 0; traj < traj_length; traj++)
    {

        double total_real_plaquettes = 0;

        // Iterate over directions.
        for (int direction = 0; direction < number_of_dimensions; direction++)
        {
            // Iterate over sites.
            for (int s = 1; s <= lattice_size; s++)
            {
                staples = collect_angles(s, dimension_lengths, direction, lattice);
                
                common = update(staples, beta, scale);
                lattice[s-1].link[direction] = common;

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
//        cout << "avg real plaquettes: " << avg_real_plaquettes << endl;
        cout << avg_real_plaquettes << endl;
//        cout << "*************************************" << endl;
    }
    
    return 0;
}