#include <bits/stdc++.h>
using namespace std;

auto read_csv(string filename){
    vector<pair<string, vector<int>>> result;
    map<string,map<string,float>> data;
    ifstream myFile(filename);
    if(!myFile.is_open()) throw runtime_error("No hay Archivo （°o°) ");
    string line, colname;
    int val;
    if(myFile.good()){
        getline(myFile, line);
        stringstream ss(line);
        while(getline(ss, colname, ',')){
            result.push_back({colname, vector<int> {}});
        }
    }
    while(getline(myFile, line)){
        stringstream ss(line);
        //cout<<line<<endl;
        
        vector<std::string> resultado;
        string::const_iterator itBegin = line.begin();
        string::const_iterator itEnd   = line.end();

        int numItems = 1;
        for( std::string::const_iterator it = itBegin; it!=itEnd; ++it )
            numItems += *it==',';

        resultado.reserve(numItems);
        for( string::const_iterator it = itBegin; it!=itEnd; ++it ){
            if( *it == ',' ){
                resultado.push_back(std::string(itBegin,it));
                itBegin = it+1;
            }
            
        }
        data[resultado[0]][resultado[1]]=stof(resultado[2]);
        //cout<<resultado[2]<<endl;
    }
    myFile.close();
    return data;
}

double pearson(map<string,map<string,float>> d, string key1, string key2){
    int dimension = 0;
    double cal1 = 0;
    vector<double> cal2(2);
    vector<double> cal3(2);
    
    for (auto i:d[key1]){
        auto it = d[key2].find(i.first);
        if(it!=d[key2].end()){
            //cout<<(*it).second<<endl;
            dimension++;
            double v_key1 = d[key1][(*it).first];
            double v_key2 = d[key2][(*it).first];
            cal1 += v_key1*v_key2;
            cal2[0] += v_key1;
            cal2[1] += v_key2;
            cal3[0] += v_key1*v_key1;
            cal3[1] += v_key2*v_key2;
            
        }
    }
    double cal5_n = sqrt(cal3[0]-pow(cal2[0],2)/dimension)*sqrt(cal3[1]-pow(cal2[1],2)/dimension);
    double cal2_n = (cal1-(cal2[0]*cal2[1])/dimension);
    if(cal5_n == 0){
        return 0;
    }
    double r = cal2_n/cal5_n;
    //cout<<cal1<<"\t"<<cal2[0]<<"\t"<<cal2[1]<<"\t"<<cal3[0]<<"\t"<<cal3[1]<<endl;
    return r;
}


int main() {
    map<string,map<string,float>> Data = read_csv("ratings.csv");
    cout<<pearson(Data,"4","20");
    return 0;
}