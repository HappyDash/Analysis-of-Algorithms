/******************************************************************************

                              

*******************************************************************************/

#include <bits/stdc++.h>
#include <time.h>

using namespace std;
class Edge {
    public:
        int vertex1;
        int vertex2;
        int weight;
        Edge(int v1, int v2, int w){
            vertex1=v1;
            vertex2=v2;
            weight=w;
        }   
};

class GenerateRandomGraph {
    public:
        int vertices;
        int edges;
        vector<vector<int> > adj;
        vector<Edge> graph;
        vector<Edge> getGraph(){
            return graph;
        }
        void addEdge(int v, int w, int weight){
            Edge e(v, w,weight);
            graph.push_back(e);
            adj[v].push_back(w);
            adj[w].push_back(v);
        }
        GenerateRandomGraph(){
            srand(time(NULL));
            cout<<"Enter number of vertices:"<<endl;
            cin>>vertices;
            cout<<"Enter number of edges (max edges can be vertices + 8):"<<endl;
            cin>>edges;
            while(edges > (vertices + 8)){
                cout<<"The number of edges exceeds the maximum limit. Please re-enter the number of edges"<<endl;
                cout<<"Enter the number of edges (max edges can be vertices + 8):"<<endl;
                cin>>edges;
            }
            for(int i=0;i<vertices;i++){
                adj.push_back(vector<int>());
            }
            for (int i = 0; i < edges; i++) {
                int v = rand()%(vertices);
                int w = rand()%(vertices);
                int weight = rand()%(10);

                while(v == w)  {
                    v = rand()%(vertices);
                    w = rand()%(vertices);
                }
                if(find(adj[v].begin(),adj[v].end(),w)==adj[v].end()){
                    addEdge(v, w,weight);
                }
            }
        }
};

bool sortDecreasing (Edge edge1,Edge edge2) { 
    return (edge1.weight>edge2.weight);
}

void dfs(int startNode, vector<vector<int> > adjacencyGraph, vector<bool> &visited) {
    visited[startNode] = true;
    for(int i=0; i<adjacencyGraph.size();i++){
        if(i==startNode){
            for(int j=0;j<adjacencyGraph[i].size();j++){
                int neighbour = adjacencyGraph[i][j];
                if (!visited[neighbour]) 
                    dfs(neighbour, adjacencyGraph, visited);
            }
        }
    }
}

bool isConnected(vector<vector<int> > adjacencyGraph, vector<bool> visited) {
    dfs(0,adjacencyGraph, visited); 
    bool flag = true;
    for (int i = 0; i < adjacencyGraph.size(); ++i) {
        if (!visited[i]) { 
            flag = false; 
            break; 
        }
    }
    return flag; 
}

int findMinimumSpanningTree(vector<Edge>graph, int vCount){
    sort(graph.begin(), graph.end(), sortDecreasing);
    int mstWeight = 0;
    vector<Edge> mst;
    vector<vector<int> > adjacencyGraph;
    for(int i=0; i<vCount; i++){		//Add placeholders for each vertex
        adjacencyGraph.push_back(vector<int>());
    }
    for(int k=0;k<graph.size();k++){
        Edge i = graph[k];
        adjacencyGraph[i.vertex1].push_back(i.vertex2);
        adjacencyGraph[i.vertex2].push_back(i.vertex1);
    }
    if(!isConnected(adjacencyGraph, vector<bool>(adjacencyGraph.size()))){
        return -1;
    }
    for(int k=0;k<graph.size();k++){
        Edge i = graph[k];
        for(int j=0;j<adjacencyGraph[i.vertex1].size();j++){
            if(adjacencyGraph[i.vertex1][j] == i.vertex2){
                adjacencyGraph[i.vertex1].erase(adjacencyGraph[i.vertex1].begin()+j);
            }
        }
        for(int j=0;j<adjacencyGraph[i.vertex2].size();j++){
            if(adjacencyGraph[i.vertex2][j] == i.vertex1){
                adjacencyGraph[i.vertex2].erase(adjacencyGraph[i.vertex2].begin()+j);
            }
        }
        if(!isConnected(adjacencyGraph, vector<bool>(adjacencyGraph.size()))){
            adjacencyGraph[i.vertex1].push_back(i.vertex2);
            adjacencyGraph[i.vertex2].push_back(i.vertex1);
            mst.push_back(i);
            mstWeight += i.weight;
        }
    }
    cout<<"-------- MST -------"<<endl;
    for(int i=0;i<mst.size();i++){
        cout<<mst[i].vertex1<<" "<<mst[i].vertex2<<" "<<mst[i].weight<<endl;
    }
    return mstWeight;
}

void testCode(){
    cout<<"Testcase: Minimum cost from algorithm is equal to actual result"<<endl;
    vector<Edge> graph;
    Edge e1(0,1,20);
    Edge e2(0,2,10);
    Edge e3(0,3,15);
    Edge e4(2,3,5);
    Edge e5(1,2,2);
    Edge e6(1,3,8);
    graph.push_back(e1);
    graph.push_back(e2);
    graph.push_back(e3);
    graph.push_back(e4);
    graph.push_back(e5);
    graph.push_back(e6);
    int minCost = 0;
    int actualMinCost = 17;
    minCost = findMinimumSpanningTree(graph, 4);
    if(minCost == actualMinCost){
        cout<<"Actual Minimum Cost "<<actualMinCost<<endl;
        cout<<"Minimum Cost from algorithm "<< minCost<<endl;
        cout<<"Test Success true";
    }
}

int main() {
    int t;
    cout<<"Enter 1 for running algorithm or Enter 2 for running test code"<<endl;
    cin>>t;
    if(t == 1){
        vector<Edge> graph;
        int minCost = 0;
        
        GenerateRandomGraph randomGraph;
        cout<<"The generated random graph :"<<endl;
        for(int i=0;i<randomGraph.graph.size();i++){
            cout<<randomGraph.graph[i].vertex1<<" "<<randomGraph.graph[i].vertex2<< " " << randomGraph.graph[i].weight<<endl;
        }
        
        struct timespec begin, end; 
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin);
        minCost = findMinimumSpanningTree(randomGraph.graph, randomGraph.vertices);
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
        long seconds = end.tv_sec - begin.tv_sec;
        long nanoseconds = end.tv_nsec - begin.tv_nsec;
        double elapsed = seconds + nanoseconds*1e-9;
        if(minCost == -1){
            cout<<"------ Disconnected graph. No MST found ---------"<<endl;
        }
        else {
            cout<< "Minimum cost of MST is "<<minCost<<endl;
        }
        cout<<endl<<"Time taken by algorithm"<<" "<<elapsed;
        return 0;
    }
    else {
        testCode();
    }
}
