/******************************************************************************

                            Author: Sankalp Pandey
                            UFID: 92878142
                            Course: Analysis of Algorithms
                            Instructor: Alin Dobra

*******************************************************************************/

#include <bits/stdc++.h>
#include <time.h>
using namespace std;

// graph generator
map<int, list<int> > generateGraph(int v, int e){
    int i = 0, j = 0, count = 0;
    int edge[e][2];
    map<int, list<int> > g;
    srand(time(NULL));
    while(i<e){
        edge[i][0] = rand()%(v) + 1;
	    edge[i][1] = rand()%(v) + 1;
	    while(edge[i][0]==edge[i][1]) {
			edge[i][0] = rand()%(v) + 1;
			edge[i][1] = rand()%(v) + 1;
		}
		i++;
    }
    for (i = 0; i < v; i++) {
		count = 0;
		list<int> sharedNodes;
			
        for (j = 0; j < e; j++) {
			if (edge[j][0] == i + 1) {
				sharedNodes.push_back(edge[j][1]);
				count++;
			}

            else if (edge[j][1] == i + 1) {
                sharedNodes.push_back(edge[j][0]);
                count++;
            }

            else if (j == e - 1 && count == 0) {
                sharedNodes.push_back(-1);
            }
        }
        if(find(sharedNodes.begin(),sharedNodes.end(), -1) == sharedNodes.end()){
            g.insert(pair<int, list<int> >(i+1, sharedNodes));
        }
    }
    return g; 
}

// dfs function to find one cycle
bool dfs(int vertex, int parent, vector<bool> visited, vector<int> &temp, map<int,list<int> > graph) {
	visited[vertex-1] = true;
	temp.push_back(vertex);
	for ( list<int>::iterator it=graph[vertex].begin(); it != graph[vertex].end(); ++it ) {
        if(visited[*it-1] == false) {
			if(dfs(*it, vertex, visited,temp, graph) == true) {
			    return true;
			}
		}
		else if(parent != *it) {
			temp.push_back(*it);
			return true;
		}
    }
	temp.pop_back();
	return false;
}

inline const char * const BoolToString(bool b)
{
  return b ? "true" : "false";
}

void testCode() {
    cout<<"Testcase 1: Cycle exists"<<endl;
    int v = 5;
    map<int, list<int> > graph;
    list<int>first;
    first.push_back(4);
    first.push_back(5);
    graph.insert(pair<int, list<int> >(1,first));
    list<int>second;
    second.push_back(3);
    graph.insert(pair<int, list<int> >(2,second));
    list<int>third;
    third.push_back(2);
    third.push_back(5);
    graph.insert(pair<int, list<int> >(3,third));
    list<int>fourth;
    fourth.push_back(1);
    fourth.push_back(5);
    graph.insert(pair<int, list<int> >(4,fourth));
    list<int>fifth;
    fifth.push_back(3);
    fifth.push_back(1);
    fifth.push_back(4);
    graph.insert(pair<int, list<int> >(5,fifth));

    vector<bool> visited(v,false);
    vector<int> temp;
    vector<int> vints;
    map<int, list<int> >::iterator it = graph.begin();
    while(it!=graph.end()){
        vints.push_back(it->first);
        it++;
    }
    bool isCyclePresent = dfs(vints[0],-1, visited, temp, graph);
    bool test = false;
    std::vector<int> actualResult;
    actualResult.push_back(1);
    actualResult.push_back(4);
    actualResult.push_back(5);
    actualResult.push_back(1);
    if(isCyclePresent && temp.size() == actualResult.size() && equal(temp.begin(), temp.end(), actualResult.begin())){
        test = true;
        int j=0;
        cout<<"Actual result ";
        while(j<actualResult.size()){
            cout<<actualResult[j]<<" ";
            j++;
        }
        cout<<endl;
        j=0;
        cout<<"Result from algorithm ";
        while(j<temp.size()){
            cout<<temp[j]<<" ";
            j++;
        }
        cout<<endl<<"Test Success"<<" "<<BoolToString(test)<<endl;
    }
    cout<<endl;
    cout<<"Testcase 2: No cycle"<<endl;
    int v2 = 3;
    map<int, list<int> > graph2;
    list<int>first1;
    first1.push_back(2);
    graph2.insert(pair<int, list<int> >(1,first1));
    list<int>second1;
    second1.push_back(3);
    second1.push_back(1);
    graph2.insert(pair<int, list<int> >(2,second1));
    list<int>third1;
    third1.push_back(2);
    graph2.insert(pair<int, list<int> >(3,third1));
    vector<bool> visited1(v2,false);
    vector<int> temp1;
    vector<int> vints1;
    map<int, list<int> >::iterator it1 = graph2.begin();
    while(it1!=graph2.end()){
        vints1.push_back(it1->first);
        it1++;
    }
    bool isCyclePresent1 = dfs(vints1[0],-1, visited1, temp1, graph2);
    bool test1 = false;
    if(!isCyclePresent1 || temp1.size() == 0){
        if(temp1.size() == 0){
            cout<<"Stack returned from algorithm is empty"<<endl;
            cout<<"Test Success true"<<endl;
        }
    }
}

int main() {
    int v,e;
    int t;
    cout<<"Enter 1 for running algorithm or Enter 2 for running test code"<<endl;
    cin>>t;
    if(t == 1){
        cout<<"Enter number of vertices:"<<endl;
        cin>>v;
        cout<<"Enter number of edges:"<<endl;
        cin>>e;
        // int v = 20000; // number of nodes
        // int e = 40000; // number of vertices
    
        vector<bool> visited(v,false);
        map<int, list<int> > graph = generateGraph(v,e);
        vector<int> temp;
        vector<int> vints;
        map<int, list<int> >::iterator it = graph.begin();
        while(it!=graph.end()){
            vints.push_back(it->first);
            it++;
        }
        
        struct timespec begin, end; 
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin); //start time
        bool isCyclePresent = dfs(vints[0],-1, visited, temp, graph);
        if(!isCyclePresent || temp.size()==0) {
            cout<<endl<< "Cycle not present";
        }
        else 
        {
            int end = temp.back();
            int start = 0;
            for(int k =temp.size()-2; k>=0; k--) {
                if(temp.at(k)==end) {
                    start = k;
                    break;
                }
            }
            if(start==0 && temp.at(start)!=end) {
                cout<<endl<<"Cycle not present";
            }
            else {
                cout<<endl<<"One cycle -> ";
                for(int p = start; p<temp.size(); p++ ) {
                    cout<<" "<<temp.at(p);
                }
            }
        }
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end); //end time
        long seconds = end.tv_sec - begin.tv_sec;
        long nanoseconds = end.tv_nsec - begin.tv_nsec;
        double elapsed = seconds + nanoseconds*1e-9;
        
        cout<<endl<<"Time taken by algorithm"<<" "<<elapsed<<"sec";
    }
    else{
        testCode();
    }
}
