#include <iostream>
#include <stdlib.h>
#include <fstream>
using namespace std;

class operation 
{
    string key;
    int possition;
    bool ext = true;

public:
  
    string path;
    int sz;
    int arr[100][100];

    operation(string pth) { path = pth; possition = 0; }
    operation();

    string Read();
    bool ReturnExt() { return ext; }
    virtual void Reset(){};
};
string operation::Read()
{
    ifstream in(path);
    ofstream out("logs.txt", ios_base::app);
    // якщо файл вдалось відкрити
    if (in.is_open())
    {
        cout << "Reading matrix" << endl;
        key = "";
        string buff;
        string iner;
        sz = 0;        
        int counter = 0, counter2 = 1, p = 0, p2 = 1, poss2 = 0, rows = 0;
        //здійснюємо прохід через весь файл
        while (!in.eof())
        {    
            in >> buff;
            //починаємо з позиції на якій закінчили
            if (poss2 >= possition)
            {
                if (counter2 == 0)
                {
                    //перевірка чи матриця квадратна
                    if (rows != sz)
                    {
                        out << "The matrix is no square";
                        exit(0);
                    }
                    possition = poss2;
                    out << "-----Reseted matrix-----" << endl;
                    return key;
                }

                counter++;

                //зчитуэмо розмір масиву, ключ обнулення та перевіряємо на кінець файлу
                if (counter - (sz + 1) == p)
                {
                    if (buff == "end_of_file") 
                    {
                        out << "end_of_file" << endl;
                        ext = false;
                        return "";
                    }
                    for (int i = 0; i < buff.size(); i++)
                    {                       
                        if (buff[i] == '-')
                        {                          
                            sz = atoi(iner.c_str());
                            if (sz > 100)
                            {
                                cout << "Max matrix size 100" << endl;
                                ext = false;
                                return "";                              
                            }
                            for (int j = 1; j <= 3; j++)
                            {
                                key += buff[i+j];                               
                            }
                            iner = "";
                            counter2 = sz;
                            counter = 0;
                            break;
                        }
                        iner += buff[i];
                    }
                    out << buff << endl;
                }

                //зчитуємо сам масив
                else
                {
                    //Число ком у рядку
                    int j = 0;
                    string number;
                    for (int i = 0; i <= buff.size(); i++)
                    {

                        if (buff[i] == ','|| i == buff.size())//якщо кома тоді записуємо число
                        {
                            arr[sz - counter2][j] = atoi(number.c_str());
                            j++;
                            number = "";
                            continue;
                        }
                        number += buff[i];
                    }
                    out << buff <<endl;
                    rows++;
                    counter2--;
                }
            }
            poss2++;
        }

    }
    else
    {
        cout << "Error" << endl;
        exit(0);
    }
    in.close();
    out.close();
}
operation::operation()
{
}
//класи-нащадки--------------------------------------------
class Reset_above_main : public operation
{
public:
    Reset_above_main(int size, int arrsimb[100][100]);
    void Reset()
    {    
        ofstream out("logs.txt", ios_base::app);
        for (int i = 0; i < sz - 1; i++)
        {
            for (int j = i + 1; j < sz; j++)
            {
              arr[i][j] = 0;               
            }
        }
        for (int i = 0; i < sz; i++) {
            for (int j = 0; j < sz; j++)
            {
                cout << "  " << arr[i][j];
                out << arr[i][j] << ",";
            }
            cout << endl;
            out << endl;
        }
        out << "---End of reseted matirx---" << endl;
    };

};
Reset_above_main::Reset_above_main(int size, int arrsimb[100][100])
{
    sz = size;
    for (int i = 0; i < sz; i++)
    {
        for (int j = 0; j < sz; j++)
        {
            arr[i][j] = arrsimb[i][j];
        }
    }
}

class Reset_under_main : public operation
{
public:
    Reset_under_main(int size, int arrsimb[100][100]);
    void Reset()
    {
        ofstream out("logs.txt", ios_base::app);
        for (int i = 0; i < sz; i++) {
            for (int j = 0; j < i; j++)
            {
                arr[i][j] = 0;
            }

        }
        for (int i = 0; i < sz; i++) {
            for (int j = 0; j < sz; j++)
            {
                cout << "  " << arr[i][j];
                out << arr[i][j] << ",";
            }
            cout << endl;
            out << endl;
        }
        out << "---End of reseted matirx---" << endl;
    };

};
Reset_under_main::Reset_under_main(int size, int arrsimb[100][100])
{
    sz = size;
    for (int i = 0; i < sz; i++)
    {
        for (int j = 0; j < sz; j++)
        {
            arr[i][j] = arrsimb[i][j];
        }
    }
}

class Reset_above_side : public operation
{
public:
    Reset_above_side(int size, int arrsimb[100][100]);
    void Reset()
    {
        ofstream out("logs.txt", ios_base::app);
        for (int i = 0; i < sz; i++)
        { 
            for (int j = 0; j < sz; j++)
            {
                if (i < sz - j - 1) 
                {
                    arr[i][j] = 0;
                }
            }
        }
        for (int i = 0; i < sz; i++) {
            for (int j = 0; j < sz; j++)
            {
                cout << "  " << arr[i][j];
                out << arr[i][j] << ",";
            }
            cout << endl;
            out << endl;
        }
        out << "---End of reseted matirx---" << endl;
    };

};
Reset_above_side::Reset_above_side(int size, int arrsimb[100][100])
{
    sz = size;
    for (int i = 0; i < sz; i++)
    {
        for (int j = 0; j < sz; j++)
        {
            arr[i][j] = arrsimb[i][j];
        }
    }
}

class Reset_under_side : public operation
{
public:
    Reset_under_side(int size, int arrsimb[100][100]);
    void Reset()
    {
        ofstream out("logs.txt", ios_base::app);
        for (int i = 0; i < sz; i++) 
        {
            for (int j = sz - i; j < sz; j++)
            {
                arr[i][j] = 0;
            }
        }
        for (int i = 0; i < sz; i++) {
            for (int j = 0; j < sz; j++)
            {
                cout << "  " << arr[i][j];
                out << arr[i][j] << ",";
            }
            cout << endl;
            out << endl;
        }
        out << "---End of reseted matirx---" << endl;
    };

};
Reset_under_side::Reset_under_side(int size, int arrsimb[100][100])
{
    sz = size;
    for (int i = 0; i < sz; i++)
    {
        for (int j = 0; j < sz; j++)
        {
            arr[i][j] = arrsimb[i][j];
        }
    }
}

void main()
{    
        string path;
        string key;
        cout << "Enter path to file: " << endl;
        cin >> path;
        operation Matrix(path);
        bool ext;
        do
        {
            
            key = Matrix.Read();
            ext = Matrix.ReturnExt();
            if (key == "amd")
            {
                Reset_above_main L1(Matrix.sz, Matrix.arr);
                L1.Reset();
            }
            else if (key == "umd")
            {
               Reset_under_main L2(Matrix.sz, Matrix.arr);
               L2.Reset();
            }
            else if (key == "asd")
            {
                Reset_above_side L3(Matrix.sz,Matrix.arr);
                L3.Reset();
            }
            else if (key == "usd")
            {
                Reset_under_side L4(Matrix.sz,Matrix.arr);
                L4.Reset();
            }
            else
            {
                cout << "No matrix left" << endl;
            }

        } while (ext);

    cout << "End of file" << endl;
}