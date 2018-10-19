#include <vector>
#include <iostream>

/**
    Class happyVoters accepts a bipartite graph to figure the maximum amount of
    compatible matches.
    The bipartite graph contains matches for incompatible votes. The maximum count
    of incompatible votes is subtracted from the total count of votes, to find the
    maximum amount of compatible matches
**/
class HappyVoters
{
public:

    //  Constructor accepts a bipartite graph as variable 'bpGraph' and its size 'n' and 'm'
    HappyVoters(std::vector<std::vector<bool> > bpGraph, int n, int m)
    {
        bipartiteGraph = bpGraph;
        N = n;
        M = m;
        match = std::vector<int> (M, -1);
    }

    //  Function that finds maximum count of compatible matches from a bipartite graph
    //  return the count of maximum compatible matches
    int maximumHappyVoters()
    {
        int maxMatch = 0;
        //  search through the bipartite graph to find matches, in each row do DFS, and increase variable 'maxMatch' when a new match is found
        for (int i = 0; i < N; i++)
        {
          visited = std::vector<int> (M, 0);
          if (DFS(i))
          {
              maxMatch++;
          }
        }
        return N + M - maxMatch;
    }

private:

    //  size of bipartite graph, 'N' for rows, 'M' for columns
    int N, M;
    //  variable 'visited' is for visited elements in each row
    //  variable 'match' stores a match, as such. Number of index is for the row number and the value for column
    std::vector<int> visited, match;
    std::vector<std::vector<bool> > bipartiteGraph;

    //  Search recursively for a match in each column, for a specific row in the bipartite graph
    bool DFS(int i)
    {
        for (int k = 0; k < M; k++)
        {
            //  when the bipartite graph has a match and has not been visited check for a match
            if (bipartiteGraph[i][k] && !visited[k])
            {
                visited[k] = true;
                if (match[k] < 0 || DFS(match[k]))
                {
                    match[k] = i;
                    return true;
                }
            }
        }
        return false;
    }
};




//  Receive input from user and enter into vector reference variables
void receiveInput(std::vector<int> &catUpVote, std::vector<int> &catDownVote, std::vector<int> &dogUpVote, std::vector<int> &dogDownVote)
{
    int catContestants = 0;
    int dogContestants = 0;
    int votes = 0;
    char animalUpVote;
    char animalDownVote;
    int upVoteNo = 0;
    int downVoteNo = 0;

    std::cin >> catContestants >> dogContestants >> votes;

    for (int i = 0; i < votes; i++)
    {
        std::cin >> animalUpVote >> upVoteNo >> animalDownVote >> downVoteNo;
        if (animalUpVote == 'C')
        {
            catUpVote.push_back(upVoteNo);
            dogDownVote.push_back(downVoteNo);
        }
        else
        {
            dogUpVote.push_back(upVoteNo);
            catDownVote.push_back(downVoteNo);
        }
    }
}

/**
    Create and return a bipartite graph from four vectors in such a way:
    Create a bipartite graph full of zeros N*M, where 'N' is number of cat favored votes and 'M' is the number of dog favored votes
    compare catUpVote[i] to catDownVote[k], if they are comparable add a one to bipartiteGraph[i][k]
**/
std::vector<std::vector<bool> > createBipartiteGraph(std::vector<int> catUpVote, std::vector<int> catDownVote, std::vector<int> dogUpVote, std::vector<int> dogDownVote)
{
    int N = catUpVote.size();
    int M = dogUpVote.size();

    std::vector<std::vector<bool> > bipartiteGraph(N, std::vector<bool>(M, 0));

    for (int i = 0; i < N; i++)
    {
        for (int k = 0; k < M; k++)
        {
            if (catUpVote[i] == catDownVote[k] || dogUpVote[k] == dogDownVote[i])
            {
                bipartiteGraph[i][k] = 1;
            }
        }
    }
    return bipartiteGraph;
}

int main()
{
    int testCases = 0;

    std::cin >> testCases;

    for (int i = 0; i < testCases; i++)
    {
        std::vector<int> catUpVote, catDownVote, dogUpVote, dogDownVote;
        receiveInput(catUpVote, catDownVote, dogUpVote, dogDownVote);

        HappyVoters *h = new HappyVoters(createBipartiteGraph(catUpVote, catDownVote, dogUpVote, dogDownVote), catUpVote.size(), dogUpVote.size());

        std::cout << h->maximumHappyVoters() << std::endl;
    }

    return 0;
}
