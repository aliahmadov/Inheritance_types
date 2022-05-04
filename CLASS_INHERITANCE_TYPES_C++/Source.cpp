#include<iostream>
#include<assert.h>
#include<Windows.h>
using namespace std;

void mysetcolor(int fg, int bg) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, fg | (bg << 4));
}

template<typename T>
class Stack {
	T* data;
	int size = 0;

public:
	Stack() :data(nullptr), size(0) {};


	T peek()const {
		return data[size - 1];
	}



	void push_back(T value) {

		auto newdata = new T[size + 1]{};

		for (size_t i = 0; i < size; i++)
		{
			newdata[i] = data[i];
		}

		newdata[size] = value;
		if (size != 0) {
			delete[]data;
		}
		data = newdata;
		newdata = nullptr;
		size++;
	}

	void pop() {
		auto newdata = new T[size - 1]{};

		for (size_t i = 0; i < size - 1; i++)
		{
			newdata[i] = data[i];
		}

		if (size != 0) {
			delete[]data;
		}

		data = newdata;
		newdata = nullptr;
		size--;
	}


	void Clear() {
		if (this->data == NULL || this->size == 0) {
			return;
		}

		delete[]data;
		this->data = NULL;
		this->size = 0;
	}

	int GetSize()const {
		return size;
	}

	void print() const {
		for (size_t i = 0; i < size; i++)
		{
			cout << data[i];
		}cout << endl;
	}

	T& operator[]( const int& index) const {
		return data[index];
	}

	~Stack()
	{
		//delete[]data;
	}
};


class Person {
	string name;
	string surname;
	int age;
public:
	Person() :name(" "), surname(" "), age(0) {}

	Person(const string& name, const string& surname, const int& age)
	{
		SetName(name);
		SetSurname(surname);
		SetAge(age);
	}

#pragma region PersonSettersGetters


	string GetName()const {
		return name;
	}

	string GetSurname()const {
		return surname;
	}

	int GetAge()const {
		return age;
	}

	void SetName(const string& name) {
		assert(name.length() > 2 && "Fill the name area!!!");
		this->name = name;
	}

	void SetSurname(const string& surname) {
		assert(surname.length() > 2 && "Fill the surname area !!!");
		this->surname = surname;
	}

	void SetAge(const int& age) {
		assert(age >= 0 && "Age value cannot be less than 0 !!!");
		this->age = age;
	}

#pragma endregion

	void Show()const {
		cout << "Name: " << name << endl;
		cout << "Surname: " << surname << endl;
		cout << "Age: " << age << endl;
	}

};




class Commander :Person {
	string armyWorkPractice;
	int victoryCount;
	string ArmyNo;
public:
	Commander() :armyWorkPractice(" "), victoryCount(0), ArmyNo(" ") {}

	Commander(const string& name, const string& surname, const int& age,
		const string& armyWorkPractice, const int& victoryCount,
		const string& ArmyNo) : Person(name, surname, age)
	{
		SetArmyNo(ArmyNo);
		SetVictoryCount(victoryCount);
		SetArmyWorkPractice(armyWorkPractice);
	}

#pragma region CommanderSettersGetters


	string GetArmyWorkPractice()const {
		return armyWorkPractice;
	}

	int GetVictoryCount()const {
		return victoryCount;
	}

	string GetArmyNo()const {
		return ArmyNo;
	}

	void SetArmyWorkPractice(const string& armyWP) {
		assert(armyWP.length() > 2 && "Army Work Practice area should be filled !!!");
		this->armyWorkPractice = armyWP;
	}

	void SetVictoryCount(const int& vC) {
		assert(vC >= 0 && "Victory count value cannot be less than 0 !!!");
		this->victoryCount = vC;
	}

	void SetArmyNo(const string& armyNo) {
		assert(armyNo.length() >= 2 && "Army No area should be filled !!!");
		this->ArmyNo = armyNo;
	}
#pragma endregion

	void Show()const {
		Person::Show();
		cout << "Army No: " << ArmyNo << endl;
		cout << "Army Work Practice: " << armyWorkPractice << endl;
		cout << "Victory Count: " << endl;
	}
};



class Fighter {
	double fightPower;
	string weapon;
public:

	Fighter() :fightPower(0), weapon(" ") {}

	Fighter(const double& fightPower, const string& weapon) {
		SetPower(fightPower);
		SetWeapon(weapon);
	}

#pragma region FighterSettersGetters
	double GetPower()const {
		return fightPower;
	}

	string GetWeapon()const {
		return weapon;
	}

