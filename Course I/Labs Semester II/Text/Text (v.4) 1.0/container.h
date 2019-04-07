#ifndef CONTAINER_H_INCLUDED
#define CONTAINER_H_INCLUDED
#include <string>

class Race
{
public:
    Race(long int rnum, long int snum, long int rang, long int misses, long int overtime, long int ent1, long int ex1, long int ent2, long int ex2, long int penalty);
    operator std::string() const;
    Race(const Race&);
    long int getFireTime() const;
    long int getMisses() const;
    //long int getRaceNumber() const;
    /*
    ~Race();
    void clear();
    void add(const std::string &item);
    bool find(const std::string &item) const;
    int getCount() const; */

private:
    const long int RaceNum, StartNum, Rank, Misses, OverallTime, Enter1, Exit1, FireTime1, Enter2, Exit2, FireTime2, PenaltyTime, summFireTime;
};

class Participant
{
public:
    Participant();
    Participant(std::string name, std::string surname, std::string country);
    Participant(const Participant&)=delete;
    Participant(Participant&&)=delete;
    Participant& operator=(const Participant&)=delete;
    Participant& operator=(Participant&&)=delete;
    ~Participant();
    void clear();
    std::string getAllInfo() const;
    double getMissPercentage() const;

private:
    struct Node{
        const long int racenum;
        Race race;
        bool hasBestTime;
        Node *next;
    };
    Node *head;
    int count;
    std::string name, surname, country;
    long int TotalMisses=0, TotalRaces=0, BestFireTime;
    double MissPercentage;

public:
    class Iterator
	{
	  public:
		Iterator(Node *current=nullptr);
		virtual Iterator& operator ++(); //move to next node if current node exist; else nothing
		virtual bool OK() const; // true iff current node exists;
		operator bool() const; //return OK()
		void setHasBestTimeToFalse() const;

		operator std::string() const;// throw(out_of_range) if no Node
		//long int getMark() const; //of current item; throw(out_of_range)
	  protected:
		Node *current;
	};
	Iterator find(const long int num) const; //returns iterator on found item; if no - on nullptr
    Iterator add(const long int rnum, const Race&);//returns iterator to newly created race; if no - on nullptr
    Iterator begin() const; //Iterator(head)
};

class Championship
{
public:
    Championship();
    Championship(const Championship&)=delete;
    Championship(Championship&&)=delete;
    Championship& operator=(const Championship&)=delete;
    Championship& operator=(Championship&&)=delete;
    ~Championship();
    void clear();

private:
    struct Node //sportsman node
    {
        std::string personalInfo;//name/surname/country - will be used to decide whether a sportsman exists and to find one
        Participant p;
        bool hasBestAim;
        Node* next;
    };
    Node* head;
    int count;
    double BestAim=1;

public:
    class Iterator{
      public:
        Iterator(Node *current=nullptr);
		virtual Iterator& operator ++();
		virtual bool OK() const;
		operator bool() const;
		void setHasBestAimToTrue()const;

        operator std::string() const;	 //all info about current sportsman if exist; else throw(out_of_range)
        //std::string getParticipantInfo() const; //throw(out_of_range)
        int checkForBestAim(const double aim) const;
        void setBestAim(double& aim) const;

        double getMissPercentage() const;
	//	void updateResult(); //throw(out_of_range)
        Participant::Iterator findRace(const long int racenum) const; //throw(out_of_range)
		Participant::Iterator addRace(const long int rnum, const Race&) const; //throw(out_of_range)
	  protected:
		Node *current;
	};

	Iterator find(const std::string personaInfo) const; //if no - iterator on nullptr
    Iterator add(const std::string personaInfo, const std::string name, const std::string surname, const std:: string country); //returns iterator to newly created sportsman
    Iterator begin() const;
  //  void addDItem(const std::string &item);
  //  bool findDItem (const std::string &item) const;
  //  int getDItemsCount() const;

    operator std::string() const;
    //void print() const; // to console
    void printResults(const std::string &fName) const; //nothrow; if empty string - to console;
   // void updateResults(); //in all sportsmen
    void findBestAim(); //finds best aim and participants that have it
    //bool checkSums(long int numOfParticipants, long int sumOfMarks) const; //true iff OK
    int getCount() const;

};

#endif // CONTAINER_H_INCLUDED


/*
class Participant
{
public:
    Participant();
    Participant(const Participant&)=delete;
    Participant(Participant&&)=delete;
    Participant& operator=(const Participant&)=delete;
    Participant& operator=(Participant&&)=delete;
    ~Participant();
    void clear();
private:
    struct Node{Race race; bool besttime; Node *next;};
    Node *head;
    int count;
    std::string name, surname, coutnry;
    int TotalMisses, TotalRaces;
    double MissPercentage, BestFireTime;
public:
    class Iterator
	{
	  public:
		Iterator(Node *current=nullptr);
		virtual Iterator& operator ++(); //move to next node if current node exist; else nothing
		virtual bool OK() const; // true iff current node exists;
		operator bool() const; //return OK()

		std::string operator *() const; //current item name with corresponding mark; throw(out_of_range) if no Node
		long int getMark() const; //of current item; throw(out_of_range)
	  protected:
		Node *current;
	};
	Iterator find(const std::string &item) const; //returns iterator on found item; if no - on nullptr
    Iterator add(const std::string &item, long int mark);//returns iterator to newly created item; if no - on nullptr
    Iterator begin() const; //Iterator(head)
    std::string print() const; // all present items with their marks
};

class Championship
{
public:
    Championship();
    Championship(const Championship&)=delete;
    Championship(Championship&&)=delete;
    Championship& operator=(const Championship&)=delete;
    Championship& operator=(Championship&&)=delete;
    ~Championship();
    void clear();
    long int getNumRaces() const;
private:
    static const long int numOfRaces=10;
    struct Node //sportsman node
    {
        long int startNumber;
        std::string name;
        std::string surname;
        double result;
        Node *next;
        Participant races[numOfRaces];
    };
    Node *head;
    int count;
    Race dItems;
public:
    class Iterator
	{
	  public:
		Iterator(Node *current=nullptr);
		virtual Iterator& operator ++();
		virtual bool OK() const;
		operator bool() const;

        std::string operator *() const;	 //all info about current sportsman if exist; else throw(out_of_range)
        long int getStartNumber() const; //throw(out_of_range)
		std::string getName() const;    //throw(out_of_range)
		std::string getSurname() const; //throw(out_of_range)
		double getResult() const;  //throw(out_of_range)
		long int getSumMarks() const; //sum of all marks for this sportsman; throw(out_of_range)
		void updateResult(); //throw(out_of_range)
        Participant::Iterator findItem(long int race, const std::string &name) const; //throw(out_of_range)
		Participant::Iterator addItem(long int race, const std::string &name, long int mark) const; //throw(out_of_range)
	  protected:
		Node *current;
	};
	Iterator find(long int startNumber) const; //if no - iterator on nullptr
    Iterator add(long int startNumber, const std::string &name, const std::string &surname); //returns iterator to newly created sportsman
    Iterator begin() const;
    void addDItem(const std::string &item);
    bool findDItem (const std::string &item) const;
    int getDItemsCount() const;

    void print() const; // to console
    void updateResults(); //in all sportsmen
    void sortByResults(); //non-decreasing order; with bubble sort
    void printResults(const std::string &fName) const; //nothrow; if empty string - to console;
    bool checkSums(long int numOfParticipants, long int sumOfMarks) const; //true iff OK
    int getCount() const;
};
*/
