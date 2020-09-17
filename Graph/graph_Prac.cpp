#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

class Edge
{
public:
    int v;
    int w;

    Edge(int v, int w)
    {
        this->v = v;
        this->w = w;
    }
};

int N;
vector<vector<Edge>> graph;

void display()
{
    for (int i = 0; i < graph.size(); i++)
    {
        cout << i << " -> ";
        for (Edge e : graph[i])
            cout << "(" << e.v << ", " << e.w << ") ";
        cout << endl;
    }

    cout << endl;
}

//================================================================================================

void addEdge(int u, int v, int w)
{
    graph[u].push_back(Edge(v, w));
    // graph[v].push_back(Edge(u, w));
}

//================================================================================================

int searchVrtx(int u, int v)
{
    int idx = -1;
    for (int i = 0; i < graph[u].size(); i++)
    {
        Edge e = graph[u][i];
        if (e.v == v)
        {
            idx = i;
            break;
        }
    }

    return idx;
}

//===============================================================================================

void removeEdge(int u, int v){
    int idx = -1;
    idx = searchVrtx(u,v);
    graph[u].erase(graph[u].begin() + idx);

    idx = searchVrtx(v, u);
    graph[v].erase(graph[v].begin()  + idx);
}

//================================================================================================

void removeVrtx(int u){
    int size = graph[u].size();
    while(size-- > 0){
        Edge e = graph[u].back();
        removeEdge(u, e.v);
    }
}

//================================================================================================

bool hasPath(int src, int dest, vector<bool> &vis){
    if(src == dest){
        return true;
    }
    vis[src] = true;
    bool res = false;
     for(Edge e : graph[src]){
        if(!vis[e.v]){
            res = res || hasPath(e.v, dest, vis);
        }
     }
     return res;
}

//===============================================================================================

void topoDFS(int src, vector<int> &vis, stack<int> &st){
    vis[src] = true;
    for(Edge e : graph[src]){
        if(!vis[e.v]){
            topoDFS(e.v, vis, st);
        }
    }
    st.push(src);
}

void topoDFS_(){
    vector<bool> vis(N, false);
    stack<int> st;
    for(int i=0; i<N; i++){
        if(!vis[i]){
            topoDFS(i, vis, st);
        }
    }
}

//================================================================================================

void khansAlgo(){
    vector<int> indegree(N, 0);
    for(int i=0; i<N; i++){
        for(Edge e : graph[i]){
            indegree[e.v]++;
        }
    }

    queue<int> q;
    vector<int> ans;
    for(int i=0; i<N; i++){
        if(indegree[i] == 0){
            q.push(i);
        }
    }

    while(q.size() != 0){
        int rvtx = q.front();
        q.pop();

        ans.push_back(rvtx);

        for(Edge e : graph[rvtx]){
            if(--indegree[e.v] == 0){
                q.push(e.v);
            }
        }
    }
    if(ans.size() != N){
        cout<< "cycle" << endl;
    }
    else{
        for(int ele : ans){
            cout<< ele << endl;
        }
    }
}

//================================================================================================

void constrctGraph(){
    N = 7;
    graph.resize(N, vector<Edge>());
     // for (int i = 0; i < N; i++)
    // {
    //     vector<Edge> g;
    //     graph.push_back(g);
    // }

    addEdge(0, 1, 10);
    addEdge(1, 2, 10);
    addEdge(2, 3, 40);
    addEdge(3, 0, 10);
    addEdge(3, 4, 2);
    addEdge(4, 5, 2);
    addEdge(4, 6, 8);
    addEdge(5, 6, 3);
    addEdge(0, 6, 10);

    // display();
}

void solve(){
    constrctGraph();
    // cout<< searchVrtx(0, 4) << endl;

    // removeEdge(3, 4);
    // removeVrtx(3);

    // std::vector<bool> vis(N);
    // cout<< hasPath(0, 6, vis) << endl;
    // khansAlgo();

    vector<bool> vis;
    stack<int> st;
    topoDFS(0, vis, st);
    display();

}
int main(){
    solve();
    return 0;
}
