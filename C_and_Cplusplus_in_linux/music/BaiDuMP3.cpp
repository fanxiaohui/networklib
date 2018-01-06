#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {

    int n;         //移位值
    int i,j,k;     //循环变量
    char s;        //用来保存加密字符串的每个字符
    char str[62];  //数组保存字母和数字
    char ss[200];  //保存解密后的字符串

    if (argc != 2) {
        cout<<"\n此命令的语法是:\n\nBaiDuMP3 [url]\n\n";
    } else {
        for (i = 1; i < 63; i++) {
            if (i <= 26) {
                str[i] = i + 96;    //26个小写字母
            } else if (i <= 36) {
                str[i] = i + 21;    //10个数字
            } else {
                str[i] = i + 28;    //26个大写字母
            }
        }

        for (i = 1; i < 63; i++) {
            if (argv[1][0] == str[i]) {
                n = i - 8;  //计算移位值
                break;
            }
        }

        for (j = 0; j < strlen(argv[1]); j++) {
            s = argv[1][j];              //逐位取字符
            for (int i = 1; i < 63; i++) {
                if (str[i] == s) {         //查找在str数组中的位置
                    k = i - n;             //减去移位值
                    if (k < 0) {
                        s = str[k + 62];
                    } else if(k > 62) {
                        s = str[k - 62];
                    } else {
                        s = str[k];
                    }
                    break;
                }
            }
            ss[j] = s;
        }

        cout<<"\n解密后的音乐地址为：\n";

        for (i = 0; i < strlen(argv[1]); i++) {
            cout<<ss[i];
        }

        cout<<"\n\n";
    }
    system("PAUSE");
    return EXIT_SUCCESS;
}
