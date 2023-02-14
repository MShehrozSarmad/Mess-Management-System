#include <iostream>
#include <string>
#include <conio.h>
#include <limits>
#include <fstream>
#include "styling.h"
#include <nlohmann/json.hpp>
using json = nlohmann::ordered_json;
using namespace std;

string menu1[] = {
    "Unlock your choice below :) \n",
    "1. Construct Menu",
    "2. Set Pricing Rates",
    "3. Set up Meal Shedule",
    "4. Track Meal Attendance",
    "5. Generate Total Bill Sheet",
    "6. Mark Fee Status of Paid Bills",
    "7. Add or Remove a Mess Attendee",};

string menu0[] = {
    "Unlock your choice below :) \n",
    "1. Consult the Menu",
    "2. Pricing  Shedule",
    "3. Food Service Hours",
    "4. Monitor Attendance",
    "5. Generate Total Bill"};

string menu[] = {
    "Continue as? \n",
    "1. Mess Attendee",
    "2. Mess Admin"};

// string *jagged[] = {menu, menu1};

void checkMonthlyAttendance(const string &jsonFile)
{
    nlohmann::ordered_json jsonData;
    ifstream jsonInput(jsonFile);
    jsonInput >> jsonData;
    string currentMonth = getCurrentMonth(); // function to get current month
    for (auto &user : jsonData["users"])
    {
        auto &attendance = user["attendance"];
        string lastMonth = attendance.rbegin().key(); // get the name of the last object in the "attendance" array
        if (lastMonth != currentMonth)
        {
            nlohmann::ordered_json template1 = {{"fee_status", ""}, {"meal1", json::array()}, {"meal2", json::array()}, {"meal3", json::array()}, {"meal4", json::array()}, {"meal5", json::array()}, {"meal6", json::array()}, {"meal7", json::array()}, {"meal8", json::array()}, {"meal9", json::array()}, {"meal10", json::array()}, {"meal11", json::array()}, {"meal12", json::array()}, {"meal13", json::array()}, {"meal14", json::array()}};
            attendance[currentMonth] = template1; // copy the template of objects or arrays from the previous month
        }
    }
    ofstream jsonOutput(jsonFile);
    jsonOutput << jsonData.dump(4);
    jsonInput.close();
    jsonOutput.close();
}

struct users
{
    string name, student_id, hostel, room_number, mess_number;
    users *next;
};

users *head = NULL;

struct attdNode
{
    string messNo;
    string mealNo;
    attdNode *next;
};

attdNode *heaad = NULL;

void addAttd()
{
    string tempMeal;
    cout << "enter meal no: ";
    getline(cin, tempMeal);
    while (true)
    {
        attdNode *newAttd = new attdNode;
        cout << "enter mess no: ";
        getline(cin, newAttd->messNo);
        newAttd->next = heaad;
        heaad = newAttd;
        if (getch() == 27)
        {
            attdNode *temp1 = new attdNode;
            temp1->mealNo = tempMeal;
            temp1->next = heaad;
            heaad = temp1;
            cout << "Exiting...";
            break;
        }
    }
}



// bbl on
// in ..
// mrg onlgn
// q ..
// sel on`2
// void updateAttendance(string filepath, attdNode *head)
// {
//     ifstream file(filepath);
//     json data;
//     file >> data;

//     json users = data["users"];
//     vector<string> mess_numbers;
//     attdNode *temp = head->next;
//     while (temp != NULL)
//     {
//         mess_numbers.push_back(temp->messNo);
//         temp = temp->next;
//     }

//     for (json::iterator it = users.begin(); it != users.end(); ++it)
//     {
//         json user = *it;
//         string mess_number = user["mess_number"];
//         if (find(mess_numbers.begin(), mess_numbers.end(), mess_number) != mess_numbers.end())
//         {
//             json attendance1 = user["attendance"]["January"];
//             attendance1[head->mealNo].push_back(true);
//             cout << "added successsfully\n";
//         }
//     }
// }

