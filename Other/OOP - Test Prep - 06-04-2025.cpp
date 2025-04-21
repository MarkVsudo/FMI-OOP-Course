#include <iostream>
#include <fstream>
//#include <iomanip>

// Bullshit
//const char* filename = "OOP - Test Prep - 06-04-2025.txt";
//const char* filenameBinary = "OOP - Test Prep - 06-04-2025 - Binary.bin";
//using namespace std;
//
//void writeFile() {
//	ofstream file(filename);
//	if (!file) {
//		cout << "Error opening file: " << filename << endl;
//		return;
//	}
//	file << "Hello World!" << endl;
//	file.close();
//}
//void appendFile() {
//	ofstream file(filename, ios::app);
//	if (!file) {
//		cout << "Error opening file: " << filename << endl;
//		return;
//	}
//	file << "Hello World!" << endl;
//	file.close();
//}
//void readFile() {
//	ifstream file(filename);
//	if (!file) {
//		cout << "Error opening file: " << filename << endl;
//		return;
//	}
//	char line[1024];
//	while (file.getline(line, sizeof(line))) {
//		cout << line << endl;
//	}
//	
//	file.close();
//}
//
//void writeBinaryFile() {
//	ofstream file(filenameBinary, ios::binary);
//	if (!file) {
//		cout << "Error opening file: " << filenameBinary << endl;
//		return;
//	}
//	int numbers[10]{1,2,3,4,5,6,7,8,9,10};
//	file.write((char*)(&numbers), sizeof(numbers));
//	file.close();
//}
//void appendBinaryFile() {
//	ofstream file(filenameBinary, ios::binary | ios::app);
//	if (!file) {
//		cout << "Error opening file: " << filenameBinary << endl;
//		return;
//	}
//	int numbers[10]{ 11111,222222,33333,444,55,66666,7777777,88,9565656,1010001 };
//	file.write((char*)(&numbers), sizeof(numbers));
//	file.close();
//}
//void readBinaryFile() {
//	ifstream file(filenameBinary, ios::binary);
//	if (!file) {
//		cout << "Error opening file: " << filenameBinary << endl;
//		return;
//	}
//	int numbers[10]{0};
//
//	//Read until EOF (!!file contains only 10 element arrays)
//	while (file.peek() != EOF) /* peek() looks at the next file bit */ {
//		file.read((char*)(&numbers), sizeof(numbers));
//		for (int i = 0; i < 10; i++) {
//			cout << setw(7) << numbers[i] << " ";
//		}
//		cout << endl;
//	}
//	file.close();
//}

/* Copy and Swap demo */
using std::swap;
class A {
	char* b,c;
	int a;

	/* Copy & Swap (only use when you can't break the swap) */
	A& operator=(const A& a) {
		if (&a != this) {
			A tmp(a);
			swap(this->b, tmp.b);
			swap(this->c, tmp.c);
			this->a = tmp.a;
		}
		return *this;
	}

};

/* Const arrays in Class + ... */
using namespace std;
char* copyString(const char* str) {
	if (!str || !*str)
		throw std::invalid_argument("Bad or empty string");
	char* res = new char[strlen(str) + 1];
	return strcpy(res, str);
}
const char* readString(istream& is) {
	static char buff[1024];
	if (!is) return nullptr;
	is.getline(buff, sizeof(buff), '\n');
	if (!is) return nullptr;
	return buff;
}
class Car {
public:
	Car(const char* m, const char* color = "N/A", unsigned km = 0) : km(km), model(copyString(model)), color(nullptr){}

	Car(const Car& c) : km(c.km),model(copyString(c.model)),color(nullptr) {
		try{
			color = copyString(c.color);
		}
		catch (exception e) {
			delete[](char*) model;
			throw;
		}
	}
	
	Car(istream& is) : km(0),model(copyString(readString(is))),color(nullptr){
		if (!(is >> km)) { 
			delete[](char*) model;
			throw std::invalid_argument("bad file");
		}
		is.ignore(1024, '\n');
		// readString(is);
		try {
			color = copyString(readString(is));
		}
		catch (exception e) {
			delete[] model;
			throw;
		}
	}
	
	~Car() {
		delete[] color;
		delete[] (char*) model; // const char* -> char*
	}
	Car& operator=(const Car&) = delete;

	unsigned getKm() const { return km; }
	void addKm(unsigned km) { this->km += km; }

	const char* getModel() const { return model; }

	const char* getColor() const { return color; }
	bool setColor(const char* newColor) {
		try {
			char* t = copyString(newColor);
			delete[] color;
			color = t;
		}
		catch (const std::bad_alloc& ba) {
			/* If we don't get new momry, try to use the current one */
			if (strlen(color) <= strlen(newColor)) {
				strcpy(color, newColor);
				return true;
			}
			cerr << "No new memory could be allocated";
			return false;
		}
		catch (exception e) {
			cerr << "Bad color";
			return false;
		}
	
	}
	
	void print(ostream& os = std::cout) const {
		os << model << '\n' << km << '\n' << color << endl;
	}

private:
	unsigned km;
	const char* const model;
	char* color;
};

class CarShop {
	Car** cars;
	const int slots;
	
public:
	CarShop& operator=(const CarShop& other) {
		if (other.slots > slots) 
			throw std::invalid_argument("Too many slots");
		if (this == &other)
			return *this;
		
		Car** old = cars;
		cars = new Car * [slots] {};
		for (size_t i = 0; i < slots; i++) {
			cars[i] = nullptr;
		}

		for (size_t i = 0; i < other.slots; i++){
			if (other.cars[i]) {
				try {
					Car* c = new Car(*(other.cars[i])); // because we don't have constructor from address blweh
					bool res = insert(c);
					/* + something else idk, he erased it */
				}
				catch (exception e) {}
			}
		}

		for (size_t i = 0; i < slots; i++)
			delete old[i];
		delete[] old;

		return *this;
	}

	Car* extractCar(int index) {
		if (index < 0 || index >= slots) {
			return nullptr;
		}
		Car* car = cars[index];
		cars[index] = nullptr;
		return car;
	}

	bool insert(Car*& car) {
		int pos = 0;
		while (pos < slots && cars[pos])
			++pos;
		if (pos == slots || !car) return false;
		cars[pos] = car;
		car = nullptr;
		return true;
	}

	bool createCar(char* model, char* color, unsigned km) {
		int pos = 0;
		while (pos < slots && cars[pos])
			++pos;
		if (pos == slots && cars[pos]) return false;
		Car* c = new Car(model, color, km);
		if (!c) return false;
		cars[pos] = c;
		return true;
	}

	~CarShop() {
		for (size_t i = 0; i < slots; i++)
			delete cars[i];
		delete[]cars;
	}
};


int main(){}