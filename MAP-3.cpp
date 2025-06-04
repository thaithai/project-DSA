#include <iostream>
#include <math.h>
#include <bits/stdc++.h>
#include <cstring>
#include <windows.h>

using namespace std;

#define INF  1e9
const double R = 6.371; //bán kính trái đất
const int number_node = 30; //số lượng node


struct Node {
    int id;  
    string name;  // tên node
    double longitude; // kinh độ
    double latitude;  // vĩ độ
    double weight;   // trọng số node
    int state;  // trạng thái node
};

struct Graph{
    Node node[number_node];  //mảng lưu các node
};

typedef struct Node* DNode;
typedef struct Graph* DGraph;

vector<DNode> Q[number_node];

//tạo node
DNode makenode(int id, string name, double longitude, double latitude){
    DNode tmp = new Node;
    tmp->id = id;
    tmp->longitude = longitude;
    tmp->latitude = latitude;
	tmp->name = name;
    return tmp;
}

//đổi từ radian sang độ
double toRadian(double degree) {
    return degree * M_PI / 180.0;
}

//tính khoảng cách
double distance(DNode node1, DNode node2){
    double delta_longitude = node2->longitude - node1->longitude;
    double delta_latitude = node2->latitude - node1->latitude;
    double d,x;
    x = sin(delta_latitude/2)*sin(delta_latitude/2) + cos(node1->latitude)*cos(node2->latitude)*sin(delta_longitude/2)*sin(delta_longitude/2);
    d = 2*R*asin(sqrt(x)); // công thức haversine
    return d;
}

//tạo cạnh
void edge(DNode node1, DNode node2){
	Q[node1->id].push_back(node2);
	Q[node2->id].push_back(node1);
}

//tìm node lân cận chưa được duyệt
DNode find(DGraph &graph){
    double min = INF;
    DNode tmp = NULL;
    for(int i=0;i<number_node;i++){
        if(graph->node[i].state == 0 && graph->node[i].weight < min){
            min = graph->node[i].weight;
            tmp = &graph->node[i];
        }
    }
    return tmp;
}

//tìm đường đi ngắn nhất
void dijsktra(DGraph graph, DNode node){
	DNode node1 = node;
	node1->weight = 0;
	while(node1 != NULL){
		node1->state = 1; //đánh dấu node đã được duyệt
		for(auto x:Q[node1->id]){
			if(x->state == 0){
				double dist = distance(node1, x) + node1->weight;
				if(x->weight > dist){
					x->weight = dist;
				}
			}
		}
		node1 = find(graph);
	}
}

//in đường đi
vector<int> map1;
void print(DGraph graph, DNode start, DNode end){
	DNode tmp = end;
	map1.push_back(tmp->id);
    while(tmp->id != start->id){
    	for(auto x:Q[tmp->id]){
    		if(abs(tmp->weight - (x->weight + distance(x, tmp))) < 1e-6){
    			tmp = x;
    			map1.push_back(tmp->id);
    			break;
			}
		}
	}
	for(int i=map1.size()-1; i>=0;i--){
		cout<< graph->node[map1[i]].name;
		if(i > 0){
			cout<<"->";
		}
	}
	cout<<endl;
}

//tìm nhà để xe gần nhất
void reset_graph(DGraph graph) {
    for(int i = 0; i < number_node; i++) {
        graph->node[i].weight = INF;
        graph->node[i].state = 0;
    }
}

DNode find_gara(DGraph graph, DNode node) {
    DNode tmp = &graph->node[26];
    double min = distance(node, tmp);
    for (int i = 27; i < 30; i++) {
        double dist = distance(node, &graph->node[i]);
        if (min >= dist) {
            tmp = &graph->node[i];
        }
    }
    return tmp;
}

