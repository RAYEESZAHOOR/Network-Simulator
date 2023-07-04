#include <iostream>
#include <time.h>
#include <bits/stdc++.h>
using namespace std;



void delay(int t)
{
    t += 1;
    t *= 10e7;
    t *= 2;
    while (t)
    {
        t--;
    }
    return;
}

void sendDataAnimation()
{
    for (int i = 0; i < 20; i++)
    {
        cout << "#";
        delay(1);
    }
    cout << endl;
    return;
}

string macAdress()
{
    unordered_map<int, char> map_1;
    for (int i = 10; i <= 15; i++)
        map_1[i] = 'A' + i - 10;

    string string_1 = "";
    for (int j = 0; j < 6; j++)
    {
        string string_2;

        int generated_no;
        for (int i = 0; i < 2; i++)
        {
            generated_no = rand() % 16;
            string_2 += generated_no >= 10 ? map_1[generated_no] : '0' + generated_no;
        }

        string_1 += string_2;
        if (j != 5)
            string_1 += ':';
    }
    return string_1;
}

string network_id(string a)
{
    int n = a.length();
    int i;
    for (i = n - 1; i >= 0; i--)
    {
        if (a[i] == '.')
            break;
    }
    return a.substr(0, i + 1);
}


//  graph class and other related functions.----------------------------------
class edge
{
public:
    int u, v, weight;
    friend bool operator<(edge &a, edge &b);
    friend bool operator>(edge &a, edge &b);
};

bool operator<(edge &a, edge &b)
{
    if (a.weight < b.weight)
        return true;
    return false;
}
bool operator>(edge &a, edge &b)
{
    if (a.weight > b.weight)
        return true;
    return false;
}


class amGraph
{
    int V = 0;
    int E = 0;
    bool isDirected, isWeighted;
    int **matrix;

public:
    amGraph(int v = 0, bool d = false, bool w = false)
    {
        this->V = v, this->isDirected = d, this->isWeighted = w;

        this->matrix = new int *[V + 1];
        for (int i = 0; i < V + 1; i++)
        {
            this->matrix[i] = new int[V + 1];

            for (int j = 0; j < V + 1; j++)
            {
                matrix[i][j] = 0;
            }
        }
    }

    void addEdge(int u, int v, int weight = 1)
    {
        this->matrix[u][v] = weight;
        if (this->isDirected == false)
            this->matrix[v][u] = weight;
        E++;
    }

    void removeEdge(int u, int v)
    {
        this->matrix[u][v] = 0;
        if (this->isDirected == false)
            this->matrix[v][u] = 0;
        E--;
    }

    void printGraph()
    {
        cout << "*       ";
        for (int i = 0; i < this->V + 1; i++)
        {
            if (i == 0)
            {
                cout << setw(2);
                continue;
            }
            cout << setw(2) << i;
        }
        cout << "\n-----------------\n";

        for (int i = 1; i < V + 1; i++)
        {
            cout << "|" << i << "| --> ";
            for (int j = 1; j < V + 1; j++)
            {
                cout << setw(2) << matrix[i][j];
            }
            cout << endl;
        }
    }


    void dijkstraws(int k)
    {
        if (k > V)
        {
            cout << "invalid router\n";
            return;
        }

        int processed[V + 1] = {0};
        int distance[V + 1];
        distance[k] = 0;
        for (int i = 1; i < V + 1; i++)
        {
            if (i == k)
                continue;
            distance[i] = INT_MAX;
        }

        int count = V;
        while (count--)
        {
            int j = INT_MAX;
            int mini = INT_MAX;
            for (int i = 1; i < V + 1; i++)
            {
                if (processed[i] == 1)
                    continue;

                if (distance[i] < mini)
                {
                    mini = distance[i];
                    j = i;
                }
            }

            processed[j] = 1;

            for (int i = 1; i < V + 1; i++)
            {
                if (matrix[j][i] > 0)
                {
                    distance[i] = min(distance[i], distance[j] + matrix[j][i]);
                }
            }
        }

        cout << "distances of routers from source router " << k << endl;
        cout << "router   distace\n";
        for (int i = 1; i < V + 1; i++)
        {
            if (i == k)
                continue;
            cout << i << " --------> " << distance[i] << endl;
        }
    }
};

//----------------------------------------------------------


