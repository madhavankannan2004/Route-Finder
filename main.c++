#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

// Function to find minimum cost of visiting subset of cities
int tsp_memo(vector<vector<int>> &dist, vector<bool> &visited, int currCity, int numCities, vector<vector<int>> &memo)
{
    if (numCities == 0)
    {
        return dist[currCity][1];
    }
    if (memo[currCity][numCities] != -1)
    {
        return memo[currCity][numCities];
    }
    int minCost = numeric_limits<int>::max();
    for (int nextCity = 1; nextCity < dist.size(); ++nextCity)
    {
        if (!visited[nextCity])
        {
            visited[nextCity] = true;
            int cost = dist[currCity][nextCity] + tsp_memo(dist, visited, nextCity, numCities - 1, memo);
            visited[nextCity] = false;
            minCost = min(minCost, cost);
        }
    }
    memo[currCity][numCities] = minCost;
    return minCost;
}

int tsp(vector<vector<int>> &dist, int numCities)
{
    vector<vector<int>> memo(dist.size(), vector<int>(1 << dist.size(), -1));
    vector<bool> visited(dist.size(), false);
    visited[1] = true; // Starting from city 1
    return tsp_memo(dist, visited, 1, numCities - 1, memo);
}

int main()
{
    int numCities;
    cout << "Enter the number of Cities: ";
    cin >> numCities;
    vector<vector<int>> dist(numCities + 1, vector<int>(numCities + 1, 0));
    cout << "Enter the distances between cities:" << endl;
    for (int i = 1; i <= numCities; ++i)
    {
        for (int j = 1; j <= numCities; ++j)
        {
            cin >> dist[i][j];
        }
    }
    cout << "Minimum cost of TSP tour: " << tsp(dist, numCities) << endl;
    return 0;
}
