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
map<int, list<int>> generateGraph(int v, int e){
    int i = 0, j = 0, count = 0;
    int edge[e][2];
    map<int, list<int>> g;
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
            g.insert(pair<int, list<int>>(i+1, sharedNodes));
        }
    }
    return g; 
}

// dfs function to find one cycle
bool dfs(int vertex, int parent, vector<bool> visited, vector<int> &temp, map<int,list<int>> graph) {
	visited[vertex-1] = true;
	temp.push_back(vertex);
	for ( list<int>::iterator it=graph[vertex].begin(); it != graph[vertex].end(); ++it ) {
        if(visited[*it-1] == false) {
			if(dfs(*it, node, visited,temp, graph) == true) {
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

int main() {
    int v = 2000; // number of nodes
	int e = 2100; // number of vertices
    vector<bool> visited(v,false);
    map<int, list<int>> graph = generateGraph(v,e);
    vector<int> temp;
    vector<int> vints;
    for(auto const& imap: graph){
        vints.push_back(imap.first);
    }
    struct timespec begin, end; 
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin); //start time
    bool isCyclePresent = dfs(vints[0],-1, visited, temp, grapha);
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
    
    cout<<endl<<"Time taken by algorithm"<<" "<<elapsed;
}
