struct Matrix{
    int w,h;
    int num[60][60];
    Matrix(int w,int h):w(w),h(h) {
        memset(num,0,sizeof(num));
    }
    Matrix operator *(const Matrix &a) const{
        Matrix t(w,a.h);
        for (int i=0;i<w;i++)
            for (int j=0;j<a.h;j++)
                for (int k=0;k<h;k++){
                    t.num[i][j] += num[i][k] * num[k][j];
                }
        return t;
    }
    void ClearHor(int line){
        for (int i=0;i<w;i++) num[line][i] = 0;
    }
    void ClearVer(int line){
        for (int i=0;i<h;i++) num[i][line] = 0;
    }
};