	void SetPower(const double& fightPower) {
		assert(fightPower >= 0 && "Power Value cannot be negative !!!");
		this->fightPower = fightPower;
	}

	void SetWeapon(const string& weapon) {
		assert(weapon.length() >= 2 && "Weapon area should be filled !!!");
		this->weapon = weapon;
	}
#pragma endregion

	void attack() {
		cout << "I am fighter !!!" << endl;
	}

	void Show()const {
		cout << "Fight Power: " << fightPower << endl;
		cout << "Weapon: " << weapon << endl;
	}
};




class Soldier : virtual public Person, public Fighter {
	int id;
public:

	Soldier() :id(0) {}

	Soldier(const int& id, const string& name, const string& surname, const int& age,
		const double& fightPower, const string& weapon) :
		Person(name, surname, age), Fighter(fightPower, weapon)
	{
		SetId(id);
	}

	void SetId(const int& id) {
		assert(id >= 0 && "ID value cannot be less than 0 !!!");
		this->id = id;
	}

	int GetId()const {
		return id;
	}

	void attack() {
		Fighter::attack();
		cout << "I help army by my human power !!!" << endl;
	}

	double GetPower() {
		return Fighter::GetPower();
	}

	void Show()const {
		cout << "Soldier ID: " << id << endl;
		Person::Show();
		Fighter::Show();
	}


	friend ostream& operator<<(ostream& out, const Soldier& soldier);


};

ostream& operator<<(ostream& out, const Soldier& soldier) {
	out << "\nSoldier ID: " << soldier.GetId() << endl;
	soldier.Person::Show();
	soldier.Fighter::Show();
	cout << "==============================" << endl;
	cout << endl;
	return out;
}



class Tank :public Fighter {
	string tankName;
	Stack<Soldier>soldiers;
public:
	Tank() : tankName(" ") {}

	Tank(const double& fightPower, const string& weapon, const string& tankName) :
		Fighter(fightPower, weapon)
	{
		SetTankName(tankName);
	}

	string GetTankName()const {
		return tankName;
	}

	void SetTankName(const string& tankName) {
		this->tankName = tankName;
	}
	
	double GetPower() const {
		double sum_power = 0;
		for (size_t i = 0; i < soldiers.GetSize(); i++)
		{
			sum_power += soldiers[i].GetPower();
		}
		return sum_power;
	}

	double GetTotalPower()const {
		return Tank::GetPower() + Fighter::GetPower();
	}

	void AddSoldiers(const Soldier& soldier) {
		soldiers.push_back(soldier);
	}

	void attack() {
		Fighter::attack();
		cout << "I help army with my explosion power !!!" << endl;
	}
	void Show()const {
		cout << "\n T A N K  I N F O \n=====================\n";
		cout << "Tank Name: " << tankName << endl;
		cout << "\nTANK SOLDIERS" << endl;
		soldiers.print();
		Fighter::Show();
		cout << "Total Power: " << GetTotalPower() << endl;
	}

	friend ostream& operator<<(ostream& out, const Tank& tank);

};

ostream& operator<<(ostream& out, const Tank& tank) {
	out << "\n Tank Info\n=====================\n";
	mysetcolor(4, 0);
	out << "Tank Name: " << tank.tankName << endl;
	mysetcolor(7, 0);
	mysetcolor(14, 0);
	out << "\nT a n k  S o l d i e r s " << endl;
	out << "********************************" << endl;
	mysetcolor(7, 0);
	tank.soldiers.print();
	mysetcolor(14, 0);
	out << "********************************" << endl;
	mysetcolor(7, 0);
	tank.Fighter::Show();
	mysetcolor(9, 0);
	out << "\nT o t a l  P o w e r ---> " << tank.GetTotalPower() << endl;
	mysetcolor(7, 0);

	return out;
}


class MilitaryAircraft :Fighter {
	string aircraftName;
	Stack<Soldier> soldiers;
public:
	MilitaryAircraft() :aircraftName(" ") {}

	MilitaryAircraft(const double& fightPower, const string& weapon,
		const string& aircraftName,const Stack<Soldier>& soldiers) :Fighter(fightPower, weapon)
	{
		SetAircraftName(aircraftName);
		this->soldiers = soldiers;
	}

	string GetAircraftName()const {
		return aircraftName;
	}

	void SetAircraftName(const string& aircraftName) {
		assert(aircraftName.length() >= 2 && "Aircraft name area should be filled !!!");
		this->aircraftName = aircraftName;
	}

	double GetPower()const {
		double sum_power = 0;
		for (size_t i = 0; i < soldiers.GetSize(); i++)
		{
			sum_power += soldiers[i].GetPower();
		}
		return sum_power;
	}