void setMessTimings(const string &file_location)
{
    ifstream i(file_location);
    json data;
    i >> data;

    string meal, start_time, end_time;
    cout << "Enter meal: ";
    getline(cin, meal);
    cout << "Enter start time: ";
    getline(cin, start_time);
    cout << "Enter end time: ";
    getline(cin, end_time);

    data["mess_data"]["mess_timings"][meal]["start_time"] = start_time;
    data["mess_data"]["mess_timings"][meal]["end_time"] = end_time;

    ofstream o(file_location);
    o << data.dump(4);
    o.close();
    i.close();
}

void updateAttendance()
{
    nlohmann::ordered_json jsonData;
    ifstream jsonFile("data.json");
    jsonFile >> jsonData;

    json users = jsonData["users"];
    string mealNo = heaad->mealNo;

    attdNode *temp1 = heaad;
    attdNode *temp = temp1->next;

    while (temp != NULL)
    {
        for (int i = 0; i < users.size(); ++i)
        {
            json user = users[i];
            string user_mess_number = user["mess_number"];
            if (user_mess_number == temp->messNo)
            {
                user["attendance"]["January"][heaad->mealNo].push_back({true});
                break;
            }
        }
        temp = temp->next;
    }
    ofstream outFile("data.json");
    outFile << jsonData.dump(4);
    jsonFile.close();
}

void updateDataToJson(users *head)
{
    nlohmann::ordered_json jsonData;
    ifstream jsonFile("data.json");
    jsonFile >> jsonData;
    users *temp = head;
    while (temp != NULL)
    {
        nlohmann::ordered_json userData;
        userData["name"] = temp->name;
        userData["student_id"] = temp->student_id;
        userData["hostel"] = temp->hostel;
        userData["room_number"] = temp->room_number;
        userData["mess_number"] = temp->mess_number;
        userData["attendance"] = {{"January", {{"fee_status", ""}, {"meal1", json::array()}, {"meal2", json::array()}, {"meal3", json::array()}, {"meal4", json::array()}, {"meal5", json::array()}, {"meal6", json::array()}, {"meal7", json::array()}, {"meal8", json::array()}, {"meal9", json::array()}, {"meal10", json::array()}, {"meal11", json::array()}, {"meal12", json::array()}, {"meal13", json::array()}, {"meal14", json::array()}}}};
        jsonData["users"].push_back(userData);

        temp = temp->next;
    }
    ofstream outFile("data.json");
    outFile << jsonData.dump(4);
    jsonFile.close();
}

void addUser()
{
    while (true)
    {
        users *newUser = new users;
        cout << "Enter Name: ";
        getline(cin, newUser->name);
        cout << "Enter Student id: ";
        getline(cin, newUser->student_id);
        cout << "Enter Hostel: ";
        getline(cin, newUser->hostel);
        cout << "Enter Room Number: ";
        getline(cin, newUser->room_number);
        cout << "Enter Mess Number: ";
        getline(cin, newUser->mess_number);
        newUser->next = NULL;
        if (head == NULL)
        {
            head = newUser;
        }
        else
        {
            users *temp = head;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = newUser;
        }
        if (getch() == 27)
        {
            updateDataToJson(head);
            checkMonthlyAttendance("./data.json");
            cout << "Exiting...";
            break;
        }
    }
    spaces(2);
}

void safeGetline(istream &is, string &s)
{
    is.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(is, s);
}

string admin_name, admin_password;
void getAdminCredentials(string fileName)
{
    json data;
    try
    {
        ifstream i(fileName);
        i >> data;
    }
    catch (json::parse_error &e)
    {
        cerr << "Error reading file: " << e.what() << endl;
        return;
    }
    try
    {
        admin_name = data["admin"]["name"];
        admin_password = data["admin"]["pswrd"];
    }
    catch (json::exception &e)
    {
        cerr << "Error: " << e.what() << endl;
        return;
    }
}


