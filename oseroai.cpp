#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

void putpieces(int tate, int yoko,int iro);
bool check(int tate, int yoko, int iro);
int canput(int iro);
int ai(int iro);

int x = 8 ;
int mountofpiece=0;
int banmen[10][10]={
    {3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
    {3, 0, 0, 0, 0, 0, 0, 0, 0, 3},
    {3, 0, 0, 0, 0, 0, 0, 0, 0, 3},
    {3, 0, 0, 0, 0, 0, 0, 0, 0, 3},
    {3, 0, 0, 0, 1, 2, 0, 0, 0, 3},
    {3, 0, 0, 0, 2, 1, 0, 0, 0 ,3},
    {3, 0, 0, 0, 0, 0, 0, 0, 0 ,3},
    {3, 0, 0, 0, 0, 0, 0, 0, 0 ,3},
    {3, 0, 0, 0, 0, 0, 0, 0, 0 ,3},
    {3, 3, 3, 3, 3, 3, 3, 3, 3 ,3}
};


int main() {
int i,tate,yoko,iro,t;
    while(mountofpiece<64){
        i++;
        for(int n=0;n<10;n++){
            for(int m=0;m<10;m++){
                std::cout<<banmen[n][m]<<" ";
            }
            std::cout<<"\n";
        }
        if(i%2==1){
            iro=1;
            for(int n=0;n<10;n++){
                for(int m=0;m<10;m++){
                    if(check(n,m,iro)){
                        std::cout<<n<<m<<"\n";
                    }
                }
            }
            if(canput(iro)>0){
                do
                {
                    std::cout<<"\n場所をタイプ"<<iro;
                    std::cin>>tate;
                    std::cin>>yoko;
                } while (!check(tate,yoko,iro));
                putpieces(tate,yoko,iro);
            }
        }else if (i%2==0){
            iro=2;
            t=ai(iro);
            std::cout<<"\nAIは"<<t<<"におきます"<<std::endl;
            putpieces(t/10,t%10,iro);
            /*
            for(int n=0;n<10;n++){
                for(int m=0;m<10;m++){
                    if(check(n,m,iro)){
                        std::cout<<n<<m<<"\n";
                    }
                }
            }
            if(canput(iro)>0){
                do
                {
                    std::cout<<"\n場所をタイプ"<<iro;
                    std::cin>>tate;
                    std::cin>>yoko;
                } while (!check(tate,yoko,iro));
                putpieces(tate,yoko,iro);
            }*/
        }
    }
    return 0;
}
int ai(int iro){
    int teki;
    if(iro==1){
        teki=2;
    }else if (iro==2){
        teki=1;
    }
    int ky[10][10];
    for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                ky[i][j] = banmen[i][j];
            }
        }
    std::vector<int> okeru;
    std::vector<int> kazu;
    for(int i =1;i<9;i++){
        for(int j = 1;j<9;j++){
            if(check(i,j,iro))
                okeru.push_back((i*10)+j);
        }
    }
    for(int basyo : okeru){
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                banmen[i][j] = ky[i][j];
            }
        }
        putpieces((basyo/10)%10,basyo%10,iro);
        kazu.push_back(canput(teki));
    }
    auto min =std::min_element(kazu.begin(),kazu.end());
    int index = std::distance(kazu.begin(), min);
    for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                banmen[i][j] = ky[i][j];
            }
    }
    return okeru[index];
}

int canput(int iro){
    int k=0;
    for(int i=1;i<=8;i++){
        for(int j=1;j<=8;j++){
            if(check(i,j,iro)){
                k++;
            }else{}
        }
    }
    return k;
}