	double GetTotalPower() const {
		return Fighter::GetPower() + MilitaryAircraft::GetPower();
	}

	void AddSoldiers(const Soldier& soldier) {
		soldiers.push_back(soldier);
	}
	void attack() {
		Fighter::attack();
		cout << "I help army with my ability to protect air territory !!!" << endl;
	}

	void Show()const{
		cout << "AIRCRAFT INFO" << endl;
		cout << "========================" << endl;
		cout << "Aircraft Name: " << aircraftName << endl;
		cout << "Aircraft Soldiers" << endl;
		soldiers.print();
		Fighter::Show();
		cout << "Total Power: " << GetTotalPower() << endl;
	}

	friend ostream& operator<<(ostream& out, const MilitaryAircraft& aircraft);

};

ostream& operator<<(ostream& out, const MilitaryAircraft& a) {
	cout << " AirCraft Info" << endl;
	cout << "========================" << endl;
	mysetcolor(4, 0);
	cout << "Aircraft Name: " << a.aircraftName << endl;
	mysetcolor(7, 0);
	mysetcolor(14, 0);
	cout << "\n A i r c r a f t   S o l d i e r s " << endl;
	out << "*********************************************" << endl;
	mysetcolor(7, 0);
	a.soldiers.print();
	mysetcolor(14, 0);
	out << "*********************************************" << endl;
	mysetcolor(7, 0);
	a.Fighter::Show();
	mysetcolor(9, 0);
	cout << "\nT o t a l  P o w e r ---> " << a.GetTotalPower() << endl;
	mysetcolor(7, 0);

	return out;
}


class MilitaryShip :Fighter {
	string shipName;
	Stack<Soldier>soldiers;
public:
	MilitaryShip() :shipName(" ") {}

	MilitaryShip(const double& fightPower, const string& weapon,
		const string& shipName, const Stack<Soldier>& soldiers) :Fighter(fightPower, weapon)
	{
		SetShipName(shipName);
		this->soldiers = soldiers;
	}

	string GetShipName()const {
		return shipName;
	}

	void AddSoldier(const Soldier& soldier) {
		soldiers.push_back(soldier);
	}

	void SetShipName(const string& shipName) {
		assert(shipName.length() >= 2 && "Ship Name Area should be filled !!!");
		this->shipName = shipName;
	}

	double GetPower()const {
		double sum_power = 0;
		for (size_t i = 0; i < soldiers.GetSize(); i++)
		{
			sum_power += soldiers[i].GetPower();
		}
		return sum_power;
	}

	double GetTotalPower()const {
		return MilitaryShip::GetPower() + Fighter::GetPower();
	}

	void Show()const {
		cout << "Military Ship Info" << endl;
		cout << "========================" << endl;
		cout << "Ship Name: " << shipName << endl;
		cout << "Ship Soldiers" << endl;
		soldiers.print();
		Fighter::Show();
		cout << "Total Power: " << GetTotalPower() << endl;
	}


	friend ostream& operator<<(ostream& out, const MilitaryShip& m);
};

ostream& operator<<(ostream& out, const MilitaryShip& m) {
	cout << "Military Ship Info" << endl;
	cout << "========================" << endl;
	mysetcolor(4, 0);
	cout << "Ship Name: " << m.shipName << endl;
	mysetcolor(7, 0);
	mysetcolor(14, 0);
	out << "\n S h i p  S o l d i e r s " << endl;
	out << "********************************" << endl;
	mysetcolor(7, 0);
	m.soldiers.print();
	mysetcolor(14, 0);
	out << "**********************************" << endl;
	mysetcolor(7, 0);
	m.Fighter::Show();
	mysetcolor(9, 0);
	cout << "\nT o t a l  P o w e r ---> " << m.GetTotalPower() << endl;
	mysetcolor(7, 0);
	return out;
}

class Army {
	Commander commander;
	Stack<Soldier> soldiers;
	Stack<Tank> tanks;
	Stack<MilitaryAircraft> aircrafts;
	Stack<MilitaryShip> militaryShips;
public:

	Army() {}

	Army(const Commander& commander, const Stack<Soldier>& soldiers, const Stack<Tank>& tanks,
		const Stack<MilitaryAircraft>& aircrafts, const Stack<MilitaryShip>& militaryShips)
	{
		this->commander = commander;
		this->soldiers = soldiers;
		this->tanks = tanks;
		this->aircrafts = aircrafts;
		this->militaryShips = militaryShips;
	}
	void addSoldier(const Soldier& soldier) {

		soldiers.push_back(soldier);
	}

