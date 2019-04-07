#include <string>
using namespace std;
class DeclaredItems
{
public:
    DeclaredItems();
    DeclaredItems(const DeclaredItems&)=delete;
    DeclaredItems(DeclaredItems&&)=delete;
    DeclaredItems& operator=(const DeclaredItems&)=delete;
    DeclaredItems& operator=(DeclaredItems&&)=delete;
    ~DeclaredItems();
    void clear();
    void add(const string &item);
    bool find(const string &item) const;
    int getCount() const;
private:
    struct Node{string name; Node *next;};
    Node *head;
    int count;
};

class Judge
{
public:
    Judge();
    Judge(const Judge&)=delete;
    Judge(Judge&&)=delete;
    Judge& operator=(const Judge&)=delete;
    Judge& operator=(Judge&&)=delete;
    ~Judge();
    void clear();
private:
    struct Node{string itemName; long int mark; Node *next;};
    Node *head;
    int count;
public:
    class Iterator
	{
	  public:
		Iterator(Node *current=nullptr);
		virtual Iterator& operator ++(); //move to next node if current node exist; else nothing
		virtual bool OK() const; // true iff current node exists;
		operator bool() const; //return OK()

		string operator *() const; //current item name with corresponding mark; throw(out_of_range) if no Node
		long int getMark() const; //of current item; throw(out_of_range)
	  protected:
		Node *current;
	};
	Iterator find(const string &item) const; //returns iterator on found item; if no - on nullptr
    Iterator add(const string &item, long int mark);//returns iterator to newly created item; if no - on nullptr
    Iterator begin() const; //Iterator(head)
    string print() const; // all present items with their marks
};

class Competition //sportsmen
{
public:
    Competition();
    Competition(const Competition&)=delete;
    Competition(Competition&&)=delete;
    Competition& operator=(const Competition&)=delete;
    Competition& operator=(Competition&&)=delete;
    ~Competition();
    void clear();
    long int getNumJudges() const;
private:
    static const long int numOfJudges=10;
    struct Node //sportsman node
    {
        long int startNumber;
        string name;
        string surname;
        double result;
        Node *next;
        Judge judges[numOfJudges];
    };
    Node *head;
    int count;
    DeclaredItems dItems;
public:
    class Iterator
	{
	  public:
		Iterator(Node *current=nullptr);
		virtual Iterator& operator ++();
		virtual bool OK() const;
		operator bool() const;

        string operator *() const;	 //all info about current sportsman if exist; else throw(out_of_range)
        long int getStartNumber() const; //throw(out_of_range)
		string getName() const;    //throw(out_of_range)
		string getSurname() const; //throw(out_of_range)
		double getResult() const;  //throw(out_of_range)
		long int getSumMarks() const; //sum of all marks for this sportsman; throw(out_of_range)
		void updateResult(); //throw(out_of_range)
        Judge::Iterator findItem(long int judge, const string &name) const; //throw(out_of_range)
		Judge::Iterator addItem(long int judge, const string &name, long int mark) const; //throw(out_of_range)
	  protected:
		Node *current;
	};
	Iterator find(long int startNumber) const; //if no - iterator on nullptr
    Iterator add(long int startNumber, const string &name, const string &surname); //returns iterator to newly created sportsman
    Iterator begin() const;
    void addDItem(const string &item);
    bool findDItem (const string &item) const;
    int getDItemsCount() const;

    void print() const; // to console
    void updateResults(); //in all sportsmen
    void sortByResult(); //non-decreasing order; with bubble sort
    void printResults(const string &fName) const; //nothrow; if empty string - to console;
    bool checkSums(long int numOfParticipants, long int sumOfMarks) const; //true iff OK
    int getCount() const;
};
