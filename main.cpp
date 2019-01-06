#include<iostream>
#include<bits/stdc++.h>
#include"Partition.cpp"
using namespace std;

ofstream outfile("output_KL.txt");
int improved = 0;
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

void print_vector(vector<int> &v, int i) {
	//if (i == 1)cout << "P" << i << " = {" << endl;
	cout << "P" << i << " = {";
	outfile << "P" << i << " = {";
	for (auto x: v) {
		cout << x << " ";
		outfile << x << " ";
	}
	cout << "}" << endl;
	outfile << "}" << endl;
}

void print_partitions(vector<vector<int>> &partitions) {
	for (int j = 0; j < partitions.size(); j++) {
		vector<int> p = partitions[j];
		print_vector(p, j + 1);
	}
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
		//cout << "NODE " << node << " OUTEDGE: " << outInEdge_node.first << " INEDGE: " << outInEdge_node.second << " BENEFIT: " << d[node] << endl;
	}
}

void updateDValue(map<int, int> &d, map<pair<int, int>, int> &map_edges_set, int node_a, int node_b, vector<int> partition1, vector<int> partition2) {
	int common_edge_xa, common_edge_xb;
	for (auto x: partition1) {
		if (x != node_a && x != node_b) {
			if (map_edges_set.find(make_pair(x, node_a)) != map_edges_set.end()) {
				common_edge_xa = map_edges_set[make_pair(x, node_a)];
			}
			else if (map_edges_set.find(make_pair(node_a, x)) != map_edges_set.end()) {
				common_edge_xa = map_edges_set[make_pair(node_a, x)];
			}
			else common_edge_xa = 0;

			if (map_edges_set.find(make_pair(x, node_b)) != map_edges_set.end()) {
				common_edge_xb = map_edges_set[make_pair(x, node_b)];
			}
			else if (map_edges_set.find(make_pair(node_b, x)) != map_edges_set.end()) {
				common_edge_xb = map_edges_set[make_pair(node_b, x)];
			}
			else common_edge_xb = 0;

			d[x] = d[x] + 2 * common_edge_xa - 2 * common_edge_xb;
			//cout << "NODE " << x << " BENEFIT: " << d[x] << endl;
		}

	}

	for (auto y: partition2) {
		if (y != node_a && y != node_b) {
			if (map_edges_set.find(make_pair(y, node_a)) != map_edges_set.end()) {
				common_edge_xa = map_edges_set[make_pair(y, node_a)];
			}
			else if (map_edges_set.find(make_pair(node_a, y)) != map_edges_set.end()) {
				common_edge_xa = map_edges_set[make_pair(node_a, y)];
			}
			else common_edge_xa = 0;

			if (map_edges_set.find(make_pair(y, node_b)) != map_edges_set.end()) {
				common_edge_xb = map_edges_set[make_pair(y, node_b)];
			}
			else if (map_edges_set.find(make_pair(node_b, y)) != map_edges_set.end()) {
				common_edge_xb = map_edges_set[make_pair(node_b, y)];
			}
			else common_edge_xb = 0;

			d[y] = d[y] + 2 * common_edge_xb - 2 * common_edge_xa;
			//cout << "NODE " << y << " BENEFIT: " << d[y] << endl;
		}
	}
}

int computeCutSize(vector<int> adj[], vector<int> partition1, vector<int> partition2) {
	int cutSize = 0;
	for (auto x: partition1) {
		for (auto y: adj[x]) {
			if (find(partition2.begin(), partition2.end(), y) != partition2.end()) {
				cutSize++;
			}
		}
	}
	/*for (auto x: partitions) {
		for (auto y:x) {
			for (auto z: adj[y]) {
				if(find(x.begin(), x.end(), z) == x.end())cutSize++;
			}
		}
	}*/
	return cutSize;
}

int sum_g(vector<int> g_values) {
	int sum = 0;
	if (!g_values.empty()) {
		for (auto x : g_values) {
			sum += x;
		}
	}
	else sum = 1;
	return sum;
}