bool check(int tate, int yoko, int iro){
    int teki, i;
    if(iro==1){
        teki=2;
    }else if (iro==2){
        teki=1;
    }
    switch (iro){
    case 1:
        if(!banmen[tate][yoko]==0)
            break;
        if(banmen[tate-1][yoko]==teki){
            i=1;
            while(1){
                i++;
                if(banmen[tate-i][yoko]==teki){
                }else if (banmen[tate-i][yoko]==iro){
                    return true;
                }else{
                    break;
                }
            }
        }else if (banmen[tate+1][yoko]==teki){
            i=1;
            while(1){
                i++;
                if(banmen[tate+i][yoko]==teki){
                }else if (banmen[tate+i][yoko]==iro){
                    return true;
                }else{
                    break;
                }
            }
        }else if (banmen[tate][yoko-1]==teki){
            i=1;
            while(1){
                i++;
                if(banmen[tate][yoko-i]==teki){
                }else if (banmen[tate][yoko-i]==iro){
                    return true;
                }else{
                    break;
                }
            }
        }else if (banmen[tate][yoko+1]==teki){
            i=1;
            while(1){
                i++;
                if(banmen[tate][yoko+i]==teki){
                }else if (banmen[tate][yoko+i]==iro){
                    return true;
                }else{
                    break;
                }
            }
        }else if (banmen[tate+1][yoko+1]==teki){
            i=1;
            while(1){
                i++;
                if(banmen[tate+i][yoko+i]==teki){
                }else if (banmen[tate+i][yoko+i]==iro){
                    return true;
                }else{
                    break;
                }
            }
        }else if (banmen[tate-1][yoko+1]==teki){
            i=1;
            while(1){
                i++;
                if(banmen[tate-i][yoko+i]==teki){
                }else if (banmen[tate-i][yoko+i]==iro){
                    return true;
                }else{
                    break;
                }
            }
        }else if (banmen[tate+1][yoko-1]==teki){
            i=1;
            while(1){
                i++;
                if(banmen[tate+i][yoko-i]==teki){
                }else if (banmen[tate+i][yoko-i]==iro){
                    return true;
                }else{
                    break;
                }
            }
        }else if (banmen[tate-1][yoko-1]==teki){
            i=1;
            while(1){
                i++;
                if(banmen[tate-i][yoko-i]==teki){
                }else if (banmen[tate-i][yoko-i]==iro){
                    return true;
                }else{
                    break;
                }
            }
        }
        break;
    case 2:
        if(!banmen[tate][yoko]==0)
            break;
        if(banmen[tate-1][yoko]==teki){
            i=1;
            while(1){
                i++;
                if(banmen[tate-i][yoko]==teki){
                }else if (banmen[tate-i][yoko]==iro){
                    return true;
                }else{
                    break;
                }
            }
        }else if (banmen[tate+1][yoko]==teki){
            i=1;
            while(1){
                i++;
                if(banmen[tate+i][yoko]==teki){
                }else if (banmen[tate+i][yoko]==iro){
                    return true;
                }else{
                    break;
                }
            }
        }else if (banmen[tate][yoko-1]==teki){
            i=1;
            while(1){
                i++;
                if(banmen[tate][yoko-i]==teki){
                }else if (banmen[tate][yoko-i]==iro){
                    return true;
                }else{
                    break;
                }
            }
        }else if (banmen[tate][yoko+1]==teki){
            i=1;
            while(1){
                i++;
                if(banmen[tate][yoko+i]==teki){
                }else if (banmen[tate][yoko+i]==iro){
                    return true;
                }else{
                    break;
                }
            }
        }else if (banmen[tate+1][yoko+1]==teki){
            i=1;
            while(1){
                i++;
                if(banmen[tate+i][yoko+i]==teki){
                }else if (banmen[tate+i][yoko+i]==iro){
                    return true;
                }else{
                    break;
                }
            }
        }else if (banmen[tate-1][yoko+1]==teki){
            i=1;
            while(1){
                i++;
                if(banmen[tate-i][yoko+i]==teki){
                }else if (banmen[tate-i][yoko+i]==iro){
                    return true;
                }else{
                    break;
                }
            }
        }else if (banmen[tate+1][yoko-1]==teki){
            i=1;
            while(1){
                i++;
                if(banmen[tate+i][yoko-i]==teki){
                }else if (banmen[tate+i][yoko-i]==iro){
                    return true;
                }else{
                    break;
                }
            }
        }else if (banmen[tate-1][yoko-1]==teki){
            i=1;
            while(1){
                i++;
                if(banmen[tate-i][yoko-i]==teki){
                }else if (banmen[tate-i][yoko-i]==iro){
                    return true;
                }else{
                    break;
                }
            }
        }
        break;
    default:
        break;
    }
    return false;
}

