#include <iostream>
#include <string>

using namespace std;

//整数转罗马数字，输入在1~3999
//这题除了细心，不知道在考啥，也可以给个数组存入罗马字符，不过时间复杂度相差不大
string intToRoman(int num)
{
    string s;
    while(num)
    {
        if(num >= 1000)
        {
            s += 'M';
            num -= 1000;
        }
        else if(num >= 500)
        {
            if(num >= 900)
            {
                s += "CM";
                num -= 900;
            }
            else
            {
                s += 'D';
                num -= 500;
            }
        }
        else if(num >= 100)
        {
            if(num >= 400)
            {
                s += "CD";
                num -= 400;
            }
            else
            {
                s += 'C';
                num -= 100;
            }
        }
        else if(num >= 50)
        {
            if(num >= 90)
            {
                s += "XC";
                num -= 90;
            }
            else
            {
                s += 'L';
                num -= 50;
            }
        }
        else if(num >= 10)
        {
            if(num >= 40)
            {
                s += "XL";
                num -= 40;
            }
            else
            {
                s += 'X';
                num -= 10;
            }
        }
        else if(num >= 5)
        {
            if(num >= 9)
            {
                s += "IX";
                num -= 9;
            }
            else
            {
                s += 'V';
                num -= 5;
            }
        }
        else if(num >= 1)
        {
            if(num >= 4)
            {
                s += "IV";
                num -= 4;
            }
            else
            {
                s += 'I';
                num -= 1;
            }
        }
    }

    return s;
}

int main()
{
    cout << intToRoman(3) << endl;
    cout << intToRoman(4) << endl;
    cout << intToRoman(9) << endl;
    cout << intToRoman(58) << endl;
    cout << intToRoman(1994) << endl;
}