int check_exist(vector<vector<int>> p, vector<int> p1, vector<int> p2) {
	auto it1 = find(p.begin(), p.end(), p1);
	auto it2 = find(p.begin(), p.end(), p2);
	if (it1 == p.end() && it2 == p.end()) return 0;
	return 1;
}

pair<vector<int>, vector<int>> partition_func(vector<int> nodeList, map<int, int> &p_lock, int partition) {
	vector<int> partition1, partition2;
	int size1 = nodeList.size() - (nodeList.size() / partition);
	int size2 = nodeList.size() / partition;
	for (auto x: nodeList) {
		//f (!p_lock[x]) {
		if ((rand() * x) % 2 == 1) {
			if ((int)partition1.size() == size1)partition2.push_back(x);
			else if ((int)partition2.size() == size2)partition1.push_back(x);
			else partition1.push_back(x);
		}
		else {
			if ((int)partition1.size() == size1)partition2.push_back(x);
			else if ((int)partition2.size() == size2)partition1.push_back(x);
			else partition2.push_back(x);
		}
		//}
	}
	//print_vector(partition1, 1);
	//print_vector(partition2, 2);
	/*for (auto x: partition1) ans.push_back(x);
	ans.push_back(-1);

	for (auto x:partition2)ans.push_back(x);
	ans.push_back(-1);*/
	return make_pair(partition1, partition2);
}

int value(vector<int> p, int pos, map<int, int> &p_lock) {
	for (int i = 0; i < p_lock.size(); i++) {
		if (p[pos] == i) {
			return i;
		}
	}
}

int partition_check(vector<vector<int>> p, int nodes, int partition) {
	cout << nodes / partition << endl;
	for (auto x:p) {
		if (x.size() < (nodes / partition)) {
			cout << "p_check " << 0 << endl;
			return 0; 
		}
	}
	cout << "p_check " << 1 << endl;
	return 1;
}

