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
void initialize_lattice(site lattice[], int lattice_size, int number_of_dimensions, double init_angle)
{
    double i = 0;
    for (int s = 0; s < lattice_size; s++)
    {
        for (int l = 0; l < number_of_dimensions; l++)
        {
//            lattice[s].link.push_back(1);
//            lattice[s].link.push_back(init_angle);
//            lattice[s].link.push_back(complex<double> (cos(init_angle), sin(init_angle)));
//            lattice[s].link.push_back(complex<double> (cos(i), sin(i)));
            if (l == 0)
            {
                lattice[s].link.push_back(complex<double> (1.0, 0.0));
            }
            else
            {
                lattice[s].link.push_back(complex<double> (cos(M_PI/2 * i), sin(M_PI/2 * i)));
            }

//            double init = drand48();
//            lattice[s].link.push_back(complex<double> (cos(init), sin(init)));
        }
        i++;
    }
}

// Print out links of the lattice.
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

// Collect the angles of staples.
complex<double> collect_angles(int index, vector<int> dimension_lengths, int direction, site lattice[])
{
    complex<double> staples(1.0, 0.0);

    for (int dir = 0; dir < dimension_lengths.size(); dir++)
    {
        if (dir != direction)
        {
            cout << "########### index: " << index << ", direction: " << direction << ", dir: " << dir << "###########" << endl;
            // Top staple.
            cout << "*********TOP*********" << endl;
            int index_top = index;

//            complex<double> b1 = -lattice[index_top-1].link[dir];
            complex<double> b1 = conj(lattice[index_top-1].link[dir]);

            cout << "b1: " << b1 << endl;
            staples *= b1;

            index_top = looper_forward(index_top, dimension_lengths, direction);
            cout << "index top: " << index_top << endl;
            
            complex<double> c1 = lattice[index_top-1].link[dir];
            cout << "c1: " << c1 << endl;
            staples *= c1;

            index_top = looper_backward(index_top, dimension_lengths, direction);
            cout << "index top: " << index_top << endl;

            index_top = looper_forward(index_top, dimension_lengths, dir);
            cout << "index top: " << index_top << endl;
            
//            complex<double> d1 = -lattice[index_top-1].link[direction];
            complex<double> d1 = conj(lattice[index_top-1].link[direction]);
            cout << "d1: " << d1 << endl;
            staples *= d1;

            // Bottom.
            cout << "*********BOT*********" << endl;

            int index_bot = index;
            
            index_bot = looper_backward(index_bot, dimension_lengths, dir);
            cout << "index bot: " << index_bot << endl;

            complex<double> b2 = lattice[index_bot-1].link[dir];
            cout << "b2: " << b2 << endl;
            staples *= b2;
            
//            complex<double> c2 = -lattice[index_bot-1].link[direction];
            complex<double> c2 = conj(lattice[index_bot-1].link[direction]);
            cout << "c2: " << c2 << endl;
            staples *= c2;
            
            index_bot = looper_forward(index_bot, dimension_lengths, direction);
            cout << "index bot: " << index_bot << endl;
//            complex<double> d2 = -lattice[index_bot-1].link[dir];
            complex<double> d2 = conj(lattice[index_bot-1].link[dir]);

            cout << "d2: " << d2 << endl;
            staples *= d2;
        }
    }
    
//    cout << "site: " << index-1 << ", direction: " << direction << ", staples: " << staples << endl;

    return staples;
}

void walker(int start, vector< vector<int> > path, site lattice[])
{
    for (int i = 0; i < path.size(); i++)
    {
        int direction = path[i][0];
        int distance = path[i][1];
        cout << "direction: " << direction << ", distance: " << distance << endl;
    }
}


complex<double> update(complex<double> U, complex<double> staples, double beta, double scale)
{
    double theta = scale * 2 * ( drand48()-.5 );
//    cout << "theta: " << theta << endl;
    complex<double> U_change(cos(theta), sin(theta));
//    double new_U_angle = fmod(U_angle + theta, 2*M_PI);

//    cout << "U_change real: " << real(U_change) << ", U_change imag: " << imag(U_change) << endl;
//    cout << endl;

    complex<double> new_U = U * U_change;

//    cout << "new_U real: " << new_U.real() << ", new_U imag: " << new_U.imag() << endl;

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

//    double old_action = cos(U + staples);
//    double new_action = cos(new_U + staples);

    double old_action = (U*staples).real();
    double new_action = (new_U*staples).real();

//    cout << "old action: " << old_action << endl;
//    cout << "new action: " << new_action << endl;
//    cout << "exponential: " << exp(beta * (new_action - old_action)) << endl;

    if (new_action > old_action)
    {
        U = new_U;
//        cout << "accept new_action > old_action" << endl;
    }
    else
    {
        double r = drand48();

        if (r < exp(beta * (new_action - old_action)))
        {
            U = new_U;
//            cout << "accept r < exp(beta * (new - old))" << endl;
        }
        else
        {
//            cout << "reject exp: " << exp(beta * (new_action - old_action)) << endl;
        }
    }
    
    return U;

}

