#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

class TOPOLOGY{
public:
    int u;
    int v;

    TOPOLOGY(int u, int v){
        this->u = u;
        this->v = v;
    }
};

int N;
vector<vector<TOPOLOGY>> graph;

void addEdge(){

}


void topoDFS(int src, vector<bool> &vis, stack<int> &st)
{
    vis[src] = true;
    for (Edge e : graph[src])
    {
        if (!vis[e.v])
            topoDFS(e.v, vis, st);
    }

    st.push(src);
}

void topologicalSort()
{
    vector<bool> vis(N, false);
    stack<int> st;

    for (int i = 0; i < N; i++)
    {
        if (!vis[i])
            topoDFS(i, vis, st);
    }
}

void kahnsAlgo()
{

    vector<int> indegre(N, 0);
    for (int i = 0; i < N; i++)
    {
        for (Edge e : graph[i])
            indegre[e.v]++;
    }

    queue<int> que;
    vector<int> ans;

    for (int i = 0; i < N; i++)
    {
        if (indegre[i] == 0)
            que.push(i);
    }

    while (que.size() != 0)
    {
        int rvtx = que.front();
        que.pop();

        ans.push_back(rvtx);
        for (Edge e : graph[rvtx])
        {
            if (--indegre[e.v] == 0)
                que.push(e.v);
        }
    }

    if (ans.size() != N)
        cout << "There is a Cycle:" << endl;
    else
    {
        for (int ele : ans)
            cout << ele << " ";
    }
}
