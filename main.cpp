#include<iostream>
using namespace std;
class data {
	private:
		bool value;
	public:
		data(int i) {
			setValue(i)
		}
		bool getValue() {
			return value;
		}
		void setValue(v) {
			value = v;
		}
		data operator+(const data& d) {
			data da;
			da.value = da.value && d.value;
		}
		data operator*(const data& d) {
			data da;
			da.value = da.value || d.value;
		}
		data operator!(const data& d) {
			data da;
			da.value = !da.value 
		}
}

main() {
	data d1(1);
	data d2(0);
	data d3 = d1 + d2;
	cout<<d3.getvalue();
} 