	double calculateArmyPower() {
		double total_power = 0;
		for (size_t i = 0; i < soldiers.GetSize(); i++)
		{
			total_power += soldiers[i].GetPower();
		}
		for (size_t i = 0; i < tanks.GetSize(); i++)
		{
			total_power += tanks[i].GetTotalPower();
		}

		for (size_t i = 0; i < aircrafts.GetSize(); i++)
		{
			total_power += aircrafts[i].GetTotalPower();
		}

		for (size_t i = 0; i < militaryShips.GetSize(); i++)
		{
			total_power += aircrafts[i].GetTotalPower();
		}
		return total_power;
	}



	void Show() {
		mysetcolor(6, 0);
		cout << "\n********************************************************" << endl;
		mysetcolor(4, 0);
		cout << "******************* A R M Y  P O W E R ******************" << endl;
		mysetcolor(6, 0);
		cout << "*********************************************************\n" << endl;
		//mysetcolor(7, 0);
		mysetcolor(6, 0);
		cout << "A r m y  C o m m a n d e r\n" << endl;
		mysetcolor(7, 0);
		commander.Show();

		mysetcolor(3, 0);
		cout << "==========================" << endl;
		mysetcolor(7, 0);

		mysetcolor(6, 0);
		cout << "\nS O L D I E R S\n" << endl;
		mysetcolor(7, 0);
		soldiers.print();
		cout << "==============================" << endl;
		mysetcolor(6, 0);
		cout << "\ T A N K S\n" << endl;
		mysetcolor(7, 0);
		tanks.print();

		mysetcolor(6, 0);
		cout << "\n A I R C R A F T S \n" << endl;
		mysetcolor(7, 0);

		aircrafts.print();

		mysetcolor(6, 0);
		cout << "\n M I L I T A R Y  S H I P S \n" << endl;
		mysetcolor(7, 0);
		militaryShips.print();

		mysetcolor(2, 0);
		cout << "\n A  R  M  Y      T  O  T  A  L      P  O  W  E  R   :    ";
		mysetcolor(4, 0);
		cout << calculateArmyPower() << endl;
		mysetcolor(7, 0);
	}
};


void main() {



	Soldier s1(1, "Ali", "Ahmadov", 20, 75, "AK-47");
	Soldier s2(2, "Elgun", "Memmedov", 12, 85, "M-416");
	Soldier s3(3, "Brad", "Pitt", 30, 65, "Mini-14");
	Soldier s4(4, "John", "Wick", 39, 100, "Makarov");
	Soldier s5(5, "Arnold", "Swatszchneiger", 45, 150, "Winchester");
	Soldier s6(6, "Ronald", "Tony", 24, 110, "Vector");
	Soldier s7(7, "Christian", "Bale", 42, 85, "Mk-14");
	Soldier s8(8, "Ugur", "Memmedov", 10, 78, "M16A4");
	Soldier s9(9, "James", "Williams", 28, 150, "AWM-Sniper");
	Soldier s10(10, "Don", "Carlione", 32, 200, "M24-Sniper");
	
	Stack<Soldier>soldiers;
	soldiers.push_back(s1);
	soldiers.push_back(s2);
	soldiers.push_back(s3);
	soldiers.push_back(s4);
	soldiers.push_back(s5);
	soldiers.push_back(s6);
	soldiers.push_back(s7);
	soldiers.push_back(s8);
	soldiers.push_back(s9);
	soldiers.push_back(s10);


	Stack<Tank>tanks;

	Tank t1(75, "Explosion tube", "Itiqovan");
	t1.AddSoldiers(s1);
	t1.AddSoldiers(s2);
	
	Tank t2(75, "tank gun", "T-54");
	t2.AddSoldiers(s7);
	t2.AddSoldiers(s8);

	tanks.push_back(t1);
	tanks.push_back(t2);

	Stack<Soldier>aircraft_soldiers;

	MilitaryAircraft aC1(100, "Bomb", "MiG-21",aircraft_soldiers);
	aC1.AddSoldiers(s3);
	aC1.AddSoldiers(s4);

	Stack<MilitaryAircraft>aircrafts;
	aircrafts.push_back(aC1);

	Stack<Soldier>militaryShip_soldiers;
	MilitaryShip mS1(90, "Strike Missile", "CG-54", militaryShip_soldiers);
	mS1.AddSoldier(s5);
	mS1.AddSoldier(s6);

	Stack<MilitaryShip>militaryShips;
	militaryShips.push_back(mS1);

	Commander commander("Edgar", "Markov", 50, "15 years", 21, "B432");

	Army army(commander, soldiers, tanks, aircrafts, militaryShips);

	army.Show();

	


}