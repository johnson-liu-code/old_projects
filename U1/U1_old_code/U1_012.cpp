#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <typeinfo>
#include <iostream>
#include <complex>
#include <vector>
#include <string>
using namespace std;


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

// Returns a vector with the dimension lengths.
vector<int> user_dimensions(string L)
{
    string delim = "x";

    vector<int> dimension_lengths;
    int index = 0;

    int start = 0;
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
    vector< complex<double> > link;
};

// Initialize lattice.
void initialize_lattice(site lattice[], int lattice_size, vector<int> dimension_lengths, double init_angle)
{

    int i = 1;
    int ii = 1;
    for (int s = 1; s <= lattice_size; s++)
    {
        for (int l = 0; l < dimension_lengths.size(); l++)
        {
//            lattice[s-1].link.push_back(complex<double> (cos((M_PI/2 * s), sin(M_PI/2 * s)));
//            cout << i << endl;
//            cout << ii << endl;

//            lattice[s-1].link.push_back(complex<double> (cos(M_PI/2), sin(M_PI/2)));
//            lattice[s-1].link.push_back(complex<double> (1.0, 0.0));
            lattice[s-1].link.push_back(complex<double> (cos(init_angle), sin(init_angle)));
//            lattice[s-1].link.push_back(complex<double> (cos(s), sin(s)));
//            if (l == 0)
//            {
//                lattice[s-1].link.push_back(complex<double> (1.0, 0.0));
//            }
//            else
//            {
//                lattice[s-1].link.push_back(complex<double> (cos(M_PI/2 * i), sin(M_PI/2 * i)));
//            }

//            lattice[s-1].link.push_back(complex<double> (cos(M_PI/2 * ii), sin(M_PI/2 * ii)));

        }
//        if (i == 8)
//        {
//            i = 1;
//            ii++;
//        }
//        else
//        {
//            i++;
//        }
    }


}