void putpieces(int tate, int yoko,int iro){
    int i = 0;
    int teki;
    if(iro==1){
        teki=2;
    }else if (iro==2){
        teki=1;
    }
    switch (iro){
    case 1:
        for(int q = tate-1;x-q >= 0; q--){//ue
            i++;
            if(banmen[q][yoko]==iro){
                while(i>0){
                    banmen[tate-i][yoko]=iro;
                    i--;
                }
                break;
            }else if (banmen[q][yoko]==teki){
            }else if (banmen[q][yoko]==0){
                break;
            }else if (banmen[q][yoko]==3){
            }else{
                std::cout<<"error";
                break;
            }
        }
        i=0;
        for(int q = tate+1;q <= x; q++){//shita
            i++;
            if(banmen[q][yoko]==iro){
                while(i>0){
                    banmen[tate+i][yoko]=iro;
                    i--;
                }
                break;
            }else if (banmen[q][yoko]==teki){
            }else if (banmen[q][yoko]==0){
                break;
            }else if (banmen[q][yoko]==3){
                break;
            }else{
                std::cout<<"error";
                break;
            }
        }
        i=0;
        for(int q = yoko+1;q <= x; q++){//migi
            i++;
            if(banmen[tate][q]==iro){
                while(i>0){
                    banmen[tate][yoko+i]=iro;
                    i--;
                }
                break;
            }else if (banmen[tate][q]==teki){
            }else if (banmen[tate][q]==0){
                break;
            }else if (banmen[tate][q]==3){
                break;
            }else{
            std::cout<<"error";
            }
        }
        i=0;
        for(int q = yoko-1;q >= 0; q--){//hidari
            i++;
            if(banmen[tate][q]==iro){
                while(i>0){
                    banmen[tate][yoko-i]=iro;
                    i--;
                }
                break;
            }else if (banmen[tate][q]==teki){
            }else if (banmen[tate][q]==0){
                break;
            }else if (banmen[tate][q]==3){
                break;
            }else{
            }
        }
        i=0;
        for(int q = yoko-1, w = tate -1;q >= 0|| w>= 0; q--,w--){//hidarinanameue
            i++;
            if(banmen[w][q]==iro){
                while(i>0){
                    banmen[tate-i][yoko-i]=iro;
                    i--;
                }
                break;
            }else if (banmen[w][q]==teki){
            }else if (banmen[w][q]==0){
                break;
            }else if (banmen[w][q]==3){
                break;
            }else{
            }
        }
        i=0;
        for(int q = yoko+1, w = tate -1;q <x || w>= 0; q++,w--){//miginanameue
            i++;
            if(banmen[w][q]==iro){
                while(i>0){
                    banmen[tate-i][yoko+i]=iro;
                    i--;
                }
                break;
            }else if (banmen[w][q]==teki){
            }else if (banmen[w][q]==0){
                break;
            }else if (banmen[w][q]==3){
                break;
            }else{
            }
        }
        i=0;
        for(int q = yoko-1, w = tate +1;q >= 0|| w< x; q--,w++){//hidarinanameshita
            i++;
            if(banmen[w][q]==iro){
                while(i>0){
                    banmen[tate+i][yoko-i]=iro;
                    i--;
                }
                break;
            }else if (banmen[w][q]==teki){
            }else if (banmen[w][q]==0){
                break;
            }else if (banmen[w][q]==3){
                break;
            }else{
            }
        }
        i=0;
        for(int q = yoko+1, w = tate +1;q <= x|| w <= x; q++,w++){//miginanameshita
            i++;
            if(banmen[w][q]==iro){
                while(i>0){
                    banmen[tate+i][yoko+i]=iro;
                    i--;
                }
                break;
            }else if (banmen[w][q]==teki){
            }else if (banmen[w][q]==0){
                break;
            }else if (banmen[w][q]==3){
                break;
            }else{
            }
        }
    banmen[tate][yoko]=iro;
    mountofpiece++;
        break;
    case 2:
        for(int q = tate-1;x-q >= 0; q--){//ue
            i++;
            if(banmen[q][yoko]==iro){
                while(i>0){
                    banmen[tate-i][yoko]=iro;
                    i--;
                }
                break;
            }else if (banmen[q][yoko]==teki){
            }else if (banmen[q][yoko]==0){
                break;
            }else if (banmen[q][yoko]==3){
            }else{
                std::cout<<"error";
                break;
            }
        }
        i=0;
        for(int q = tate+1;q <= x; q++){//shita
            i++;
            if(banmen[q][yoko]==iro){
                while(i>0){
                    banmen[tate+i][yoko]=iro;
                    i--;
                }
                break;
            }else if (banmen[q][yoko]==teki){
            }else if (banmen[q][yoko]==0){
                break;
            }else if (banmen[q][yoko]==3){
                break;
            }else{
                std::cout<<"error";
                break;
            }
        }
        i=0;
        for(int q = yoko+1;q <= x; q++){//migi
            i++;
            if(banmen[tate][q]==iro){
                while(i>0){
                    banmen[tate][yoko+i]=iro;
                    i--;
                }
                break;
            }else if (banmen[tate][q]==teki){
            }else if (banmen[tate][q]==0){
                break;
            }else if (banmen[tate][q]==3){
                break;
            }else{
            std::cout<<"error";
            }
        }
        i=0;
        for(int q = yoko-1;q >= 0; q--){//hidari
            i++;
            if(banmen[tate][q]==iro){
                while(i>0){
                    banmen[tate][yoko-i]=iro;
                    i--;
                }
                break;
            }else if (banmen[tate][q]==teki){
            }else if (banmen[tate][q]==0){
                break;
            }else if (banmen[tate][q]==3){
                break;
            }else{
            }
        }
        i=0;
        for(int q = yoko-1, w = tate -1;q >= 0|| w>= 0; q--,w--){//hidarinanameue
            i++;
            if(banmen[w][q]==iro){
                while(i>0){
                    banmen[tate-i][yoko-i]=iro;
                    i--;
                }
                break;
            }else if (banmen[w][q]==teki){
            }else if (banmen[w][q]==0){
                break;
            }else if (banmen[w][q]==3){
                break;
            }else{
            }
        }
        i=0;
        for(int q = yoko+1, w = tate -1;q <x || w>= 0; q++,w--){//miginanameue
            i++;
            if(banmen[w][q]==iro){
                while(i>0){
                    banmen[tate-i][yoko+i]=iro;
                    i--;
                }
                break;
            }else if (banmen[w][q]==teki){
            }else if (banmen[w][q]==0){
                break;
            }else if (banmen[w][q]==3){
                break;
            }else{
            }
        }
        i=0;
        for(int q = yoko-1, w = tate +1;q >= 0|| w< x; q--,w++){//hidarinanameshita
            i++;
            if(banmen[w][q]==iro){
                while(i>0){
                    banmen[tate+i][yoko-i]=iro;
                    i--;
                }
                break;
            }else if (banmen[w][q]==teki){
            }else if (banmen[w][q]==0){
                break;
            }else if (banmen[w][q]==3){
                break;
            }else{
            }
        }
        i=0;
        for(int q = yoko+1, w = tate +1;q <= x|| w <= x; q++,w++){//miginanameshita
            i++;
            if(banmen[w][q]==iro){
                while(i>0){
                    banmen[tate+i][yoko+i]=iro;
                    i--;
                }
                break;
            }else if (banmen[w][q]==teki){
            }else if (banmen[w][q]==0){
                break;
            }else if (banmen[w][q]==3){
                break;
            }else{
            }
        }
    banmen[tate][yoko]=iro;
    mountofpiece++;
        break;
    default:
        std::cout<<"error3";
        break;
    }
    return;
}
