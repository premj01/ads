#include <iostream>
using namespace std;

const int TABLE_SIZE = 10;

class client
{
public:
    string name;
    long long int phoneNumber;
    bool isOccupied;
};

class Telephone
{
private:
    client hash_table[TABLE_SIZE];

    int findHashIndex(long long phonenum)
    {
        return phonenum % TABLE_SIZE;
    }

public:
    Telephone()
    {
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            hash_table[i].isOccupied = false;
        }
    }
    void insertClient(string name, long long int phonenum)
    {
        int index = findHashIndex(phonenum);

        int originalIndex = index;

        while (hash_table[index].isOccupied)
        {
            if (hash_table[index].phoneNumber == phonenum)
            {
                cout << "Record Already exists" << endl; // Fix typo and add endl
                return;
            }
            index = (index + 1) % TABLE_SIZE;

            if (index == originalIndex)
            {
                cout << "Table is full" << endl; // Add endl for better formatting
                return;
            }
        }

        hash_table[index].name = name;
        hash_table[index].phoneNumber = phonenum;
        hash_table[index].isOccupied = true;
    }

    void delete_client(long long int phonenum)
    {
        int index = findHashIndex(phonenum);
        int origional_index = index;
        while (hash_table[index].isOccupied)
        {
            if (hash_table[index].phoneNumber == phonenum)
            {
                hash_table[index].isOccupied = false;
                cout << "index " << index << " deleted" << endl;
                return;
            }
            index = (index + 1) % TABLE_SIZE;
            if (index == origional_index)
            {
                break;
            }
        }
        cout << "Phone number is not present";
    }
    void searchNumber(long long int phonenum)
    {
        int index = findHashIndex(phonenum);

        int origionalindex = index;
        while (hash_table[index].isOccupied)
        {
            if (hash_table[index].phoneNumber == phonenum)
            {
                cout << "key found at " << index << " position" << endl;
            }
            index = (index + 1) % TABLE_SIZE;
            if (index == origionalindex)
            {
                break;
            }
        }
        cout << "Number not present" << endl;
    }
    void display()
    {
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            if (hash_table[i].isOccupied)
                cout << i << "\t" << hash_table[i].name << "\t" << hash_table[i].phoneNumber << endl;
        }
    }
};

int main()
{
    Telephone *t = new Telephone();
    t->insertClient("prem", 7620349964);
    t->insertClient("om", 762034992);
    t->insertClient("atul", 7620359964);
    t->insertClient("ajay", 7620349965);

    t->display();
    t->delete_client(7620349965);
    t->display();

    return 0;
}
