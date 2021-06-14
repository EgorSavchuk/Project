#include<iostream>
#include<sstream>
#include<istream>
#include<fstream>
#include<string>
#include<set>
#include<vector>
#include<map>
#include <iomanip>
#include <algorithm>


using namespace std;

class Date {
public:
    Date(int new_year, int new_month, int new_day) {
        year = new_year;
        if (new_month > 12 || new_month < 1) {
            throw logic_error("Month value is invalid: " + to_string(new_month));
        }
        month = new_month;
        if (new_day > 31 || new_day < 1) {
            throw logic_error("Day value is invalid: " + to_string(new_day));
        }
        day = new_day;
    }

    int GetYear() const {
        return year;
    }
    int GetMonth() const {
        return month;
    }
    int GetDay() const {
        return day;
    }

private:
    int year;
    int month;
    int day;
};


class product {
public:
    product () {
        name = "empty";
        fat = 0;
        carbs = 0;
        prot = 0;
        cal = 0;
    }
    product (string temp_name, double temp_fat, double temp_carbs, double temp_prot, double temp_cal) {
        name = temp_name;
        fat = temp_fat;
        carbs = temp_carbs;
        prot = temp_prot;
        cal = temp_cal;
    }
    string GetName() const {
        return name;
    }

private:
    string name;
    double fat;
    double carbs;
    double prot;
    double cal;
};

bool operator<(const product& a, const product& b) {
    if (a.GetName() < b.GetName()) {
        return true;
    }
    else {
        return false;
    }
}


struct one_meal {
    set<product> meal;
};


struct day_food {
    one_meal Breakfast;
    one_meal Lunch;
    one_meal Dinner;
    one_meal Other;
};

bool operator<(const Date& a, const Date& b) {
    if (a.GetYear() < b.GetYear()) return true;
    else if (a.GetYear() > b.GetYear()) return false;
    else {
        if (a.GetMonth() < b.GetMonth()) return true;
        else if (a.GetMonth() > b.GetMonth()) return false;
        else {
            if (a.GetDay() < b.GetDay()) return true;
            else {
                return false;
            }
        }
    }
}

struct all_food {
    map<Date, day_food> foods;
};

product search(string search_name) {
    ifstream products_list("products_list.txt");
    string temp_name;
    double temp_fat, temp_carbs, temp_prot, temp_cal;
    if (products_list)
    {
        while (!products_list.eof())
        {
            products_list >> temp_name >> temp_fat >> temp_carbs >> temp_prot >> temp_cal;
            if (search_name == temp_name) {
                products_list.close();
                return product(temp_name, temp_fat, temp_carbs, temp_prot, temp_cal);
            }
        }
        products_list.close();
        cout << "No such product found";
        return product();
    }
}

int main() {
    string a = "chicken";
    product b = search(a);
    cout << b.GetName(); // то что в мэин это так, чисто проверял как робит, но большую часть от сюда я уже убрал.
}
