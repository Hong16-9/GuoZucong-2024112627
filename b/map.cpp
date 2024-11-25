//我用的是张毅学长教我的A*算法，所以会存在一些情况不是最优解
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
class yyy
{
private:
    
public:
    int x = -1;
    int y = -1;
    double cost = 10005;
    int manba = 10005;
};
int main()
{
    int n,m;
    double t;
    cin >>n>>m;
    vector <vector <int>> map (n+2,vector <int>(m+2));
    vector <vector <yyy>> mapout (n+2,vector <yyy>(m+2));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> map[i][j];
        }
        
    }
    cin >>t;
    int x1,y1,x2,y2;
    cin >>x1>>y1>>x2>>y2;
    x1++;y1++;x2++;y2++;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            mapout[i][j].cost = (map[i][j-1] + map[i-1][j] + map[i+1][j] + map[i][j+1])*t + map[i][j];
            mapout[i][j].x = i-1;
            mapout[i][j].y = j-1;
        }
        
    }
    double sum = 0;
    int aa=x1,bb=y1;
    while (aa!=x2 || bb!=y2)
    {
        int mamba_left = 100005;
        int mamba_right = 100005;
        int mamba_up = 100005;
        int mamba_down = 100005;
        if (mapout[aa][bb].x!=0)
        {
            mamba_up = abs(mapout[x2][y2].x - mapout[aa-1][bb].x)+abs(mapout[x2][y2].y - mapout[aa-1][bb].y);
            mapout[aa-1][bb].manba = mamba_up;
        }
        if (mapout[aa][bb].y!=0)
        {
            mamba_left = abs(mapout[x2][y2].x - mapout[aa][bb-1].x)+abs(mapout[x2][y2].y - mapout[aa][bb-1].y);
            mapout[aa][bb-1].manba = mamba_left;
        }
        if (mapout[aa][bb].x!=n-1)
        {
            mamba_down = abs(mapout[x2][y2].x - mapout[aa+1][bb].x)+abs(mapout[x2][y2].y - mapout[aa+1][bb].y);
            mapout[aa+1][bb].manba = mamba_down;
        }
        if (mapout[aa][bb].y!=m-1)
        {
            mamba_right = abs(mapout[x2][y2].x - mapout[aa][bb+1].x)+abs(mapout[x2][y2].y - mapout[aa][bb+1].y);
            mapout[aa][bb+1].manba = mamba_right;
        }
        vector<yyy> jud (4);
        jud[0] = mapout[aa-1][bb];
        jud[1] = mapout[aa][bb-1];
        jud[3] = mapout[aa+1][bb];
        jud[2] = mapout[aa][bb+1];
        yyy temp;
        temp = *min_element(jud.begin(),jud.end(),[](
            yyy a,yyy b
        ){
            return a.cost+a.manba < b.cost+b.manba;
        });
        sum += temp.cost;
        mapout[aa][bb].cost = 10005;
        int temp1 = temp.x+1;
        int temp2 = temp.y+1;
        aa = temp1; bb = temp2;
    }
    cout <<sum <<endl;
    return 0;
}