// Print out the links of the lattice.
void print_lattice(site lattice[], int lattice_size, int number_of_dimensions)
{
    for (int i = 0; i < lattice_size; i++)
    {
        for (int l = 0; l < number_of_dimensions; l++)
        {
            cout << "site: " << i << ", dir: " << l << ", complex: " << lattice[i].link[l] << endl;
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

// Collect the staples.
complex<double> get_staples(int index, vector<int> dimension_lengths, int direction, site lattice[])
{
    complex<double> staples(0.0, 0.0);

    for (int dir = 0; dir < dimension_lengths.size(); dir++)
    {
        if (dir != direction)
        {            
            int index_top = index;
            int index_bot = index;

            complex<double> b1 = conj(lattice[index_top-1].link[dir]);

            index_top = looper_forward(index_top, dimension_lengths, direction);
            
            complex<double> c1 = lattice[index_top-1].link[dir];

            index_top = looper_backward(index_top, dimension_lengths, direction);
            index_top = looper_forward(index_top, dimension_lengths, dir);
            
            complex<double> d1 = conj(lattice[index_top-1].link[direction]);
                        
            index_bot = looper_backward(index_bot, dimension_lengths, dir);

            complex<double> b2 = lattice[index_bot-1].link[dir];

            complex<double> c2 = conj(lattice[index_bot-1].link[direction]);

            index_bot = looper_forward(index_bot, dimension_lengths, direction);
            
            complex<double> d2 = conj(lattice[index_bot-1].link[dir]);

            staples += b1*c1*d1 + b2*c2*d2;
        }
    }

    return staples;
}

//void walker(int start, vector< vector<int> > path, site lattice[])
//{
//    for (int i = 0; i < path.size(); i++)
//    {
//        int direction = path[i][0];
//        int distance = path[i][1];
//        cout << "direction: " << direction << ", distance: " << distance << endl;
//    }
//}

complex<double> unitarize(complex<double> comp)
{
    complex<double> uni = comp / sqrt(conj(comp)*comp);
    return uni;
}
    
complex<double> update(complex<double> U, complex<double> staples, double beta, double scale)
{
    double theta = scale * 2 * ( drand48()-.5 );
    
    complex<double> U_change(cos(theta), sin(theta));
    
    complex<double> new_U = unitarize(U * U_change);

    double old_action = beta * (U*staples).real();
    double new_action = beta * (new_U*staples).real();

    if (new_action > old_action)
    {
        U = new_U;
    }
    else
    {
        double r = drand48();

        if (r < exp(new_action - old_action))
        {
            U = new_U;
        }
    }
    
    return U;
}

double compute_plaquettes_at_site(int index, vector<int> dimension_lengths, int direction, site lattice[])
{
    int index_loop = index;
    
    double real_plaquettes_at_site = 0;
    
    for (int second_direction = direction + 1; second_direction < dimension_lengths.size(); second_direction++)
    {
        complex<double> a = lattice[index_loop-1].link[direction];
        complex<double> b = conj(lattice[index_loop-1].link[second_direction]);

        index_loop = looper_forward(index_loop, dimension_lengths, direction);

        complex<double> c = lattice[index_loop-1].link[second_direction];

        index_loop = looper_backward(index_loop, dimension_lengths, direction);
        index_loop = looper_forward(index_loop, dimension_lengths, second_direction);

        complex<double> d = conj(lattice[index_loop-1].link[direction]);
        
        real_plaquettes_at_site += (a*b*c*d).real();
    }

    return real_plaquettes_at_site;
}

void compute_avg_plaquette(vector<int> dimension_lengths, int lattice_size, site lattice[])
{
    complex<double> real_plaquettes_at_site;
    complex<double> total_real_plaquettes = 0;
    
    int number_of_plaquettes = choose(number_of_dimensions, 2) * lattice_size;
    
    for (int direction = 0; direction < dimension_lengths.size(); direction++)
    {
        // Iterate over sites.
        for (int s = 1; s <= lattice_size; s++)
        {
            // Iterate over directions.
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
        
    cout << "PLAQ " << avg_real_plaquettes << " ";
}


complex<double>* update_polyakov(vector<int> dimension_lengths, site lattice[], complex<double>* polyakov_list)
{
    int time_dimension_position = dimension_lengths.size() - 1;
    
    complex<double> total_polyakov(0.0, 0.0);
    
    int spacial_dimension = 1;
    
    for (int s = 0; s < dimension_lengths.size(); s++)
    {
        spacial_dimension *= dimension_lengths[s];
    }
        
    complex<double> polyakov;
    complex<double> U;
    for (int i = 1; i <= spacial_dimension; i++)
    {
        polyakov = 1;
        int time_index = i;
        for (int t = 1; t <= dimension_lengths[time_dimension_position]; t++)
        {
//            U = lattice[time_index-1].link[time_dimension_position];
            polyakov *= lattice[time_index-1].link[time_dimension_position];
//            cout << "i: " << i << " t: " << t << " time_index: " << time_index << " U: " << U << endl;
            time_index = looper_forward(time_index, dimension_lengths, time_dimension_position);
        }
//        cout << i << " " << polyakov << endl;

        polyakov_list[i-1] = polyakov;

//        cout << polyakov_list[i-1] << endl;
        
        total_polyakov += polyakov;
    }
    
    double avg_polyakov_real = total_polyakov.real()/spacial_dimension;
    double avg_polyakov_imag = total_polyakov.imag()/spacial_dimension;

    double avg_polyakov = sqrt(total_polyakov.real()*total_polyakov.real() + total_polyakov.imag()*total_polyakov.imag()) / spacial_dimension;

//    cout << "POLY " << avg_polyakov_real << " " << avg_polyakov_imag << " " << avg_polyakov << endl;
    cout << "POLY " << avg_polyakov << endl;
    
    return polyakov_list;

}

//void compute_polyakov_pairs(vector<int> dimension_lengths, complex<double>* polyakov_list)
//{
//    int time_dimension_position = dimension_lengths.size() - 1;
//
//    int spacial_dimension = 1;
//    
//    for (int s = 0; s < dimension_lengths.size()-1; s++)
//    {
//        spacial_dimension *= dimension_lengths[s];
//    }
//    
//    complex<double> total_mult(0.0, 0.0);
//    
//    double num_of_pairs = 0;
//    
//    for (int i = 1; i <= spacial_dimension; i++)
//    {
//        complex<double> polyakov = polyakov_list[i-1];
//        for (int ii = i + 1; ii <= spacial_dimension; ii++)
//        {
//            complex<double> conj_polyakov = conj(polyakov_list[ii-1]);
//            complex<double> mult = polyakov * conj_polyakov;
//            total_mult += mult;
//            num_of_pairs++;
//        }
//    }
//    
//    complex<double> avg = total_mult / num_of_pairs;
//    
//    cout << "avg mult: " << avg << endl;
//}


//void compute_polyakov_pairs(vector<int> dimension_lengths, complex<double>* polyakov_list)
//{
//    int ind = 0;
//    int l_dimension = 1;
//    
//    for (int d = 0; d < dimension_lengths.size() - 1; d++ )
//    {
//        for (int m = 0; m < dimension_lengths[d]; m++)
//        {
////            cout << m << endl;
//        }
//    }
//}


void compute_polyakov_pairs(vector<int> dimension_lengths, complex<double>* polyakov_list)
{
    int spacial_dimension = 1;
    
    for (int s = 0; s < dimension_lengths.size()-1; s++)
    {
        spacial_dimension *= dimension_lengths[s];
    }
    
    complex<double> origin_poly = polyakov_list[0];
    
    for (int i = 0; i < spacial_dimension; i++)
    {
        int sum_of_squares = 0;
        int leng = 1;
        
        for (int d = 0; d < dimension_lengths.size()-1; d++)
        {
            int m = i / leng;
            int mm = m % dimension_lengths[d];
            
            sum_of_squares += mm*mm;
            
            leng *= dimension_lengths[d];
        }
        
        double r = sqrt(sum_of_squares);
        
        complex<double> other_poly = polyakov_list[i];
        
        complex<double> PP = origin_poly * conj(other_poly);

        cout << "r: " << r << "pair: " << PP << endl;
        
    }
    
}


double* fillarr(double* arr)
{
    arr[0] = 2;
    return arr;
}




int main(int argc, char* argv[])
{
    if (argc < 6)
    {
        cout << "Wrong number of arguments." << endl;
        return 1;
    }

    string L = argv[1];
    double beta = atof(argv[2]);
    double scale = atof(argv[3]);
    int traj_length = atof(argv[4]);
    int meas = atof(argv[5]);

    
    double init_angle = 0;

    vector<int> dimension_lengths = user_dimensions(L);
    int number_of_dimensions = dimension_lengths.size();

    int lattice_size = 1;
    
    for (int i = 0; i < number_of_dimensions; i++)
    {
        lattice_size = lattice_size * dimension_lengths[i];
    }
    
    site lattice[lattice_size];
    initialize_lattice(lattice, lattice_size, dimension_lengths, init_angle);

    double real_plaquettes_at_site;

    double total_real_plaquettes = 0;
    
//    print_lattice(lattice, lattice_size, number_of_dimensions);

    

    
    complex<double> polyakov_list[spacial_dimension];
    complex<double> *polyakov_list_pointer = update_polyakov(dimension_lengths, lattice, polyakov_list);

//    cout << "*******************************************" << endl;

    // Iterate over number of frames.
    for (int traj = 1; traj <= traj_length; traj++)
    {
        double total_real_plaquettes = 0;

        // Iterate over sites.
        for (int s = 1; s <= lattice_size; s++)
        {
            // Iterate over directions.
            for (int direction = 0; direction < number_of_dimensions; direction++)
            {
                complex<double> staples = get_staples(s, dimension_lengths, direction, lattice);
                complex<double> U = lattice[s-1].link[direction];
                U = update(U, staples, beta, scale);
                lattice[s-1].link[direction] = U;
            }
        }

//        if (traj % meas == 0)
//        {
//            // Iterate over sites.
//            for (int s = 1; s <= lattice_size; s++)
//            {
//                // Iterate over directions.
//                for (int direction = 0; direction < (number_of_dimensions - 1); direction++)
//                {
//                    real_plaquettes_at_site = compute_plaquettes_at_site(s, dimension_lengths, direction, lattice);
//                    total_real_plaquettes += real_plaquettes_at_site;
//                }
//            }
//        
//            double avg_real_plaquettes = total_real_plaquettes / number_of_plaquettes;
//
//            cout << "PLAQ " << avg_real_plaquettes << " ";
//            polyakov_list_pointer = update_polyakov(dimension_lengths, lattice, polyakov_list);
//            compute_polyakov_pairs(dimension_lengths, polyakov_list);
//
//        }
    }
    

//    double y[10];
//    double *a = fillarr(y);
//    cout << y[0] << endl;

//    a = fillarr(y);
//    cout << y[0] << endl;

//    y = a;

//    int lx = 4;
//    int ly = 3;
//    int lz = 2;
//    int i = 19;
//    
//    cout << i/lx << endl;
//    cout << i/(lx*ly) << endl;

//    cout << i % lx << endl;

    return 0;
}