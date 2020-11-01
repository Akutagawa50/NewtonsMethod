#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

ofstream of;
const double x0 = 3;            //関数に与える初期値
const double eps = 0.000001;    //許容誤差
int funcmode = 0;   //解析する関数を選ぶ変数

float func(int mode, double x){ //f(x)の中身　funcmodeの値で変わる
    switch (mode){
    case 0:
        return x + cos(x);
    case 1:
        return pow(x-7.53, 2) - 3.15; //f(x)=(x-7.35)^2 - 3.15

    case 2:
        return exp(x) - 5;            //f(x)=e^x - 5
    default:
        return 9999.0; //エラー
    }
}

float dfunc(int mode, double x){    //funcを数値微分したものを返す
    return (func(mode, x+eps)-func(mode, x))/eps;
}

bool NewtonRaphsonMethod(double *x, int nmax){
    int n=0;        //ループ回数をカウント
    double fx=0.0;  //関数にｘを代入したときの値
    double dfx=0.0; //微分した関数にxを代入した値

    //funcmodeごとにcsvファイルを開く
    switch (funcmode){
    case 0:
        of.open("funcmode0.csv", ios::trunc);
        break;
    case 1:
        of.open("funcmode1.csv", ios::trunc);
        break;
    case 2:
        of.open("funcmode2.csv", ios::trunc);
        break;
    default:
        return false;
    }
    if(!of){
        cout << "オープンエラー" << endl;
        return false;
    }
    
    //初期値をファイルとコンソールに出力
    of << *x << "\t" << fixed << func(funcmode, *x) << endl;
    cout << "x= " <<*x << "\tf(x)= " << func(funcmode, *x) << endl;

    //Newton法で計算
    do{
        fx=func(funcmode, *x);  //f(x)を計算
        dfx=dfunc(funcmode, *x);   //f(x)を数値微分
        *x=-fx/dfx + *x;    //y=0との交点をxに代入

        //値をファイルとコンソールに出力
        of << *x << "\t" << func(funcmode, *x) << endl;
        cout << "x= " <<*x << "\tf(x)= " << func(funcmode, *x) << endl;

        if(fabs(func(funcmode, *x))<eps){    //収束したら終了
            of.close();
            return true;
        }
        n++;
    }while(n<nmax);
    of.close();
    return false;
}

int main(void){
    double x=x0;
    if(NewtonRaphsonMethod(&x, 100)){
        cout << "収束しました"<< endl;
        cout << "x = " << x << endl;
        cout << "f(x) = " << fixed << func(funcmode, x) << endl;
    }
    else
        cout << "収束しませんでした" << endl;
    
    return 0;
        
}