void printMealsData(const string &filePath)
{
    json root;
    ifstream file(filePath);
    if (!file.good())
    {
        cout << "Error opening file " << filePath << endl;
        return;
    }
    file >> root;
    json meals = root["mess_data"]["meals"];
    
    vector<string> lines; // create a vector to store each line of the table
    stringstream s2;
    s2 << left << setw(15) << "Days" << setw(15) << "Meals" << setw(30) << "Menu";
    string headers = s2.str();
    cout<<setw(setwVal(headers))<<headers<<endl<<endl;
    for (auto day = meals.begin(); day != meals.end(); ++day)
    {
        bool isFirstMeal = true; // variable to check if it's the first meal of the day
        for (auto meal = day.value().begin(); meal != day.value().end(); ++meal)
        {
            for (auto item : meal.value())
            {
                stringstream ss;
                if (isFirstMeal)
                { // if it's the first meal of the day, print the day name
                    ss << left << setw(15) << day.key();
                    isFirstMeal = false;
                }
                else
                {
                    ss << left << setw(15) << " "; // if it's not the first meal, leave the day name empty
                }
                if (item.is_string())
                {
                    ss << setw(15) << meal.key() << setw(30) << item.get<string>();
                }
                else
                {
                    ss << setw(15) << meal.key() << setw(30) << item;
                }
                lines.push_back(ss.str());
            }
        }
    }
    for(auto line : lines){ // print all the lines
        cout<< setw(setwVal(line)) << line<<endl;
    }
}





void setBrunchDinner(const string &file_location)
{
    ifstream i(file_location);
    json data;
    i >> data;

    string day, brunch, dinner;
    cout << "Enter day: ";
    cin >> day;
    cout << "Enter brunch: ";
    cin >> brunch;
    cout << "Enter dinner: ";
    cin >> dinner;

    data["mess_data"]["meals"][day]["brunch"] = {brunch};
    data["mess_data"]["meals"][day]["dinner"] = {dinner};

    ofstream o(file_location);
    o << data.dump(4);
    o.close();
    i.close();
}



void print_mess_timings(const string &file_path)
{
    ifstream data_file(file_path);
    json data;
    data_file >> data;
    string x = "Mess Timings";
    cout  << setw(setwVal(x))<< x << endl <<endl;
    stringstream ss, ss1;
    ss << "Brunch: " << data["mess_data"]["mess_timings"]["brunch"]["start_time"] << setw(10) << data["mess_data"]["mess_timings"]["brunch"]["end_time"] << endl;
    x = ss.str();
    cout<< setw(setwVal(x))<<x;
    ss1 << "Dinner: " << data["mess_data"]["mess_timings"]["dinner"]["start_time"] << setw(10) << data["mess_data"]["mess_timings"]["dinner"]["end_time"] << endl;
    x = ss1.str();
    cout<< setw(setwVal(x))<<x;
}




void print_pricing_table(string file_path)
{
    ifstream file(file_path);
    json data;
    file >> data;
    json price = data["mess_data"]["price"];
    cout << "Meal No\tPrice" << endl;
    for (json::iterator it = price.begin(); it != price.end(); ++it)
    {
        cout << it.key() << "\t" << it.value()  << " PKR" << endl;
    }
}


template <typename T, size_t N>
void render(T (&arr)[N])
{
    for (int i = 0; i < N; i++)
    {
        cout << setw(setwVal1(arr[i])) << arr[i] << endl;
    }
    cout << endl;
}

void form(bool x);

string choice = "0",
       choice0 = "0",
       choice1 = "0";

void user()
{
    system("cls");
    heading();
    render(menu0);
    safeGetline(cin, choice0);
    if (choice0 == "1")
    {
        spaces(2);
        printMealsData("data.json");
        spaces(2);
        cout << "\n enter c to continue: ";
        char ch;
        cin >> ch;
        if (ch = 'c')
        {
            user();
        }
        else
        {
            exit(0);
        }
    }
    else if (choice0 == "3")
    {
        print_mess_timings("data.json");
        spaces(2);
        cout << "\n enter c to continue: ";
        char ch;
        cin >> ch;
        if (ch = 'c')
        {
            user();
        }
        else
        {
            exit(0);
        }
    }
    else if (choice0 == "2")
    {
        print_pricing_table("data.json");
        spaces(2);
        cout << "\n enter c to continue: ";
        char ch;
        cin >> ch;
        if (ch = 'c')
        {
            user();
        }
        else
        {
            exit(0);
        }
    }
}