void network_layer()
{
    cout<<"1. ARP\n";
    cout<<"2. Open Shortest Path First - Dynamic Routing PROTOCOL\n";
    cout<<"3. static routing\n";
    int n;
    cin >> n;
    if (n == 1)
    {
        map<string, int> r_table;
        r_table["20.0.0.0"] = 1;
        r_table["40.0.0.0"] = 2;
        // r_table["0.0.0.0"] = 2;
        auto r_mac = macAdress();
        map<string, string> ARP_r;

        int n_of_N, n1, n2;
        // cout<<"Enter number of networks connected to router: ";
        cout << "no of devices in network 1: ";
        cin >> n1;

        cout << "no of devices in network 2: ";
        cin >> n2;

        // 20.0.0.0/24 for network 1 and 40.0.0.0/24 for network 2
        vector<string> mac_n1;
        vector<string> mac_n2;

        for (int i = 0; i < n1; i++)
            mac_n1.push_back(macAdress());
        for (int i = 0; i < n2; i++)
            mac_n2.push_back(macAdress());

        map<int, pair<string, string>> id_to_IP_MAC;
        for (int i = 1; i <= n1; i++)
        {
            string x = "20.0.0.";
            x.append(to_string(i));
            id_to_IP_MAC[i] = make_pair(x, mac_n1[i - 1]);
        }
        for (int i = 1; i <= n2; i++)
        {
            string x = "40.0.0.";
            x.append(to_string(i));
            id_to_IP_MAC[i + n1] = make_pair(x, mac_n2[i - 1]);
        }

        cout << "\n\n\n\nnetwork 1 devices:\n\n";
        cout << "id    IP Adress     Mac Adress\n\n";
        for (auto e : id_to_IP_MAC)
        {
            cout << e.first << "     " << e.second.first << "      " << e.second.second << endl;
            if (e.first == n1)
            {
                cout << "network 2 devices:\n\n";
                cout << "id    IP Adress     Mac Adress\n\n";
            }
        }
        cout << "\n\n\n\n";
        // cout<<"\n\n\n\nIP Address      MAC Address\n\n";
        // for (int i = 0; i < n1; i++)
        // {
        //     cout << "20.0.0." << i+1 << "/24     " << mac_n1[i]<<endl;
        // }

        map<int, string> switch1;
        for (int i = 1; i <= n1; i++)
            switch1[i] = mac_n1[i - 1];
        map<int, string> switch2;
        for (int i = 1; i <= n2; i++)
            switch2[i] = mac_n2[i - 1];

        map<string, string> ARP[n1 + n2]; // IP TO MAC

        // adding mac and ip's to router's arp.
        for (int i = 1; i <= n1; i++)
            ARP_r[id_to_IP_MAC[i].first] = id_to_IP_MAC[i].second;
        for (int i = n1 + 1; i <= n1 + n2; i++)
            ARP_r[id_to_IP_MAC[i].first] = id_to_IP_MAC[i].second;

        int t = true;
        while (t == true)
        {
            int d1, d2;
            cout << "Enter source device id: ";
            cin >> d1;
            cout << "Enter destination device id: ";
            cin >> d2;

            if (network_id(id_to_IP_MAC[d1].first) == network_id(id_to_IP_MAC[d2].first))
            {
                delay(3);
                cout << "NID's are same => so both devices are from same network.\n\n";
                delay(3);
                cout << "checking ARP Cache.\n\n";
                delay(3);
                if (ARP[d1].find(id_to_IP_MAC[d2].first) != ARP[d1].end())
                {
                    cout << "device mac found in ARP Cache.\n\n";
                    delay(3);
                    cout << "sending data to device 2\n\n";
                    delay(3);
                    sendDataAnimation();
                }
                else
                {
                    cout << "device mac not found in ARP Cache.\n\n";
                    delay(3);
                    cout << "sending ARP request.\n\n";
                    delay(3);
                    for (int i = 0; i < n1; i++)
                    {
                        if (i + 1 == d2)
                        {
                            cout << "device with IP " << id_to_IP_MAC[d2].first << " found with MAC Adress " << id_to_IP_MAC[d2].second << endl;
                            delay(3);
                            ARP[d1][id_to_IP_MAC[d2].first] = id_to_IP_MAC[d2].second;
                            delay(3);
                            cout << "sending ARP Responce.\n\n";
                            break;
                        }
                    }

                    cout << "sending data to device 2\n\n";
                    sendDataAnimation();
                }
            }
            else // diffrent networks
            {
                cout << "NID's are diffrent => so both devices are from diffrent network.\n\n";
                cout << "checking in source's ARP Cache.\n\n";
                if (ARP[d1].find(id_to_IP_MAC[d2].first) != ARP[d1].end())
                {
                    cout << "device mac found in ARP Cache.\n\n";
                    delay(3);

                    cout << "sending data to router.\n\n";
                    delay(3);
                    sendDataAnimation();
                    cout << "searching for interface from routing table.\n\n";
                    delay(3);

                    bool flag = false;
                    for (auto x : r_table)
                    {
                        if (network_id(id_to_IP_MAC[d2].first) == network_id(x.first))
                        {
                            cout << "router will transmit the packet from interface " << x.second << ".";
                            delay(3);
                            cout << "router will now send ARP request to network on interface " << x.second << "\n\n";
                            delay(3);
                            flag = true;
                            break;
                        }
                    }
                    delay(3);
                    if (!flag)
                    {
                        cout << "router will transmit the packet through default gateway.\n\n";
                        delay(3);
                    }

                    cout << "now reciver will send ARP responce to router.\n\n";
                    delay(3);

                    cout << "searching receivers mac from router's ARP Cache.\n\n";
                    delay(3);
                    for (auto x : ARP_r)
                    {
                        if (id_to_IP_MAC[d2].first == x.first)
                        {
                            cout << "sending data from router to reciver with MAC " << x.second << "\n\n";
                            delay(3);
                            sendDataAnimation();
                        }
                    }
                }
                else
                {
                    cout << "Destination mac not found in source's ARP Cache.\n\n";
                    delay(3);
                    cout << "sending ARP request to Router.\n\n";
                    delay(3);
                    ARP[d1][id_to_IP_MAC[d2].first] = id_to_IP_MAC[d2].second;

                    cout << "ARP Responve recived from router.\n\n";
                    delay(3);

                    cout << "sending data to router.\n\n";
                    delay(3);
                    sendDataAnimation();
                    cout << "searching for interface from routing table.\n\n";

                    bool flag = false;
                    for (auto x : r_table)
                    {
                        if (network_id(id_to_IP_MAC[d2].first) == network_id(x.first))
                        {
                            cout << "router will transmit the packet from interface " << x.second << ".";
                            delay(3);
                            cout << "router will now send ARP request to network on interface " << x.second << "\n\n";
                            delay(3);
                            flag = true;
                            break;
                        }
                    }
                    if (!flag)
                    {
                        cout << "router will transmit the packet through default gateway.\n\n";
                        delay(3);
                    }

                    cout << "now reciver will send ARP responce to router.\n\n";
                    delay(3);

                    cout << "searching receivers mac from router's ARP Cache.\n\n";
                    delay(3);
                    for (auto x : ARP_r)
                    {
                        if (id_to_IP_MAC[d2].first == x.first)
                        {
                            cout << "sending data from router to reciver with MAC " << x.second << "\n\n";
                            delay(3);
                            sendDataAnimation();
                        }
                    }
                }
            }
        }
    }

    else if(n==2)
    {
        // amGraph tmp(4, false, true);
        // tmp.addEdge(1, 2, 10);
        // tmp.addEdge(2, 3, 7);
        // tmp.addEdge(3, 4, 8);
        // cout<<"\ntopology:\n";
        // tmp.printGraph();
        // cout<<"\nOSPF calculated distances:\n";
        // tmp.dijkstraws(1);

        cout<<"R1 with IP 10.0.0.1 is connected with R2 with IP 20.0.0.1 and device with IP 10.0.0.2\n";
        cout<<"R2 with IP 20.0.0.1 is connected with R3 with IP 30.0.0.1 and device with IP 20.0.0.2\n";
        cout<<"R3 with IP 30.0.0.1 is connected with R4 with IP 40.0.0.1 and device with IP 30.0.0.2\n";
        int n1,n2;
        cout<<"Enter sender device.";
        cin>>n1;
        cout<<"Enter reciver device.";
        cin>>n2;
        cout<<"device" << n1 << "try to send data but data transfer fails as routing table of r1 don't have IP of next hop\n";

        cout<<"now throw static routing";
        
        map<int, string> device_id_IP;
        device_id_IP[1] = "10.0.0.2";
        device_id_IP[2] = "20.0.0.2";
        device_id_IP[3] = "30.0.0.2";
        string r_nid = network_id(device_id_IP[n2]);

        map<string, string> r1_m,r2_m, r3_m, r4_m;
        r1_m["30.0.0."] = "20.0.0.1";
        r1_m["20.0.0.0"] = "20.0.0.3";
        r1_m["10.0.0.3"] = "30.0.0.3";

        r2_m["20.0.0.1"] = "30.0.0.1";
        r2_m["30.0.0.2"] = "20.0.0.2";
        r2_m["20.0.0.2"] = "10.0.0.3";

        cout<<"device 1 trying to send packet to device 3 using static routing\n";
        cout<<"packet is transferred from r1 to r2.\n";
        cout<<"packet is transferred from r2 to r3.\n";
        cout<<"finally packet is recived by device 3 which is connected to router 3.\n";




    }
    else if(n==3)
    {
        amGraph tmp(4, false, true);
        tmp.addEdge(1, 2, 4);
        tmp.addEdge(2, 3, 5);
        tmp.addEdge(3, 4, 6);
        tmp.addEdge(4, 1, 7);
        cout<<"\ntopology:\n";
        tmp.printGraph();
        cout<<"\nManually calculated optimal distances:\n";
        cout<<"distances of routers from source router2\nrouter   distace\n1 --------> 4\n3 --------> 5\n4 --------> 11"<<endl;
    }

}

