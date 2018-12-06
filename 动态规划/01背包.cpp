#include <iostream>
#include <cstring>
#include <algorithm>
#define MAXN 100
#define MAXV 100
//MAXN和MAXV根据题目自行调整
using namespace std;
int main(){
 int v;//背包的容积
 int n;//物品的数量
 cin >> v >> n;
 int V[MAXN];//物品的体积（数组下标从1开始）V[i]相当于前文所述的Vi
 int P[MAXN];//物品的价值（数组下标从1开始）P[i]相当于前文所述的Pi
 for (int i=1;i<=n;i++) cin >> V[i] >> P[i];
 int f[MAXN][MAXV];//用于保存递推过程的数组
 memset(f,0,sizeof(f));//清零f数组，特别是f[0]的每项元素都必须为0
 for (int i=1;i<=n;i++)//处理编号为i的物品是否要放入背包中
   for (int j=1;j<=v;j++)//枚举背包的容积从1到最大值v
     if (V[i] <= j) {
     //确保该物品可以放入背包（在可能清空别的物品的情况下）
     f[i][j] = max(f[i-1][j],f[i-1][j-V[i]]+P[i]);
     /*上一行代码特别说明一下:
     f[i-1][j]是在本次不放入编号为i的物体情况下背包的内物品的最大价值和。
     f[i-1][j-V[i]]是背包在放入编号为i的物品前，
     在背包容积只有j-V[i]的情况下背包内物品的最大价值和，
     这样就明白为什么要从1开始枚举背包的容积到最大值v了吧。
     P[i]不必多言，还要再放上该物品，因此要加上它的价值。
     max函数的巧妙在于直接决定放i与否可以取得最大值。
     */
     }
     else f[i][j] = f[i-1][j];//这个物品的体积超过了我们目前枚举的背包容积j，因此不放入它，保持上次的原样
 cout << f[n][v] << endl;//这里求得的f[n][v]即为所求放入背包内的物品的最大价值和。
 return 0;
}