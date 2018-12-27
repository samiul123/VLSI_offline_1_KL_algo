#include<iostream>
#include<bits/stdc++.h>
#include"Partition.cpp"
using namespace std;


int str_to_int(string s) {
	int u = 0;
	stringstream geek(s);
	geek >> u;
	return u;
}


void addEdge(vector<int> adj[], int u, int v) {
	adj[u].push_back(v);
	//adj[v].push_back(u);
}


pair<int, int> getNodesandpartition() {
	string line;
	int nodes = 0;
	ifstream inFile("input_KL.txt");
	getline(inFile, line);
	int partition = str_to_int(line);
	cout << partition << endl;
	while (getline(inFile, line)) {
		cout << line << endl;
		nodes++;
	}
	return make_pair(partition, nodes);
}



void printGraph(vector<int> adj[], int V){
	for (int v = 1; v <= V; v++){
		cout << "\n Adjacency list of vertex " << v << "\n head ";

		//cout << adj[v].size() << endl;
		for (auto x : adj[v])cout << "-> " << x;
		printf("\n");
	}
}

void print_vector(vector<int> &v) {
	for (auto x: v) {
		cout << x << " ";
	}
	cout << endl;
}

void print_map(map<pair<int, int>, int> myMap) {
	for (map<pair<int, int>, int >::const_iterator it = myMap.begin();
		it != myMap.end(); ++it){
		std::cout << it->first.first << " " << it->first.second << " " << it->second << "\n";
	}
}

void swap(vector<int> &partition1, vector<int> &partition2, int pos1, int pos2) {
	int temp = partition1[pos1];
	partition1[pos1] = partition2[pos2];
	partition2[pos2] = temp;
}

int container(int node, vector<int> &partition1, vector<int> &partition2) {
	if (find(partition1.begin(), partition1.end(), node) != partition1.end())return 1;
	else return 2;
}

pair<int, int> out_inEdge(int node, vector<int> adj[], vector<int> partition1, vector<int> partition2) {
	int numOutEdge = 0;
	int numInEdge = 0;
	int findNode = container(node, partition1, partition2);
	for (auto x: adj[node]) {
		int findX = container(x, partition1, partition2);
		if (findNode != findX) numOutEdge++;
		else numInEdge++;
	}
	//cout << "NODE " << node << " OUTEDGE: " << numOutEdge << " INEDGE: " << numInEdge << endl;
	return make_pair(numOutEdge, numInEdge);
}

void findDValue(map<int, int> &d, vector<int> adj[], vector<int> partition1, vector<int> partition2) {
	for (map<int, int>::iterator it = d.begin(); it != d.end(); it++) {
		int node = it->first;
		pair<int, int> outInEdge_node = out_inEdge(node, adj, partition1, partition2);
		d[node] = outInEdge_node.first - outInEdge_node.second;
		cout << "NODE " << node << " OUTEDGE: " << outInEdge_node.first << " INEDGE: " << outInEdge_node.second << " BENEFIT: " << d[node] << endl;
	}
}



void KL(map<pair<int, int>, int> &edgeSet, vector<int> adj[], map<int, int> &permanent_lock, map<int, int> &d, int partition, int nodes, int inodes) {
	int size1 = inodes - (inodes / partition), size2 = inodes / partition;
	vector<int> partition1, partition2;
	vector<int> lock(nodes, false);
	Partition p(nodes);
	p.partition(partition1, partition2, size1, size2, permanent_lock);
	findDValue(d, adj, partition1, partition2);

	//print_vector(partition1);
	//print_vector(partition2);

}

int main() {
	map<pair<int, int>, int> edgeSet;
	map<int, int> permanent_lock;
	map<int, int> d;
	vector<int> nodeList;
	pair<int, int> nodesPartition = getNodesandpartition();
	int partition = nodesPartition.first;
	int nodes = nodesPartition.second;
	int inodes = nodes;
	vector<int> adj[1000];
	//adj = new vector<int>[nodes];
	string line;
	ifstream inFile("input_KL.txt");
	getline(inFile, line);
	while (getline(inFile, line)) {
		//cout << line << endl;
		//nodes++;
		istringstream iss(line);
		vector<string> results((istream_iterator<string>(iss)), istream_iterator<string>());
		int u = str_to_int(results[0]);
		//cout << results.size() << endl;
		permanent_lock[u] = false;
		d[u] = 0;
		nodeList.push_back(u);
		for (int i = 2; i < results.size(); i++) {
			int v = str_to_int(results[i]);
			addEdge(adj, u, v);
			edgeSet[make_pair(u, v)] = 1;
			
			//cout << results[i] << " ";
		}
		//cout << endl;
	}
	printGraph(adj, nodes);
	print_map(edgeSet);
	//vector<int> permanent_lock(nodes, false);
	//vector<int> d(nodes, 0);
	/*if (nodes == partition) {
		cout << "Given grapgh is already divided into " << partition << " partitions" << endl;
	}
	else {
		while (partition != 1) {

		}
	}*/
	KL(edgeSet, adj, permanent_lock, d, partition, nodes, inodes);
	cin.get();
	return 0;
}