void transport_layer()
{
    int n1,n2;
    cout<<"Enter number of processes in sender. ";
    cin>>n1;
    cout<<"Enter number of processes in reciver. ";
    cin>>n2;

    cout<<"\n\nsender side:\n";
    cout<<"process-id   port no\n";
    for(int i=1; i<=n1; i++)
        cout<<i<<endl;
    
    
    map<int,int> ports_recvr;
    for(int i=1 ; i<=n2; i++)
        ports_recvr[i] =  rand()%1024;
    
    cout<<"\nreciver side:\n";
    cout<<"process-id   port no\n";
    for(auto x : ports_recvr)
        cout<<x.first<<"            "<<x.second<<endl;


    while(true)
    {
        int p1,p2;
        cout<<"\n\nEnter sender process id. ";
        cin>>p1;
        cout<<"Enter reciver process id. ";
        cin>>p2;
        string data;
        cout<<"enter data: ";
        cin>>data;


        cout<<"\nsender  socket (IP and Port): 10.0.0.1  - "<<1024 + rand()%(65535-1024+1)<<endl;
        cout<<"reciver socket (IP and Port): 10.0.0.2  - "<<ports_recvr[p2];

        cout<<"\n\nprotocol used to send data is Go Back 4.\n\n";  
        delay(2);
        int wp = 0;//pointer for implimenting window.
        while(wp<data.size())
        {   
            string tmp = data.substr(wp,4);
            cout<<"window: "<< tmp <<" transmitting\n";
            int wp_local=wp;
            for(int i=0; i<tmp.size() ; i++)
            {
                int bit_recived = rand()%100;
                if(bit_recived<50) // not recived.
                {   //ack recived
                    cout<<"    ACK for bit "<<i+1<<" recived\n";
                    wp_local = wp+i+1;
                }
            }
            if(wp_local == wp)
                cout<<"NO ACK RECIVED.";
            delay(2);
            wp = wp_local;
            cout<<endl;
        }

        cout<<"\n\n";
    }
    
}

void application_layer()
{
    srand(time(0));

    string macAddress = macAdress();
    string networkID = network_id("192.168.1.1");

    cout << "MAC Address: " << macAddress << endl;
    cout << "Network ID: " << networkID << endl;

    cout << "Application Layer - Sending data..." << endl;
    sendDataAnimation();
    return;
}

int main()
{
    srand(time(NULL));//to generate random through out the program.
    cout << "choose layer:\n";
    cout << "3. Network Layer\n";
    cout << "4. Transport Layer\n";
    cout << "5.Application Layer\n";

    int n;
    cin >> n;
    cout<<endl;

    if (n == 3)
        network_layer();
    else if (n == 4)
        transport_layer();
    else if (n == 5)
        application_layer();



    char  getChar;
    cin>> getChar;
    return 0;
}