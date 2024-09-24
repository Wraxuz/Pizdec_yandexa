// Напишите код упрощенного текстового редактора здесь#include <iostream>
#include <string>
#include <deque>
#include <algorithm>
#include <iterator>
#include <list>
#include <iostream>

using namespace std;

class Editor {
public:
    Editor() : cursor(0), it(text.end()) {}
    
    void Left() {
        if (cursor > 0){
            --it;
            --cursor;
        }
        //cout << *it << endl;
    }

    void Right() {
        //cout << cursor << " " << *it << endl;
        if (cursor < text.size()){
            ++it;
            ++cursor;
        }
        //cout << *it << " "s << cursor << endl;
    }

    void Insert(char token) {
        if (cursor == text.size()){
            //cout << token << endl;
            text.push_back(token);
            it = text.end();
        }
        else{
            text.insert(it--, token);
        }
        ++cursor;
        //cout << cursor << endl;
        
    }

    void Cut(size_t tokens = 1) {
        list<char>::iterator ne = it;
        buffer.clear();
        if (cursor + tokens < text.size()){
            size_t i = 0;
            while (i < tokens){
                ++ne;
                i += 1;
            }
        }
        else{
            ne = text.end();
        }
        buffer.insert(buffer.begin(), it, ne);
        text.erase(it, ne);
        it = ne;
    }

    void Copy(size_t tokens = 1) {
        list<char>::iterator ne = it;
        buffer.clear();
        if (cursor + tokens < text.size()){
            size_t i = 0;
            while (i < tokens){
                ++ne;
                ++cursor;
                i += 1;
            }
        }
        else{
            ne = text.end();
            cursor = text.size();
        }
        buffer.insert(buffer.begin(), it, ne);
    }

    void Paste() {
        if (!buffer.empty()) {
            //cout << 1 << endl;
            /*if (it == text.end()){
                text.push_back(' ');
            }
            else{
                text.insert(it, ' ');

            }*/
            //it++;
            text.insert(it, buffer.begin(), buffer.end());
            cursor += buffer.size();
            //size_t i = 0;
            //while (i < buffer.size()){
                //++it;
                //++i;
            //}
        }
    }

    string GetText() const {
        string ans = ""s;
        for (auto i : text){
            ans += i;
        }
        //cout << cursor << endl;
        //cout << *it << endl;
        
        return ans;
    }

private:
    list<char> text = {};
    deque<char> buffer;
    size_t cursor;
    list<char>::iterator it;
};

int main() {
    Editor editor;
    const string text = "hello, world"s;
    for (char c : text) {
        editor.Insert(c);
    }
    //cout << editor.GetText() << endl;
    // Текущее состояние редактора: `hello, world|`
    for (size_t i = 0; i < text.size() + 1; ++i) {
        editor.Left();
    }
    // Текущее состояние редактора: `|hello, world`
    //cout << editor.GetText() << endl;
    editor.Cut(7);
    cout << editor.GetText() << endl;
    // Текущее состояние редактора: `|world`
    // в буфере обмена находится текст `hello, `
    for (size_t i = 0; i < 5; ++i) {
        editor.Right();
    }
    
    // Текущее состояние редактора: `world|`
    //cout << editor.GetText() << endl;
    editor.Insert(',');
    cout << editor.GetText() << endl;
    editor.Insert(' ');
    cout<< editor.GetText() << endl;

    // Текущее состояние редактора: `world, |`
    editor.Paste();
    //cout << editor.GetText() << endl;
    // Текущее состояние редактора: `world, hello, |`
    editor.Left();
    editor.Left();
    //Текущее состояние редактора: `world, hello|, `
    editor.Cut(3);  // Будут вырезаны 2 символа
    // Текущее состояние редактора: `world, hello|`
    cout << editor.GetText();
    return 0;
}