pair<vector<int>, vector<int>> KL(map<pair<int, int>, int> &map_edges_set, vector<int> adj[],
	map<int, int> &p_lock, map<int, int> &d, int partition, int nodes,
	vector<int> partition1, vector<int> partition2, int original_cut) {
	//int size1 = inodes - (inodes / partition), size2 = inodes / partition;
	//vector<vector<int>> partitions;
	vector<int> p1 = partition1;
	vector<int> p2 = partition2;
	//vector<int> partition1, partition2;
	vector<int> lock(nodes + 1, false);
	//partition1 = { 1, 2, 3, 4 };
	//partition2 = { 5, 6, 7, 8 };
	
	/*partition_func(nodeList, p_lock, ans, partition);
	int flag = 0;
	for (auto x : ans) {
		if (x == -1)flag = 1;
		else if (flag) partition2.push_back(x);
		else partition1.push_back(x);
	}*/

	findDValue(d, adj, partition1, partition2);
	int common_edges = 0;
	//int gain = 0;
	pair<int, int> edge;
	map<pair<int, int>, int> pair_gain;
	vector<int> g_values;
	vector<int> pos1_value, pos2_value;
	vector<pair<int, int>> exchange_pair;
	int gain, temp_gain;
	int partition_node_1, partition_node_2;
	int cut = computeCutSize(adj, partition1, partition2);
	int prev_cut = 0;
	//int prev_best_cut = cut;
	int initial_cut = computeCutSize(adj, partition1, partition2);
	int present_cut = initial_cut;
	cout << "Inner iteration:" << endl;
	outfile << "	Inner iteration:" << endl;
	cout << "Step	Pair	G	Sum_G	CutSize" << endl;
	outfile << "	Step	Pair	G	Sum_G	CutSize" << endl;
	int inner_step = 0;
	cout << inner_step << "	-	-	-	" << initial_cut << endl;
	outfile << "	" << inner_step << "	-	-	-	" << initial_cut << endl;
	vector<int> cuts;
	cuts.push_back(original_cut);
	while(prev_cut == 0 || present_cut != cut) {
		
		//findDValue(d, adj, partition1, partition2);
		inner_step++;
		bool found = false;
		for (int i = 0; i < partition1.size(); i++) {
			//cout << "in for 1" << endl;
			for (int j = 0; j < partition2.size(); j++) {
				//cout << "in for 2" << endl;
				if (!lock[partition1[i]] && !lock[partition2[j]]) {
					//cout << "if 1" << endl;
					//cout << partition1[i] << " " << partition2[j] << endl;
					if (map_edges_set.find(make_pair(partition1[i], partition2[j])) != map_edges_set.end()) {
						//cout << partition1[i] << " " << partition2[j] << "found" << endl;
						edge = make_pair(partition1[i], partition2[j]);
						common_edges = map_edges_set[make_pair(partition1[i], partition2[j])];
					}
					else if (map_edges_set.find(make_pair(partition2[j], partition1[i])) != map_edges_set.end()) {
						//cout << partition2[j] << " " << partition1[i] << "found" << endl;
						edge = make_pair(partition1[i], partition2[j]);
						common_edges = map_edges_set[make_pair(partition2[j], partition1[i])];
					}
					else {
						common_edges = 0;
					}
					//pair_gain[edge] = d[partition1[i]] + d[partition2[j]] - 2 * common_edges;
					if (!found) {
						gain = d[partition1[i]] + d[partition2[j]] - 2 * common_edges;
						//cout << "if" << endl;
						partition_node_1 = i;
						partition_node_2 = j;
						found = true;
					}
					else {
						temp_gain = d[partition1[i]] + d[partition2[j]] - 2 * common_edges;
						//cout << "else" << endl;
						if (temp_gain > gain) {
							gain = temp_gain;
							partition_node_1 = i;
							partition_node_2 = j;
						}
					}
					pair_gain[edge] = gain;
				}
			}
			
		}

		

		lock[partition1[partition_node_1]] = true;
		pos1_value.push_back(partition_node_1);

		lock[partition2[partition_node_2]] = true;
		pos2_value.push_back(partition_node_2);

		g_values.push_back(gain);
		exchange_pair.push_back(make_pair(partition1[partition_node_1], partition2[partition_node_2]));
		
		/*pair<pair<int, int>, int> highest = *pair_gain.begin();
		map<pair<int, int>, int>::iterator it = pair_gain.begin();
		cout << "pair gains" << endl;
		for (map<pair<int, int>, int>::iterator it = pair_gain.begin(); it != pair_gain.end(); it++) {
			cout << it->first.first << " " << it->first.second << " " << it->second << endl;

		}*/
		/*while (pair_gain.value_comp()(*it++, highest)) {
			highest = *it;
		}
		int pos1, pos2;
		vector<int>::iterator val1 = find(partition1.begin(), partition1.end(), highest.first.first);
		vector<int>::iterator val2 = find(partition2.begin(), partition2.end(), highest.first.second);
		if (val1 != partition1.end()) {
			pos1 = distance(partition1.begin(), val1);
			pos2 = distance(partition2.begin(), val2);
			lock[partition1[pos1]] = true;
			lock[partition2[pos2]] = true;
		}
		else {
			pos2 = distance(partition2.begin(), val1);
			pos1 = distance(partition1.begin(), val2);
			lock[partition1[pos1]] = true;
			lock[partition2[pos2]] = true;
		}
		pos1_value.push_back(pos1);
		pos2_value.push_back(pos2);
		g_values.push_back(highest.second);*/
		updateDValue(d, map_edges_set, partition1[partition_node_1], partition2[partition_node_2], partition1, partition2);
		cout << inner_step << "	(" << partition1[partition_node_1] << ", " << partition2[partition_node_2] << ")	" 
			<< gain << "	" << sum_g(g_values) << "	";
		outfile << "	" << inner_step << "	(" << partition1[partition_node_1] << ", " << partition2[partition_node_2] << ")	"
			<< gain << "	" << sum_g(g_values) << "	";
		swap(partition1, partition2, partition_node_1, partition_node_2);
		//cout << "after swapping: " << endl;
		//print_vector(partition1, 1);
		//print_vector(partition2, 2);
		prev_cut = present_cut;
		present_cut = computeCutSize(adj, partition1, partition2);
		//swap(partition1, partition2, partition_node_1, partition_node_2);
		//cout << "present cut: " << present_cut << endl;
		
		cout << present_cut << endl;
		outfile << present_cut << endl;
		cuts.push_back(present_cut);
	}
		
	/*int max_g = *max_element(g_values.begin(), g_values.end());
	vector<int>::iterator max_it = find(g_values.begin(), g_values.end(), max_g);
	int max_g_index = distance(g_values.begin(), max_it);
	if (max_g < 0 && max_g_index == 1) max_g_index = -1;
	for (int i = 0; i < max_g_index; i++) {
		swap(partition1, partition2, pos1_value[i], pos2_value[i]);
	}*/
	//print_vector(g_values, 0);
	int max_g = g_values[0], cum_maxg = g_values[0], index_upto_max_cum_g = 1;
	for (int i = 1; i < g_values.size(); ++i){
		cum_maxg = cum_maxg + g_values[i];
		if (cum_maxg > max_g){
			max_g = cum_maxg;
			index_upto_max_cum_g = i;
		}
	}
	/*cout << "max_g: " << max_g << endl;
	cout << "max_index: " << index_upto_max_cum_g << endl;*/
	partition1 = p1;
	partition2 = p2;
	//print_vector(pos1_value, 00);
	//print_vector(pos2_value, 01);
	vector<int>::iterator minIt = min_element(cuts.begin(), cuts.end());
	
	if (max_g >= 0 && *minIt < cuts[0]) {
		
		cout << "Parmanent Exchange: ";
		outfile << "	Parmanent Exchange: ";
		/*for (auto x: exchange_pair) {
			if(x == exchange_pair.back()) cout << "(" << x.first << ", " << x.second << ")" << endl;
			else cout << "(" << x.first << ", " << x.second << "), ";
		}*/
		for (int i = 0; i <= index_upto_max_cum_g; i++) {
			if (i == index_upto_max_cum_g) {
				cout << "(" << exchange_pair[i].first << ", " << exchange_pair[i].second << ")" << endl;
				outfile << "(" << exchange_pair[i].first << ", " << exchange_pair[i].second << ")" << endl;
			}
			else {
				cout << "(" << exchange_pair[i].first << ", " << exchange_pair[i].second << "), ";
				outfile << "(" << exchange_pair[i].first << ", " << exchange_pair[i].second << "), ";
			}
			swap(partition1, partition2, pos1_value[i], pos2_value[i]);
			int pos_in_lock_1 = value(partition1, pos1_value[i], p_lock);
			p_lock[pos_in_lock_1] = true;
			p_lock[value(partition2, pos2_value[i], p_lock)];

		}
		outfile << "	";
		print_vector(partition1, 1);
		outfile << "	";
		print_vector(partition2, 2);
		
		cout << "Cutsize: " << computeCutSize(adj, partition1, partition2) << endl;
		outfile << "	Cutsize: " << computeCutSize(adj, partition1, partition2) << endl;
		//improved = 1;
		cuts = {};

		
	}
	else {
		cout << "No improvement." << endl;
		outfile << endl << endl << "	No improvement." << endl;
		//improved = 0;
	}
	outfile << "--------------------------------------------------" << endl << endl;
	//if ((partition - 1) == 1) {
	//	for (int i = 0; i < partition1.size(); ++i) {
	//		//ans.push_back(partition1[i]);
	//		p_lock[partition1[i]] = 1;
	//	}
	//	//ans.push_back(-1);
	//}

	//for (int i = 0; i < partition2.size(); ++i) {
	//	//ans.push_back(partition2[i]);
	//	p_lock[partition2[i]] = 1;
	//}
	return make_pair(partition1, partition2);
	//ans.push_back(-1);

	
	//print_vector(partition1, 1);
	//print_vector(partition2, 2);
	
	/*map<int, int>::iterator lock_it = p_lock.find(highest.first.first);
	if (lock_it != p_lock.end())p_lock[lock_it->first] = true;
	lock_it = p_lock.find(highest.first.second);
	if (lock_it != p_lock.end())p_lock[lock_it->first] = true;*/
	
	//cout << "highest gain: " << highest.second << endl;
	//print_vector(partition1);
	//print_vector(partition2);

}

