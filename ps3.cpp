#include<bits/stdc++.h>
using namespace std;
#define int long long int
int protocol_sz;
vector<string> access_list;
map<pair<int,int>,set<string>> map_access_list;
unordered_map<string,vector<string>> access_list_content;

void Access(int num1,int num2){
    for(auto child:map_access_list[{num1,num2}]){
        cout<<child<<endl;
        for(auto curr_protocol:access_list_content[child]){
            cout<<curr_protocol<<" ";
        }
        cout<<endl;
    }
    cout<<endl<<endl;
}

void ADD(int num1,int num2, string &s){
    map_access_list[{num1,num2}].insert(s);
    Access(num1,num2);
}

int getRandomGroup(){
    int x=(0+rand())%65537;
    return x;
}

int getPermit(){
    int y=(0+rand())%2;
    return y;
}

int getProtocol(){
    int z=(0+rand())%(protocol_sz);
    return z;
}

void generateAcessList(){
    // vector<string> accessList;
    access_list.clear();
    bool f=1;
    for(char i='a'; i<='z'; i++){
        for(char j='a'; j<='z'; j++){
            string access = "";
            access_list.push_back(access+i+j);
            if (access_list.size()==500){
                f=0;
                break;
            }
        }
        if(!f) break;

    }
}

void ttt(string& s){
    string num1_str="";
    string num2_str="";
    int ind=32;
    for(int i=32;;i++){
    ind=i;
    if(s[i]==' ') break;
    num1_str=num1_str+s[i];
    }
    // cout<<num1_str<<" ";
    int num1=stoi(num1_str);
    for(int i=ind+4;;i++)
    {
    ind=i;
    if(s[i]==' ') break;
    num2_str=num2_str+s[i];
    }
    // cout<<num2_str<<" ";
    int num2=stoi(num2_str);
    // cout<<num1<<" "<<num2<<endl;
    string list="";
    list=s.substr(ind+1);
    // cout<<list<<" ";
    // cout<<endl;
    ADD(num1,num2,list);
}

void generate_input(){
    // vector<string> access_list={"a","b","c","d","e","f","g","h","i","j"};
    vector<string> protocol={"ahp","eigrp","esp","gre","icmp","igmp","ip","ipinip","nos","ospf","pcp","pim","tcp","udp"};
    protocol_sz=protocol.size();
    access_list_content.clear();
    // unordered_map<string,vector<string>> access_list_content;
    for(int list_it=0;list_it<access_list.size();list_it++){
        // cout<<"Ip access-list role-based ";
        // cout<<access_list[list_it]<<endl;
        string temp=access_list[list_it];
        for(int rules_it=0;rules_it<20;rules_it++){
            if(rules_it%2==0){
                string query="";
                int x=getRandomGroup(),y=getRandomGroup(),isp=getPermit(),protocol_ind=getProtocol();
                query+=to_string(x);query+=" ";
                // cout<<x<<" ";
                // if(isp) cout<<"permit ";
                // else cout<<"deny ";
                if(isp) query+="permit ";
                else query+="deny ";
                if(y==x) y=(x+1)%65537;
                // cout<<y<<endl;
                query+=to_string(y);
                access_list_content[temp].push_back(query);
            }else{
                string query="";
                int x=getRandomGroup(),isp=getPermit(),protocol_ind=getProtocol();
                // cout<<x<<" ";
                query+=to_string(x);query+=" ";
                // if(isp) cout<<"permit ";
                // else cout<<"deny ";
                if(isp) query+="permit ";
                else query+="deny ";
                // cout<<protocol[protocol_ind]<<endl;
                query+=protocol[protocol_ind];
                access_list_content[temp].push_back(query);
            }
        }
    }
    // vector<string> access={"Allow_ICMP","Block_Malware","Block_ICMP","Allow_Malware"};
    vector<string> queries;
    for(int i=0; i<10000; i++){
        int source =0+rand()%65536;
        int destination=0+rand()%65536;
        int aceessIndex=0+rand()%4;
        // cout<<"Cts role - based permissions from "<<source<<" to "<<destination<<" "<<access_list[aceessIndex]<<endl;
        string tmp="Cts role-based permissions from ";
        tmp+=to_string(source);tmp+=" to ";
        tmp+=to_string(destination);tmp+=" ";
        tmp+=access_list[aceessIndex];
        queries.push_back(tmp);
    }
    for(int i=0;i<queries.size();i++) ttt(queries[i]);
}
signed main(){
    // int t;cin>>t;
    // while(t--){
        map_access_list.clear();
        generateAcessList();
        generate_input();
    // } 
}
