

#include<vector>


std::vector<int> determine_ij(int i, int j, int x_len, int y_len)
{
    int i_up, i_down, j_left, j_right;

    if (x_len == 1)
    {
        i_up = 0;
        i_down = 0;
    }
    else
    {
        if (i == 0)
        {
            i_down = 1;
            i_up = x_len - 1;
        }
        else if (i == x_len - 1)
        {
            i_down = 0;
            i_up = i - 1;
        }
        else
        {
            i_down = i + 1;
            i_up = i - 1;
        }
    }
    if (y_len == 1)
    {
        j_left = 0;
        j_right = 0;
    }
    else
    {
        if (j == 0)
        {
            j_left = y_len - 1;
            j_right = 1;
        }
        else if (j == y_len - 1)
        {
            j_left = j - 1;
            j_right = 0;
        }
        else
        {
            j_left = j - 1;
            j_right = j + 1;
        }
    }

    std::vector<int> ij_coordinates = {i_up, i_down, j_left, j_right};

    return ij_coordinates;
}
