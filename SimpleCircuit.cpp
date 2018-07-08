#include<iostream>
#include<string>
using namespace std;
class data {
	private:
		int value;
	public:
		void setValue(int i) {
			value = i;
		}
		int getValue() {
			return value;
		}
		data operator*(const data& d) { //AND
			data da;
			if(d.value == value == 1) da.value = 1;
			else da.value = 0;
			return da;
		}
		data operator+(const data& d) { //OR
			data da;
			if(d.value == value == 0) da.value = 0;
			else da.value = 1;
			return da;
		}
		data operator!() { //NOT
			data da;
			if(value) da.value = 0;
			else da.value = 1;
			return da;
		}
		data operator-(const data& d) { //XOR
			data da;
			if(d.value == value) da.value = 0;
			else da.value = 1;
			return da;
		}
};
class gate:public data {
	private: 
		int input1,input2;
		data output;
		string name;
	public:
		void setIn(int in1,int in2) {input1 = in1;input2 = in2;}
		void calculate(data i1,data i2) {
			if(name == "AND") {
				output = AND(i1,i2);
			}
			else if(name == "OR") {
				output = OR(i1,i2);
			}
			else if(name == "NOT") {
				output = NOT(i1);
			}
			else if(name == "XOR") {
				output = XOR(i1,i2);
			}
			else if(name == "NAND") {
				output = NOT(AND(i1,i2));
			}
		}
		data AND(data in1,data in2) {
			data d;
			d = in1 * in2;
			return d;
		}
		data OR(data in1,data in2) {
			data d;
			d = in1 + in2;
			return d;
		}
		data NOT(data in1) {
			data d;
			d = !in1;
			return d;
		}
		data XOR(data in1,data in2) {
			data d;
			d = in1 - in2;
			return d;
		}
		void setName(string name) {
			this->name = name;
		}
		string getName() {
			return name;
		}
		int getInt1() {
			return input1;
		}
		int getInt2() {
			return input2;
		}
		data getOut() {
			return output;
		}
};

int main() {
//	data d1;
//	d1.setValue(1);
//	data d2;
//	d2.setValue(0);
//	data d3 = d2+!d1+d1;
//	cout<<d3.getValue();
	gate g[100];
	data d[100];
	for(int i =0;i<100;i++) {
		d[i].setValue(-1);
	}
	int n,input1,input2;
	string name;
	
	cout<<"Input total number of gates."<<endl;
	cin>>n;
	
	for(int i = 0;i < n;i++) {
		cout<<"Input names of gates,"<<"remain "<<n-i<<endl;
		cin>>name;
		if(name!="AND"&&name!="OR"&&name!="NOT"&&name!="XOR"&&name!="NAND") {
			cout<<"ilegal input."<<endl;
			i--;
		} else {
			g[i].setName(name);
		}
	} 
	
	cout<<"Check out output interfaces of gates"<<endl;
	for(int i = 0;i < n;i++) {
		cout<<i<<"."<<g[i].getName()<<" "<<endl;
	}

	bool check;
	
	while(!check) {
		check = true;
		cout<<"Connect output interfaces to input of others,input 101 or 100 if you want 1 or 0 to be an input"<<endl;
		for(int i = 0;i < n;i++) {
			cout<<"To "<<i<<"."<<g[i].getName()<<" "<<endl;
			cin>>input1>>input2;
			if(99>input1>n||99>input2>n) {
				cout<<"out of range."<<endl;
				i--;
			} else {
				g[i].setIn(input1,input2);	
			}	
		}		
		for(int i = 0;i < n;i++) {
			if(g[i].getInt1()==-1||g[i].getInt2()==-1) {
				cout<<"input of "<<i<<" is not full filled."<<endl; 
				check = false;			
			}
		}
		bool cnt = 0;
		for(int i = 0;i < n;i++) {
			if(g[i].getInt1()>99&&g[i].getInt2()>99) {
				cnt = 1;
			}
			if(g[i].getInt1()==i||g[i].getInt2()==i) {
				cnt = 1;
			}
		}
		if(!cnt) {
			cout<<"Loop circuit detected."<<endl;
			check = false;
		}
	}
	
	for(int i = 0;i < n;i++) {
		cout<<i<<"."<<g[i].getName()<<" "<<"input1:"<<g[i].getInt1()<<" input2:"<<g[i].getInt2()<<endl;
	}
	
	bool el = 0;
	bool tmp = 1;
	while(!el) {
		el = 1;
		for(int i = 0;i < n;i++) {
			int i1 = g[i].getInt1();
			int i2 = g[i].getInt2();
			if(d[i].getValue()!=-1) continue;
			else {
//				cout<<i<<"!"; 
				if(i1>99&&i2>99) {
					data d1;
					data d2;
					d1.setValue(i1-100);
					d2.setValue(i2-100);
					g[i].calculate(d1,d2);
					d[i] = g[i].getOut();
					cout<<i<<"."<<g[i].getName()<<": "<<d[i].getValue()<<endl;
				}
				else if(d[i1].getValue()!=-1&&i2>99) {
					data d2;
					d2.setValue(i2-100);
					g[i].calculate(d[i1],d2);
					d[i] = g[i].getOut();
					cout<<i<<"."<<g[i].getName()<<": "<<d[i].getValue()<<endl;
				}
				else if(d[i2].getValue()!=-1&&i1>99) {
					data d1;
					d1.setValue(i1-100);
					g[i].calculate(d[i2],d1);
					d[i] = g[i].getOut();
					cout<<i<<"."<<g[i].getName()<<": "<<d[i].getValue()<<endl;
				}
				else if(d[i1].getValue()!=-1&&d[i2].getValue()!=-1) {
					data d1;
					data d2;
					g[i].calculate(d[i1],d[i2]);
					d[i] = g[i].getOut();
					cout<<i<<"."<<g[i].getName()<<": "<<d[i].getValue()<<endl;
				}
			} 

		}		
		for(int i = 0;i < n;i++) {
			if(d[i].getValue() != -1) el =0;
		}
			for(int i = 0;i < n;i++) {
			if(d[i].getValue()==-1) tmp = 0;
		}
		if(tmp) {
			cout<<"successful running"<<endl;
			return 0; 
		}		
	}


} 