void displayAttd()
{
    attdNode *temp1 = heaad;
    cout << "Attendance marked for meal no: " << heaad->mealNo << endl;
    attdNode *temp = temp1->next;
    cout << "And Attendees are: \n";
    while (temp != NULL)
    {
        cout << temp->messNo << " " << temp->mealNo << endl;
        temp = temp->next;
    }
}

void setMealPrices(const string &filepath)
{
    ifstream jsonFile(filepath);
    json data;
    jsonFile >> data;

    for (int i = 1; i <= 14; ++i)
    {
        string meal = "meal" + to_string(i);
        double price;
        cout << "Enter price for " << meal << ": ";
        cin >> price;
        data["mess_data"]["price"][meal] = price;
    }

    ofstream jsonOut(filepath);
    jsonOut << data;
}

void admin()
{
    system("cls");
    heading();
    render(menu1);
    safeGetline(cin, choice1);
    if (choice1 == "7")
    {
        spaces(2);
        string adusr = "Add Users";
        cout << setw(setwVal(adusr)) << colorize(adusr, "32") << endl;
        spaces(2);
        addUser();
        cout << colorize("Added Successfully!", "32") << "\n enter c to continue: ";
        char ch;
        cin >> ch;
        if (ch = 'c')
        {
            admin();
        }
        else
        {
            exit(0);
        }
    }
    else if (choice1 == "4")
    {
        addAttd();
        updateAttendance();
        displayAttd();
        cout << "\n enter c to continue: ";
        char ch;
        cin >> ch;
        if (ch = 'c')
        {
            admin();
        }
        else
        {
            exit(0);
        }
    }
    else if (choice1 == "2")
    {
        setMealPrices("data.json");
        cout << "\n enter c to continue: ";
        char ch;
        cin >> ch;
        if (ch = 'c')
        {
            admin();
        }
        else
        {
            exit(0);
        }
    }
    else if (choice1 == "1")
    {
        setBrunchDinner("data.json");
        cout << "\n enter c to continue: ";
        char ch;
        cin >> ch;
        if (ch = 'c')
        {
            admin();
        }
        else
        {
            exit(0);
        }
    }
    else if (choice1 == "3")
    {
        setMessTimings("data.json");
        cout << "\n enter c to continue: ";
        char ch;
        cin >> ch;
        if (ch = 'c')
        {
            admin();
        }
        else
        {
            exit(0);
        }
    }
}

void wrongCrdt(bool y)
{
    string err = "Wrong Credentials, Try Again!";
    cout << setw(setwVal(err)) << colorize(err, "31") << endl;
    form(y);
}

void form(bool x)
{

    if (x)
    {
        string name, pswrd;
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Passcode: ";
        cin >> pswrd;
        getAdminCredentials("data.json");
        if (name == admin_name && pswrd == admin_password)
        {
            admin();
        }
        else
        {
            wrongCrdt(x);
        }
    }
    else if (!x)
    {
        string name, pswrd;
        cout << "Registration Number: ";
        cin >> name;
        cout << "Enter Mess Passcode: ";
        cin >> pswrd;
        if (name == "student" && pswrd == "studentPasscode")
        {
            user();
        }
        else
        {
            wrongCrdt(x);
        }
    }
}

bool menuFlag = false, menuFlag0 = false, menuFlag1 = false;
void userMenu()
{
    string sgn = "Sign In\n";
    cout << setw(setwVal(menu1[5])) << colorize(sgn, "32");
    render(menu);
    getline(cin, choice);
    if (choice == "1")
    {
        menuFlag = false;
        form(menuFlag);
    }
    else if (choice == "2")
    {
        menuFlag = true;
        form(menuFlag);
    }
    else
    {
        system("cls");
        heading();
        string err = "Invalit choice, Try Again!";
        cout << setw(setwVal(err)) << colorize(err, "31") << endl;
        userMenu();
    }
}


int main()
{
    // to open in maximized window
    maxWin();
    //  disable restore down button
    disRestoreDown();
    // to disable scrollbar
    ShowScrollBar(GetConsoleWindow(), SB_VERT, 0);
    // setting console title
    system("title Mess Management System");
    checkMonthlyAttendance("./data.json");
    // heading
    heading();
    // login
    userMenu();
}