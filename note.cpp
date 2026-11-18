#include <iostream>
#include "note.h"
#include <stdexcept>
#include <fstream>
#include <memory>
#include <utility>
using namespace std;

Note::Note(): route(nullptr), count(0) {
    cout<<"Вызван конструктор Note\n";
}

Note::Note(Route** r, int c): route(nullptr), count(0) {
    if (c<0 || (c>0 && r==nullptr)) {
        throw invalid_argument("Ошибка: некорректные параметры конструктора Note\n");
    }
    try {
        for (int i=0; i<c; i++) {
            if (r[i]==nullptr) {
                throw invalid_argument("Ошибка: пустой указатель на маршрут!\n");
            }
            unique_ptr<Route>item(new Route(*r[i]));
            add(item.get(), count);
            item.release();
        }
    }
    catch (...) {
        for (int i=0; i<count; i++) {
            delete route[i];
        }
        delete[] route;
        throw;
    }
    cout<<"Вызван конструктор Note с параметрами\n";
}

Note::Note(const Note& other): route(nullptr), count(0)  {
    try {
        for (int i=0; i<other.count; i++) {
            unique_ptr<Route>item(new Route(*other.route[i]));

            add(item.get(), count);
            item.release();
        }
    }
    catch(...) {
        for (int i=0; i<count; i++) {
            delete route[i];
        }
        delete[] route;
        throw;
    }
    cout<<"Вызван конструктор копирования Note\n";
}


Note::~Note() {
    for (int i=0; i<count; i++) {
        delete route[i];
    }
    delete[] route;
    cout<<"Вызван деструктор Note\n";
}

// добавление
void Note::add(Route* item, int index) {
    if (index<0 || index>count) {
        throw out_of_range("Ошибка: неверная позиция маршрута!\n");
    }
    if (item==nullptr) {
        throw invalid_argument("Ошибка: нельзя добавить пустой маршрут!\n");
    }

    for (int i=0; i<count; i++) {
        if (route[i]==item) {
            throw invalid_argument("Ошибка: маршрут уже находится в списке!\n");
        }
    }

    Route** newRoute=new Route*[count+1];
    for (int i=0; i<index; i++) {
        newRoute[i]=route[i];
    }
    newRoute[index]=item;
    for (int i=index; i<count; i++) {
        newRoute[i+1]=route[i];
    }
    delete[] route;
    route=newRoute;
    count+=1;
    sort();
    cout<<"Новый маршрут успешно добавлен!\n";

}

// удаление
void Note::remove(int index) {
    if (count==0) {
        throw runtime_error("Ошибка: маршрутов в списке нет!\n");
    }
    if (index<0 || index>=count) {
        throw out_of_range("Ошибка: неверная позиция маршрута!\n");
    }

    // создание нового массива на -1 размером
    Route** newRoute=nullptr;
    if (count>1) {
        newRoute=new Route*[count-1];
        int newIndex=0;
        for (int i=0; i<count; i++) {
            if (i==index) continue;
            newRoute[newIndex]=route[i];
            newIndex++;
        }
    }
    delete route[index];
    delete[] route;
    route=newRoute;
    count-=1;
    cout<<"Маршрут успешно удален из списка!\n";
}

// промотр всех
void Note::showAll() const{
    if (count==0) {
        throw runtime_error("Ошибка: маршрутов в списке нет!\n");
    }
    cout<<"\nСписок маршрутов\n";
    for (int i=0; i<count; i++) {
        cout<<"Маршрут "<<(i+1)<<endl;
        cout<<*route[i];
    }
    cout<<endl;
}


// редактирование 
void Note::edit(int index){
    if (count==0) {
        throw runtime_error("Ошибка: маршрутов в списке нет!\n");
    }
    if (index<0 || index>=count) {
        throw out_of_range("Ошибка: неверная позиция маршрута!\n");
    }
    string newPoint_a, newPoint_b;
    int newNumber;

    cout<<"Введите новый начальный пункт: ";
    if (!getline(cin>>ws, newPoint_a)) {
        throw runtime_error("Ошибка: ошибка при вводе начального пункта!\n");
    }

    cout<<"Введите новый конечный пункт: ";
     if (!getline(cin>>ws, newPoint_b)) {
        throw runtime_error("Ошибка: ошибка при вводе конечного пункта!\n");
    }
    if (newPoint_a.empty() || newPoint_b.empty()) {
        throw runtime_error("Ошибка: пункты маршрута не должны быть пустыми!\n");
    }

    cout<<"Введите новый номер маршрута: ";
     if (!(cin>>newNumber) || newNumber<=0) {
        throw runtime_error("Ошибка: ошибка при вводе номера маршрута!\n");
    }

    route[index]->setPoint_a(newPoint_a);
    route[index]->setPoint_b(newPoint_b);
    route[index]->setNumber(newNumber);

    sort();

    cout<<"Маршрут успешно отредактирован!\n";

}

// сортировка 
void Note::sort() {
    for (int i=0; i<count-1; i++) {
        int flagSort=0;
        for (int j=0; j<count-1-i; j++) {
            if (route[j]->getNumber()>route[j+1]->getNumber()) {
                Route* temp=route[j];
                route[j]=route[j+1];
                route[j+1]=temp;
                flagSort=1;
            }
        }
        if (!flagSort) {
            break;
        }
    }
}

// поиск
void Note::find(int num) {
    int flagFind=0;
    for (int i=0; i<count; i++) {
        if (route[i]->getNumber()==num) {
            cout<<*route[i];
            flagFind=1;
        }
    }
    if (!flagFind) {
        throw runtime_error("Ошибка: маршрута с таким номером в списке нет!\n");
    }
    
}

// сохранение в файл 
void Note::saveToFile(const std::string& file) const {
    ofstream out(file);
    if (!out.is_open()) {
        throw runtime_error("Ошибка: не удалось открыть файл для сохранения!\n");
    }
    out<<count<<endl;
    for (int i=0; i<count; i++) {
        out<<route[i]->getPoint_a()<<endl;
        out<<route[i]->getPoint_b()<<endl;
        out<<route[i]->getNumber()<<endl;
    }
    if (!out) {
        throw runtime_error("Ошибка: ошибка при записи данных в файл!\n");
    }
    out.close();
    cout<<"Маршрут успешно сохранен в файл!\n";

}

// загрузка из файла
void Note::loadToFile(const std::string& file) {
    ifstream in(file);
    if (!in.is_open()) {
        throw runtime_error("Ошибка: не удалось открыть файл для загрузки!\n");
    }
    int size;
    if (!(in>>size)) {
        throw runtime_error("Ошибка: не удалось прочитать количество маршрутов!\n");
    }

    Note temp;
    for (int i=0; i<size; i++) {
        unique_ptr<Route>item(new Route());

        if (!(in>>*item)) {
            throw runtime_error("Ошибка: некорректные данные в файле!\n");
        }
        if (item->getNumber()<=0 || item->getPoint_a().empty() || item->getPoint_b().empty()) {
            throw invalid_argument("Ошибка: некорректные поля маршрута в файле!\n");
        }

        temp.add(item.get(), temp.count);
        item.release();
    }

    in>>ws;

    swap(route, temp.route);
    swap(count, temp.count);

    cout<<"Маршруты успешно загружены из файла!\n";
}

// оператор =
Note& Note::operator=(const Note& other) {
    if (this==&other) {
        return *this;
    }
    Note temp(other);
    swap(route, temp.route);
    swap(count, temp.count);
    return *this;
}