double compute_plaquettes_at_site(int index, vector<int> dimension_lengths, int direction, site lattice[])
{
    int index_loop = index;
    double real_plaquettes_at_site = 0;
    
//    cout << "site: " << index << endl;
//    cout << "dir: " << direction << endl;
    
    for (int second_direction = direction + 1; second_direction < dimension_lengths.size(); second_direction++)
    {
        complex<double> a = lattice[index_loop-1].link[direction];
//        complex<double> b = -lattice[index_loop-1].link[second_direction]; // minus
        complex<double> b = conj(lattice[index_loop-1].link[second_direction]);

        index_loop = looper_forward(index_loop, dimension_lengths, direction);
//        cout << "next site: " << index_loop << endl;
        complex<double> c = lattice[index_loop-1].link[second_direction];
    
        index_loop = looper_backward(index_loop, dimension_lengths, direction);
//        cout << "next site: " << index_loop << endl;
    
        index_loop = looper_forward(index_loop, dimension_lengths, second_direction);
//        cout << "next site: " << index_loop << endl;
//        complex<double> d = -lattice[index_loop-1].link[direction]; // minus
        complex<double> d = conj(lattice[index_loop-1].link[direction]);
        
//        cout << "a: " << a << ", b: " << b << ", c: " << c << ", d: " << d << endl;

//        cout << "a*b*c*d: " << a*b*c*d << endl;
//        cout << "site: " << index << ", plaquette: " << (a*b*c*d).real() << endl;
        
        real_plaquettes_at_site += (a*b*c*d).real();
    }

//    cout << "real plaquette: " << real_plaquettes_at_site << endl;

    return real_plaquettes_at_site;
}

//double compute_plaquettes_at_site(int index, vector<int> dimension_lengths, int direction, site lattice[])
//{
//    int index_loop = index;
//    double real_plaquettes_at_site = 0;
//    
////    cout << "site: " << index << endl;
////    cout << "dir: " << direction << endl;
//    
//    for (int second_direction = 0; second_direction < dimension_lengths.size(); second_direction++)
//    {
//        if (direction != second_direction)
//        {
//            complex<double> a = lattice[index_loop-1].link[direction];
////          complex<double> b = -lattice[index_loop-1].link[second_direction]; // minus
//            complex<double> b = conj(lattice[index_loop-1].link[second_direction]);
//
//            index_loop = looper_forward(index_loop, dimension_lengths, direction);
////          cout << "next site: " << index_loop << endl;
//            complex<double> c = lattice[index_loop-1].link[second_direction];
//    
//            index_loop = looper_backward(index_loop, dimension_lengths, direction);
////          cout << "next site: " << index_loop << endl;
//    
//            index_loop = looper_forward(index_loop, dimension_lengths, second_direction);
////          cout << "next site: " << index_loop << endl;
////          complex<double> d = -lattice[index_loop-1].link[direction]; // minus
//            complex<double> d = conj(lattice[index_loop-1].link[direction]);
//        
////          cout << "a: " << a << ", b: " << b << ", c: " << c << ", d: " << d << endl;
//
////          cout << "a*b*c*d: " << a*b*c*d << endl;
////          cout << "site: " << index << ", plaquette: " << (a*b*c*d).real() << endl;
//        
//            real_plaquettes_at_site += (a*b*c*d).real();
//        
//        }
//    }
//
////    cout << "real plaquette: " << real_plaquettes_at_site << endl;
//
//    return real_plaquettes_at_site;
//}

//int compute_number_of_plaquettes(vector<int> dimension_lengths)
//{
//    int number_of_plaquettes = 0;
//    for (int d = 0; d < dimension_lengths.size(); d++)
//    {
//        if (d < (dimension_lengths.size() - 1) )
//        {
//            number_of_plaquettes += dimension_lengths[d] * dimension_lengths[d+1];
//        }
//        else
//        {
//            number_of_plaquettes += dimension_lengths[d] * dimension_lengths[0];
//        }
//    }
//    
//    number_of_plaquettes *= dimension_lengths.size()-1;
//    
//    return number_of_plaquettes;
//}

