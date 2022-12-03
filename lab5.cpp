#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class classPath
{
private:
    string path;

public:
    

    classPath(string strPath) : path(strPath) { /*...*/ }

    string catalog_or_path() const;
    string return_file_name() const;
    bool correct_path() const;

    friend ostream& operator<<(ostream& os, const classPath& str);
    
    classPath operator+(const classPath&) const;
    classPath operator+=(const classPath&);
   
    classPath operator=(const classPath&);
    string operator[] (unsigned int index) const;

    bool operator==(const classPath&) const;
    bool operator==(const string&) const;
    
};

bool classPath::correct_path() const
{
    bool correct = true;
    bool file = false;
    bool absolute = false;

    // проверка на абсолютность пути
    if ((path.size() > 2) & (path[0] >= 'A') & ('Z' >= path[0]) & (path[1] == ':')) { 
        absolute = true;
    }

    unsigned int i; 
    if (absolute) { i = 2; }
    else { i = 0; }

    while (path.size() > i) {
        char ch = path[i];

        // Проверка на допустимые символы (парсинг 2000лвл)
        if (((ch >= 'A') & (ch <= 'Z')) |
            ((ch >= 'a') & (ch <= 'z')) |
            ((ch >= '.') & (ch <= '9')) |
            ((ch >= '#') & (ch <= '%')) |
            ((ch >= '\'') & (ch <= ')')) |

            (ch == '{') | (ch == '}') |
            (ch == '~') | (ch == '@') |
            (ch == '^') | (ch == '-') |
            (ch == '_') | (ch == '`'))

        {

            //проверка на название файла
            if (path[i] == '.') { file = true; }

            // Проверка на корректность окончания пути файла
            if ((path.size() - 1 == i) & (file) & (path[i] != '.'))
            {
                correct = false;
                break;
            }

            // Проверка на корректность окончания пути каталога
            if ((path.size() - 1 == i) & (!file) & (path[i] != '/'))
            {
                correct = false;
                break;
            }

            
        }
        else { correct = false; break; }
    }

    return correct;
}

string classPath::catalog_or_path() const {

    

  if (find(path.begin(), path.end(), '.') != path.end()) {

    return string("filepath");
          
  }
    
  else {

    return string("catalogpath");
  }
    

   
}

string classPath::return_file_name() const
{
    

  if (find(path.begin(), path.end(), '.') == path.end()) {

    return string("catalogpath");
  }
  else {
    return string(find(path.rbegin(), path.rend(), '/').base(), path.end());
  }
    

    
}

classPath classPath::operator+(const classPath& obj) const {

   

    

 if ((obj.path[1]) != ':') {

    if (find(path.rbegin(), path.rend(), '/') == path.rbegin()) {

      string str;
      str = string(path.begin(), path.end() - 1) + obj.path;
      return str;
    }
    else return classPath(string("non_convertional"));

 }     
  else return classPath(string("non_convertional"));

}

classPath classPath::operator+=(const classPath& obj)
{
   



  if ((obj.path[1]) != ':')
  {
    if (find(path.rbegin(), path.rend(), '/') == path.rbegin())
    {
      this->path = string(path.begin(), path.end() - 1);
      path += obj.path;
      return *this;
    }
    else return classPath(string("non_convertional"));
  }
  else return classPath(string("non_convertional"));
  
}

ostream& operator<<(ostream& os, const classPath& str) 
{
    os << str.path;
    return os;
}


classPath classPath::operator=(const classPath& str) 
{
    path = str.path;
    return *this;
}

string classPath::operator[] (unsigned int index) const {
    auto iter_left = path.begin();
    unsigned int k = 1;

    while ((k++ != index) & (iter_left != path.end())) {
        iter_left = find(iter_left, path.end(), '/');
        iter_left++;
       }
    return string(iter_left, find(iter_left, path.end(), '/'));
}

bool classPath::operator==(const classPath& obj) const
{
    return (this->path == obj.path);
}

bool classPath::operator==(const string& newStr) const
{
    return (this->path == newStr);
}



int main() {

    setlocale(LC_ALL, "Russian");

    classPath test1("D:/abc/");
    classPath test2("D:/abc/ustala.exe");
    classPath test3("/tyazhko/");
    classPath test4("/abc/ustala.exe");

    cout<< test1.correct_path()<< endl;


    cout << "Путь до каталога или до файла? \t" << test1.catalog_or_path() << endl;
    cout << "Имя файла: \t" << test1.return_file_name() << endl << endl;
    cout << "Путь до каталога или до файла? \t" << test2.catalog_or_path() << endl;
    cout << "Имя файла: \t" << test2.return_file_name() << endl << endl;
    cout << "Путь до каталога или до файла? \t" << test3.catalog_or_path() << endl;
    cout << "Имя файла: \t" << test3.return_file_name() << endl << endl;
    cout << "Путь до каталога или до файла? \t" << test4.catalog_or_path() << endl;
    cout << "Имя файла: \t" << test4.return_file_name() << endl << endl;

    classPath testLeft("C:/Desktop/");
    cout << "Строка 1: " << testLeft << endl;
    classPath testRight("/labs/Adobe_PS.exe"); 
    cout << "Строка 2: " << testRight << endl;

    classPath newPath = testLeft + testRight;
    cout << "Новая строка 1: " << newPath << endl;

    testLeft += testRight;
    cout << "Новая строка 2: " << testLeft << endl << endl;

    test1 = test2;
    cout << "\nПрисвоим объекту значение другого объекта: "<< test1<<endl<<endl;

    if (test1 == test2) { cout << "Строки равны" << endl; }
    else { cout << "Строки не равны" << endl; }

    if (test3 == test4) { cout << "Строки равны" << endl; }
    else { cout << "Строки не равны" << endl; }

    string anystr;
    cout << "Введите любую строку: ";
    getline(cin, anystr);

    if (test3 == anystr) { cout << "Строки равны" << endl; }
    else { cout << "Строки не равны" << endl; }

    
    return 0;

}