int main() {
	map<pair<int, int>, int> map_edges_set;
	map<int, int> p_lock;
	map<int, int> d;
	vector<int> nodeList;
	
	vector<vector<int>> partitions = {};
	vector<int> partition1, partition2;
	//vector<int> partition1, partition2;
	pair<int, int> nodesPartition = getNodesandpartition();
	int partition = nodesPartition.first;
	int const_part = partition;
	int nodes = nodesPartition.second;
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
		p_lock[u] = false;
		d[u] = 0;
		nodeList.push_back(u);
		for (int i = 2; i < results.size(); i++) {
			int v = str_to_int(results[i]);
			addEdge(adj, u, v);
			map_edges_set[make_pair(u, v)] = 1;

			//cout << results[i] << " ";
		}
		//cout << endl;
	}
	/*printGraph(adj, nodes);
	print_map(map_edges_set);*/
	//partitions.push_back(nodeList);
	pair<vector<int>, vector<int>> pair_part = partition_func(nodeList, p_lock, 2);
	/*int flag = 0;
	for (auto x: ans) {
		if (x == -1)flag = 1;
		else if (flag) partition2.push_back(x);
		else partition1.push_back(x);
	}*/
	//partitions.push_back(partition1);
	//partitions.push_back(partition2);
	//partition1 = { 1, 2, 3, 4 };
	//partition2 = { 5, 6, 7, 8 };
	partition1 = pair_part.first;
	partition2 = pair_part.second;
	outfile << "**************************************************" << endl << endl;
	cout << "Initial partitions:" << endl;
	outfile << "Initial partitions:" << endl;
	print_vector(partition1, 1);
	print_vector(partition2, 2);
	int initial_cut = computeCutSize(adj, partition1, partition2);
	cout << "Initial cutsize: " << initial_cut << endl;
	outfile << "Initial cutsize: " << initial_cut << endl << endl;
	outfile << "**************************************************" << endl << endl;
	int out_it = 1;
	int prev_best_cut = 0;
	int present_best_cut = computeCutSize(adj, partition1, partition2);
	//vector<int> p_lock(nodes, false);
	//vector<int> d(nodes, 0);
	if (nodes == partition) {
		cout << "Given grapgh is already divided into " << partition << " partitions" << endl;
	}
	else {
		cout << partitions.size() << endl;
		while (partition != 0 && partition_check(partitions, nodesPartition.second, nodesPartition.first)) {
			cout << "Outer iteration " << out_it << ":" << endl;
			outfile << "Outer iteration " << out_it << ":" << endl;
			outfile << "--------------------------------------------------" << endl << endl;
			//print_vector(partition1, 1);
			//print_vector(partition2, 2);
			//initial_cut = computeCutSize(adj, partition1, partition2);
			
			//if (!partition_check(partitions, nodesPartition.second, nodesPartition.first)) {
				pair<vector<int>, vector<int>> new_part = KL(map_edges_set, adj, p_lock, d, partition, nodes, partition1, partition2, initial_cut);
				partition1 = new_part.first;
				partition2 = new_part.second;
				initial_cut = computeCutSize(adj, partition1, partition2);
				if (!check_exist(partitions, partition1, partition2)) {
					partitions.push_back(partition1);
					partitions.push_back(partition2);
					/*cout << "after push" << endl;
					print_partitions(partitions);*/
					//ans = {};
					//ans.clear();
					//cout << "front" << endl;
					//print_vector(partitions.front(), 1);
					cout << "partion size: " << partitions.size() << endl;
					if (partitions.size() < nodesPartition.first) {
						pair_part = partition_func(partitions.front(), p_lock, 2);
						partitions.erase(partitions.begin());

						/*cout << "after erase" << endl;
						print_partitions(partitions);
						cout << "clear part" << endl;*/
						partition1 = pair_part.first;
						partition2 = pair_part.second;
						//print_vector(partition1, 1);
						//partition2.clear();
						//print_vector(partition2, 2);
					}
					
					//partition1.clear();

					
					/*flag = 0;
					for (auto x : ans) {
						if (x == -1)flag = 1;
						else if (flag) partition2.push_back(x);
						else partition1.push_back(x);
					}*/
					//print_vector(partition1, 1);
					//print_vector(partition2, 2);
					//break;
					improved = 0;
					//break;
				}
				//else {
				//	partitions.push_back(partition1);
				//	partitions.push_back(partition2);
				//	if (partitions.size() < partition) {
				//		pair_part = partition_func(partitions.front(), p_lock, ans, 2);
				//		partitions.erase(partitions.begin());

				//		cout << "after erase" << endl;
				//		print_partitions(partitions);
				//		cout << "clear part" << endl;
				//		partition1 = pair_part.first;
				//		partition2 = pair_part.second;
				//		print_vector(partition1, 1);
				//		//partition2.clear();
				//		print_vector(partition2, 2);
				//	}
				//}
				
			//}
			--partition;
			out_it++;
			//print_vector(partition1, 1);
			//print_vector(partition2, 2);
			/*prev_best_cut = present_best_cut;
			present_best_cut = computeCutSize(adj, partition1, partition2);
			//cout << "present cut: " << present_best_cut << endl;
			if (present_best_cut == prev_best_cut) {
				cout << "No improvement." << endl;
				outfile << "No improvement." << endl;
				break;
			}*/
			
			//inodes = inodes - (inodes / partition);
			//if (improved) {
			//	partitions.push_back(partition1);
			//	partitions.push_back(partition2);
			//	cout << "after push" << endl;
			//	print_partitions(partitions);
			//	//ans = {};
			//	//ans.clear();
			//	cout << "front" << endl;
			//	//print_vector(partitions.front(), 1);
			//	pair_part = partition_func(partitions.front(), p_lock, ans, 2);
			//	partitions.erase(partitions.begin());
			//	
			//	cout << "after erase" << endl;
			//	print_partitions(partitions);
			//	cout << "clear part" << endl;
			//	partition1 = pair_part.first;
			//	partition2 = pair_part.second;
			//	
			//	//partition1.clear();
			//	
			//	print_vector(partition1, 1);
			//	//partition2.clear();
			//	print_vector(partition2, 2);
			//	/*flag = 0;
			//	for (auto x : ans) {
			//		if (x == -1)flag = 1;
			//		else if (flag) partition2.push_back(x);
			//		else partition1.push_back(x);
			//	}*/
			//	//print_vector(partition1, 1);
			//	//print_vector(partition2, 2);
			//	//break;
			//	improved = 0;
			//	//break;
			//}
			//partitions.erase(partitions.begin());
						/*ans = {};
			partition_func(partitions.front(), p_lock, ans, 2);
			partition1 = {};
			partition2 = {};
*/
			//if (partitions.size() < const_part) {
			//	vector<int> p = partitions.front();
			//	//print_vector(p, 1);
			//	partitions.erase(partitions.begin());
			//	ans = {};
			//	partition_func(p, p_lock, ans, 2);
			//	partition1 = {};
			//	partition2 = {};
			/*flag = 0;
			for (auto x : ans) {
				if (x == -1)flag = 1;
				else if (flag) partition2.push_back(x);
				else partition1.push_back(x);
			}*/
			//	partitions.push_back(partition1);
			//	partitions.push_back(partition2);
			//}
			
			
		}
	}

	cout << "Final Partitions:" << endl;
	outfile << "**************************************************" << endl << endl;
	outfile << "Final Partitions:" << endl;
	for (int j = 0; j < partitions.size(); j++) {
		vector<int> p = partitions[j];
		print_vector(p, j + 1);
	}
	outfile << endl << "**************************************************" << endl << endl;
	//vector<int> p1 = { 4, 3,7 ,8 }, p2 = { 1, 2, 5 , 6 };

	/*KL(map_edges_set, ans, adj, p_lock, d, partition, nodes, inodes, p1, p2);
	for (int i = 0; i < ans.size(); i++)
	{
		if (ans[i] != -1)
			cout << ans[i] << " ";
		else
			cout << endl;
	}*/
	
	cin.get();
	return 0;
}