#include <iostream>
#include <set>
#include <iterator>
using namespace std;

class Conference
{
public:
    set<string> spanishSpeakers;
    set<string> germanSpeakers;

    void addSpanishSpeaker(string name)
    {
        spanishSpeakers.insert(name);
    }

    void addGermanSpeaker(string name)
    {
        germanSpeakers.insert(name);
    }

    void displaySet(const set<string> &s)
    {
        for (const string &speaker : s)
        {
            cout << speaker << " ";
        }
        cout << endl;
    }

    void unionSets()
    {
        set<string> result = spanishSpeakers;
        result.insert(germanSpeakers.begin(), germanSpeakers.end());

        cout << "Union (Spanish ∪ German): ";
        displaySet(result);
    }

    void intersectionSets()
    {
        set<string> result;
        for (string speaker : spanishSpeakers)
        {
            if (germanSpeakers.find(speaker) != germanSpeakers.end())
            {
                result.insert(speaker);
            }
        }

        cout << "Intersection (Spanish ∩ German): ";
        displaySet(result);
    }

    void differenceSets()
    {
        set<string> result;
        for (const string &speaker : spanishSpeakers)
        {
            if (germanSpeakers.find(speaker) == germanSpeakers.end())
            {
                result.insert(speaker);
            }
        }

        cout << "Difference (Spanish - German): ";
        displaySet(result);
    }
};

int main()
{
    Conference conf;

    // Adding Spanish speakers
    conf.addSpanishSpeaker("Juan");
    conf.addSpanishSpeaker("Maria");
    conf.addSpanishSpeaker("Carlos");

    // Adding German speakers
    conf.addGermanSpeaker("Hans");
    conf.addGermanSpeaker("Maria");
    conf.addGermanSpeaker("Fritz");

    // Displaying the sets
    cout << "Spanish Speakers: ";
    conf.displaySet(conf.spanishSpeakers);

    cout << "German Speakers: ";
    conf.displaySet(conf.germanSpeakers);

    // Performing set operations
    conf.unionSets();
    conf.intersectionSets();
    conf.differenceSets();

    return 0;
}
