#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <iostream>

namespace v {
	template <class TYP>
	class Iterator {
	private:
		TYP* this_el;
	public:
		Iterator() : this_el(nullptr) {}
		Iterator(TYP* val) : this_el(val) {}
		~Iterator() {}
		bool operator !=(const Iterator<TYP>& other) const {
			if (this_el == nullptr || other.this_el == nullptr) {
				return false;
			}
			return (this->this_el != other.this_el);
		}
		bool operator ==(const Iterator<TYP>& other) const {
			if (this_el == nullptr || other.this_el == nullptr) {
				return false;
			}
			return (this->this_el == other.this_el);
		}
		bool operator <(const Iterator<TYP>& i) {
			return this->this_el < i.this_el;
		}
		bool operator >(const Iterator<TYP>& i) {
			return this->this_el > i.this_el;
		}
		bool operator <=(const Iterator<TYP>& i) {
			return this->this_el <= i.this_el;
		}
		bool operator >=(const Iterator<TYP>& i) {
			return this->this_el >= i.this_el;
		}
		TYP& operator *() {
			return *this->this_el;
		}
		TYP* operator ->() {
			return this->this_el;
		}
		Iterator<TYP>& operator ++() {
			++this->this_el;
			return *this;
		}
		Iterator<TYP>& operator --() {
			--this->this_el;
			return *this;
		}
		Iterator<TYP> operator --(int i) {
			Iterator <TYP> res;
			res = *this;	
			--this->this_el;
			return &*res;
		}
		Iterator<TYP> operator ++(int i) {
			Iterator <TYP> res;
			res = *this;
			++this->this_el;
			return &*res;
		}
		Iterator<TYP>(const Iterator<TYP>& other) {
			this->this_el = other.this_el;
		}
		Iterator<TYP>& operator = (const Iterator<TYP> other) {
			this->this_el = other.this_el;
			return *this;
		}

	};
	template <class T>
	class vector {
	    T* mas;
		int len;
	public:
		/// <summary>
		/// ����������� �� ���������
		/// </summary>
		vector() {
			 len = 0;
			 mas = nullptr;
		}
		/// <summary>
		///  ����������� 
		/// </summary>
		/// <param name="l">
		/// ���������� ���������, ��� ������� ���� �������� ������
		/// throw logic error ��� ������� ������� ������ ����� l<0
		/// </param>
		vector(int l) {
			if (l >= 0) {
				if (l > 0) {
					mas = new T[l];
					len = l;
				}
				else {
					len = 0;
					mas = nullptr;
				}
			}
			else { throw std::logic_error("Error"); }
		}
		/// ����������
		~vector() {
			delete[] mas;
		}
		/// <summary>
		/// �������� �������
		/// </summary>
		void erase() {
			if (mas != nullptr) {
				delete[] mas;
			}
			mas = nullptr;
			len = 0;
		}
		/// <summary>
		/// �������� ����������
		/// </summary>
		/// <param name="index">
		/// ������ �������� �������, ������� ���� �����
		/// </param>
		/// <returns>
		/// ���������� ��������� �� ������� ������� � �������� index
		/// throw logic_error ��� index < 0 || index > len
		/// </returns>
		T& operator[](int index) {
			if (index >= 0 && index < len)
			return mas[index];
			else { throw std::logic_error("Error"); }
		}
		/// <summary>
		/// ����������� �������� ����������
		/// </summary>
		/// <param name="index">
		/// ������ ������������� ��������
		/// </param>
		/// <returns>
		///  ���������� ��������� �� ������� ������� � �������� index
		///  throw logic_error ��� index < 0 || index > len
		/// </returns>
		T& operator[](int index) const {
			if (index >= 0 && index < len)
				return mas[index];
			else { throw std::logic_error("Error"); }
		}
		/// <summary>
		/// Geter
		/// </summary>
		/// <returns>
		///  ���������� ����� �������
		/// </returns>
		int getlen()const { return len; }
		/// <summary>
		/// ��������� ����� ������
		/// </summary>
		/// <param name="new_len">
		/// ����� ����� �������
		/// </param>
		void resize(int new_len) {
			if (new_len == len) { return; }
			if (new_len <= 0) {
				erase();
				return;
			}
			T* nmas = new T[new_len];
			for (int i = 0; i < len; i++) {
				nmas[i] = mas[i];
			}
			delete[] mas;
			mas = nmas;
			len = new_len;
		}
		/// <summary>
		/// ���������� ������ � ������ new_len
		/// </summary>
		/// <param name="new_len">
		/// ����� ����� ������� 
		/// </param>
		void reinit(int new_len) {
			erase();
			if (new_len <= 0) { return; }
			mas = new T[new_len];
			len = new_len;
		}
		/// <summary>
		/// �������� �������� � �������� index
		/// </summary>
		/// <param name="index">
		/// ������ ���������� ��������
		/// </param>
		void remove(int index) {
			if (index < 0 || index >= len) { return; }
			if (len == 1) {
				erase();
				return;
			}
			T* nmas = new T[len - 1];
			for (int i = 0; i < index; i++) {
				nmas[i] = mas[i];
			}
			for (int i = index + 1; i < len; i++) {
				nmas[i - 1] = mas[i];
			}
			delete[] mas;
			len--;
			mas = nmas;
			return;
		}
		/// <summary>
		/// ���������� � ������ �������� � ������� index
		/// </summary>
		/// <param name="index">
		/// ������ ������������ ��������
		/// </param>
		/// <param name="item">
		/// ����������� �������
		/// </param>
		void add(int index, T item) {
			if (index < 0 || index > len) { return; }
			T* nmas = new T[len + 1];
			for (int i = 0; i < index; i++) {
				nmas[i] = mas[i];
			}
			nmas[index] = item;
			for (int i = index; i < len; i++) {
				nmas[i + 1] = mas[i];
			}
			delete[] mas;
			len++;
			mas = nmas;
			return;
		}
		/// <summary>
		/// ���������� �����������
		/// </summary>
		/// <param name="other">
		/// ������, ������� ��������
		/// </param>
		vector(const vector& other) {
			this->len = other.len;
			this->mas = new T[this->len];
			for (int i = 0; i < this->len; i++) {
				this->mas[i] = other.mas[i];
			}
		}
		/// <summary>
		/// ���������� ��������� ������������ ������������ 
		/// </summary>
		/// <param name="other">
		/// ������, ������� ��������
		/// </param>
		/// <returns>
		/// ���������� ��������� �� ������� ������
		/// </returns>
		vector& operator = (const vector other) {
			this->len = other.len;
			this->mas = new T[this->len];
			for (int i = 0; i < this->len; i++) {
				this->mas[i] = other.mas[i];
			}
			return *this;
		}
		typedef Iterator<T> Iterator;
		/// <summary>
		/// ��������
		/// </summary>
		/// <returns>
		///  ���������� ��������� �� ��������� ������� �������
		/// </returns>
		Iterator begin() const {
			return Iterator(this->mas);
		}
		/// <summary>
		/// ��������
		/// </summary>
		/// <returns>
		/// ���������� ��������� �� �������� ������� ������� 
		/// </returns>
		Iterator end() const {
			return Iterator(this->mas+(this->len));
		}
		/// <summary>
		/// ����� 
		/// </summary>
		/// <param name="num">
		/// ����� �������� ��������
		/// </param>
		/// <returns>
		/// ������� ��������� �� ������� ������� num
		///</returns>
		Iterator find(int num) const {
			if (num < 0 || num > this->len) {
				num = this->len;
			}
			return Iterator(this->mas + num * (sizeof(T)));
		}
		/// <summary>
		/// ���������� ������ ��������
		/// </summary>
		/// <param name="new_el">
		/// ����� �������
		/// </param>
		void push_back(T new_el) {
			resize(this->len + 1);
			this->mas[this->len - 1] = new_el;
		}
		/// <summary>
		/// �������� �� ��, ���� �� ������
		/// </summary>
		/// <returns>
		/// True ���� ������, False ���� ���
		/// </returns>
		bool empty()const {
			if (len == 0) { return true; }
			else { return false; }
		}
	};
	template <class T, class  T1>
	class mapa {
	private:
		T* table_key;
		T1* table_value;
		int kol;
		void make_moreT() {
			T* new_T = nullptr;
			new_T = new T[this->kol + 1];
			for (int i = 0; i < this->kol; i++) {
				new_T[i] = this->table_key[i];
			}
			kol++;
			delete[] this->table_key;
			this->table_key = new_T;
		}
		void make_moreT1() {
			T1* new_T1 = nullptr;
			new_T1 = new T1[this->kol];
			for (int i = 0; i < this->kol - 1; i++) {
				new_T1[i] = this->table_value[i];
			}
			delete[] this->table_value;
			this->table_value = new_T1;
		}
	public:
		mapa() {
			this->table_key = nullptr;
			this->table_value = nullptr;
			this->kol = 0;
		}
		void add_el(T key, T1 value) {
			make_moreT();
			make_moreT1();
			this->table_key[kol - 1] = key;
			this->table_value[kol - 1] = value;
		}
		void del_el(T key) {
			T* new_T = nullptr;
			new_T = new T[this->kol - 1];
			T1* new_T1 = nullptr;
			new_T1 = new T1[this->kol - 1];
			int flag = 0;
			for (int i = 0; i < this->kol - 1; i++) {
				if (this->table_key[i] == key) {
					flag = 1;
				}
				if (flag == 0) {
					new_T[i] = this->table_key[i];
					new_T1[i] = this->table_value[i];

				}
				else if (flag == 1 && i + 1 < kol) {
					new_T[i] = this->table_key[i + 1];
					new_T1[i] = this->table_value[i];
				}
			}
			delete[] this->table_key;
			this->table_key = new_T;
			delete[] this->table_value;
			this->table_value = new_T1;
		}
		T1& operator [] (T key) {
			for (int i = 0; i < this->kol; i++) {
				if (this->table_key[i] == key) {
					return this->table_value[i];
					break;
				}
			}
			throw std::logic_error("no such key");
		}
		int get_kol() {
			return this->kol;
		}
	};

}


#endif // !VECTOR_HPP

