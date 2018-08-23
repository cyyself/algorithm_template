//欧拉函数的定义为小于等于x的数中有多少个数与x互质
#include <iostream>
using namespace std;
int phi[40005];
int main() {
    int n;
    cin >> n;
    phi[1] = 1;
    for (int i=2;i<=n;i++) {
        if (phi[i] == 0) for (int j=i;j<=n;j+=i) {
            if (phi[j] == 0) phi[j] = j;
            phi[j] = phi[j] / i * (i - 1);
        }
    }//CYY也不知道怎么证明，闷声背代码吧
    cout << phi[n] << endl;
    return 0;
}