int main(){
	SetConsoleOutputCP(65001);
    Graph g;
    
    // Tạo các node với tên và tọa độ (latitude, longitude)
   	g.node[0] = {0, "C1", toRadian(105.8431282973016), toRadian(21.00704213080386), INF, 0};
	g.node[1] = {1, "C2", toRadian(105.8424014156262), toRadian(21.00639007963458), INF, 0};
	g.node[2] = {2, "C9", toRadian(105.84228299935458), toRadian(21.005821342202463), INF, 0};
	g.node[3] = {3, "A", toRadian(105.84342158784236), toRadian(21.00619449536794), INF, 0};
	g.node[4] = {4, "B", toRadian(105.84311574359431), toRadian(21.005713919148494), INF, 0};
	g.node[5] = {5, "C", toRadian(105.84231540952679), toRadian(21.00502724684272), INF, 0};
	g.node[6] = {6, "D4", toRadian(105.84209935793606), toRadian(21.004173316008735), INF, 0};
	g.node[7] = {7, "D", toRadian(105.84234066231011), toRadian(21.004178554863106), INF, 0};
	g.node[8] = {8, "D8", toRadian(105.84266894849344), toRadian(21.003992575420355), INF, 0};
	g.node[9] = {9, "D6", toRadian(105.84256309757227), toRadian(21.004351436954444), INF, 0};
	g.node[10] = {10, "E", toRadian(105.84338124063451), toRadian(21.00368615667903), INF, 0};
	g.node[11] = {11, "D9", toRadian(105.84416350525709), toRadian(21.003821401579213), INF, 0};
	g.node[12] = {12, "D7", toRadian(105.84497870822503), toRadian(21.004137051073617), INF, 0};
	g.node[13] = {13, "D3-5", toRadian(105.845270857709), toRadian(21.00461577617853), INF, 0};
	g.node[14] = {14, "D5", toRadian(105.84493664620237), toRadian(21.004358647302606), INF, 0};
	g.node[15] = {15, "D3", toRadian(105.84498130022953), toRadian(21.004789869957694), INF, 0};
    g.node[16] = {16, "C8", toRadian(105.84507628590657), toRadian(21.005382034012978), INF, 0 };
    g.node[17] = {17, "C7", toRadian(105.84500760731859), toRadian(21.005792564795897), INF, 0 };
    g.node[18] = {18, "C6", toRadian(105.84502801753538), toRadian(21.006222689457477), INF, 0 };
    g.node[19] = {19, "C3", toRadian(105.84399237951273), toRadian(21.006643640715133), INF, 0 };
    g.node[20] = {20, "C4", toRadian(105.84408154809348), toRadian(21.00620539364889), INF, 0 };
    g.node[21] = {21, "C5", toRadian(105.84415656099513), toRadian(21.00582525412773), INF, 0 };
    g.node[22] = {22, "C10", toRadian(105.84409640103762), toRadian(21.005468493046543), INF, 0 };
    g.node[23] = {23, "TV", toRadian(105.844149157304), toRadian(21.004698697745933), INF, 0 };
    g.node[24] = {24, "Alumi", toRadian(105.84351266005486), toRadian(21.004689845073486), INF, 0 };
    g.node[25] = {25, "F", toRadian(105.84364787848264), toRadian(21.005092693449974), INF, 0 };
    g.node[26] = {26, "NDX-D4", toRadian(105.84249138211935), toRadian(21.004524927038492), INF, 0 };
    g.node[27] = {27, "NDX-D9", toRadian(105.84411731354535), toRadian(21.003989858779278), INF, 0 };
    g.node[28] = {28, "NDX-D5", toRadian(105.84489462659562), toRadian(21.00457274456316), INF, 0 };
    g.node[29] = {29, "NDX-C4", toRadian(105.84449015397965), toRadian(21.006385734663166), INF, 0 };

    
    // Tạo các cạnh kết nối 
    edge(&g.node[0], &g.node[1]); 
    edge(&g.node[0], &g.node[3]);
    edge(&g.node[1], &g.node[2]);
    edge(&g.node[1], &g.node[4]);
    edge(&g.node[2], &g.node[5]);
    edge(&g.node[5], &g.node[7]);
    edge(&g.node[7], &g.node[6]);
    edge(&g.node[7], &g.node[9]);
    edge(&g.node[7], &g.node[8]);
    edge(&g.node[8], &g.node[9]);
    edge(&g.node[9], &g.node[10]);
    edge(&g.node[8], &g.node[10]);
    edge(&g.node[9], &g.node[24]);
    edge(&g.node[10], &g.node[11]);
    edge(&g.node[11], &g.node[24]);
    edge(&g.node[11], &g.node[12]);
    edge(&g.node[12], &g.node[13]);
    edge(&g.node[12], &g.node[14]);
    edge(&g.node[13], &g.node[14]);
    edge(&g.node[13], &g.node[15]);
    edge(&g.node[14], &g.node[15]);
    edge(&g.node[15], &g.node[23]);
    edge(&g.node[15], &g.node[16]);
    edge(&g.node[23], &g.node[22]);
    edge(&g.node[23], &g.node[24]);
    edge(&g.node[23], &g.node[25]);
    edge(&g.node[25], &g.node[4]);
    edge(&g.node[4], &g.node[3]);
    edge(&g.node[16], &g.node[17]);
    edge(&g.node[17], &g.node[18]);
    edge(&g.node[18], &g.node[19]);
    edge(&g.node[18], &g.node[20]);
    edge(&g.node[19], &g.node[20]);
    edge(&g.node[17], &g.node[20]);
    edge(&g.node[17], &g.node[21]);
    edge(&g.node[20], &g.node[21]);
    edge(&g.node[16], &g.node[21]);
    edge(&g.node[16], &g.node[22]);
    edge(&g.node[21], &g.node[22]);
    edge(&g.node[3], &g.node[19]);
    edge(&g.node[3], &g.node[20]);
    edge(&g.node[3], &g.node[21]);
    edge(&g.node[11], &g.node[23]);

    //liệt kê danh sách các toà 
    cout << "Danh sách cac toà nhà\n";
    cout << "0.C1\n";
    cout << "1.C2\n";
    cout << "2.C9\n";
    cout << "6.D4\n";
    cout << "8.D8\n";
    cout << "9.D6\n";
    cout << "11.D9\n";
    cout << "12.D7\n";
    cout << "13.D3-5\n";
    cout << "14.D5\n";
    cout << "15.D3\n";
    cout << "16.C8\n";
    cout << "17.C7\n";
    cout << "18.C6\n";
    cout << "19.C3\n";
    cout << "20.C4\n";
    cout << "21.C5\n";
    cout << "22.C10\n";
    cout << "23.TV\n";
    cout << "24.Alumi\n";
    cout << "26.NDX-D4\n";
    cout << "27.NDX-D9\n";
    cout << "28.NDX-D5\n";
    cout << "29.NDX-C4\n";

    int start, end;
    cout<<"Nhập địa điểm hiện tại của bạn(nhập id): "; cin>>start;
    cout<<"Nhập chỗ bạn muốn đến(nhập id): "; cin>>end;
    // Gọi thuật toán Dijkstra
    dijsktra(&g, &g.node[start]);
    print(&g, &g.node[start], &g.node[end]);
	//In nhà gửi xe gần nhất
	reset_graph(&g);
	DNode gara = find_gara(&g, &g.node[start]);
	cout<<"Nhà để xe gần nhất: "<<gara->name;
	print(&g, &g.node[start], gara);
    return 0;
}