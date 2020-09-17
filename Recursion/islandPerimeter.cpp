int islandPerimeter(vector<vector<int>> &grid)
{
    int count = 0;
    int nbrs = 0;
    for (int i = 0; i < grid.size(); i++)
        for (int j = 0; j < grid[0].size(); j++)
        {
            if (grid[i][j] == 1)
            {
                count++;
                for (int d = 0; d < 4; d++)
                {
                    int r = i + dir[d][0];
                    int c = j + dir[d][1];

                    if (r >= 0 && c >= 0 && r < grid.size() && c < grid[0].size() && grid[r][c] == 1)
                        nbrs++;
                }
            }
        }


    return 4 * count - nbrs;
}