//void compute_polyakov_loop(site lattice[], vector<int> dimension_lengths, int lattice_size)
//{
//    int direction = 0;
//    int time_length = dimension_lengths[0];
//    int number_of_loops = 1;
//    
//    for (int d = 1; d < dimension_lengths.size(); d++)
//    {
//        number_of_loops *= dimension_lengths[d];
//    }
//    
//    double sum_cos = 0;
//    double sum_sin = 0;
//    
//    double sum_angle;
//    int s;
//    
//    for (int n = 0; n < number_of_loops; n++)
//    {
//        s = (n*time_length) + 1;
//        sum_angle = 0;
//        for (int t = 1; t <= time_length; t++)
//        {
//            sum_angle += lattice[s].link[0];
//            s = looper_forward(s, dimension_lengths, direction);
//        }
//        sum_cos += cos(sum_angle);
//        sum_sin += sin(sum_angle);
//    }
//
//    double avg_real_polyakov = sum_cos/number_of_loops;
//    double avg_imag_polyakov = sum_sin/number_of_loops;
//    
////    cout << "avg real Polyakov: " << avg_real_polyakov << endl;
////    cout << "avg imag Polyakov: " << avg_imag_polyakov << endl;
//}

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
    
    double init_angle = 1;

//    srand48(time(NULL));

    vector<int> dimension_lengths = user_dimensions(L);
    int number_of_dimensions = dimension_lengths.size();
    
//    for (int i = 0; i < number_of_dimensions; i++)
//    {
//        cout << dimension_lengths[i] << endl;
//    }
//    cout << number_of_dimensions << endl;


    int lattice_size = 1;
    
    for (int i = 0; i < number_of_dimensions; i++)
    {
        lattice_size = lattice_size * dimension_lengths[i];
    }
    
//    cout << lattice_size << endl;

    site lattice[lattice_size];
    initialize_lattice(lattice, lattice_size, number_of_dimensions, init_angle);

    double real_plaquettes_at_site;
    int number_of_plaquettes = choose(number_of_dimensions, 2) * lattice_size;
//    int number_of_plaquettes = compute_number_of_plaquettes(dimension_lengths);

//    cout << number_of_plaquettes << endl;

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
//            cout << "plaquette: " << real_plaquettes_at_site << endl;
            
            total_real_plaquettes += real_plaquettes_at_site;
        }
    }
        
    double avg_real_plaquettes = total_real_plaquettes / number_of_plaquettes;
        
    cout << "avg real plaquettes: " << avg_real_plaquettes << endl;
    cout << "*******************************************" << endl;

//    int s = 1;
//    int direction = 0;
    
//    complex<double> staples = collect_angles(s, dimension_lengths, direction, lattice);
//    cout << "site: " << s << ", dir: " << direction << ", staples: " << staples << endl;

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
                complex<double> staples = collect_angles(s, dimension_lengths, direction, lattice);

//                cout << "site: " << s << ", staples: " << staples << endl;

                complex<double> U = lattice[s-1].link[direction];
//                cout << "angle: " << U << endl;

                U = update(U, staples, beta, scale);

//                cout << U << endl;
                
//                lattice[s-1].link[direction] = U;
            }
        }
        
        // Iterate over directions.
        for (int direction = 0; direction < (number_of_dimensions - 1); direction++)
        {
            // Iterate over sites.
            for (int s = 1; s <= lattice_size; s++)
            {
                real_plaquettes_at_site = compute_plaquettes_at_site(s, dimension_lengths, direction, lattice);
                total_real_plaquettes += real_plaquettes_at_site;
            }
        }
        
        double avg_real_plaquettes = total_real_plaquettes / number_of_plaquettes;

        cout << "avg real plaquettes: " << avg_real_plaquettes << endl;
                
        cout << "*******************************************" << endl;
    }
    
    
    vector< vector< int > > path = {{0, 2}, {1, -1}};
    int start = 0;
//    walker(start, path, lattice);

//    print_lattice(lattice, lattice_size, number_of_dimensions);

//    double theta = scale * 2 * ( drand48()-.5 );
//    cout << "theta: " << theta << endl;
//    complex<double> U_change(cos(theta), sin(theta));
//
////    cout << "U_change real: " << U_change.real() << ", U_change imag: " << U_change.imag() << endl;
//    cout << U_change;
//    cout << endl;
    
//    complex<double> new_U = U * U_change;

    return 0;
}