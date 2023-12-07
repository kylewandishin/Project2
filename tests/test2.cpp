#include <iostream>
// small scale demo
void changeMe(int& num){
    num -= 1;
}
int main(){
    int a = (0>5 ? 7 : 0);
    changeMe(a);
    printf("%d\n",a);
}