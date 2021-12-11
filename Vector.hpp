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
		/// Конструктор по умолчанию
		/// </summary>
		vector() {
			 len = 0;
			 mas = nullptr;
		}
		/// <summary>
		///  Конструктор 
		/// </summary>
		/// <param name="l">
		/// количество элементов, под которые надо выделить вектор
		/// throw logic error при попытке создать массив длины l<0
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
		/// Деструктор
		~vector() {
			delete[] mas;
		}
		/// <summary>
		/// очищение массива
		/// </summary>
		void erase() {
			if (mas != nullptr) {
				delete[] mas;
			}
			mas = nullptr;
			len = 0;
		}
		/// <summary>
		/// оператор индексации
		/// </summary>
		/// <param name="index">
		/// индекс элемента массива, который надо найти
		/// </param>
		/// <returns>
		/// возвращает указатель на элемент массива с индексом index
		/// throw logic_error при index < 0 || index > len
		/// </returns>
		T& operator[](int index) {
			if (index >= 0 && index < len)
			return mas[index];
			else { throw std::logic_error("Error"); }
		}
		/// <summary>
		/// Константный оператор индексации
		/// </summary>
		/// <param name="index">
		/// индекс возвращаемого элемента
		/// </param>
		/// <returns>
		///  возвращает указатель на элемент массива с индексом index
		///  throw logic_error при index < 0 || index > len
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
		///  возвращает длину массива
		/// </returns>
		int getlen()const { return len; }
		/// <summary>
		/// выделение новой памяти
		/// </summary>
		/// <param name="new_len">
		/// новая длина массива
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
		/// пересоздаёт массив с длиной new_len
		/// </summary>
		/// <param name="new_len">
		/// новая длина массива 
		/// </param>
		void reinit(int new_len) {
			erase();
			if (new_len <= 0) { return; }
			mas = new T[new_len];
			len = new_len;
		}
		/// <summary>
		/// Удаление элемента с индексом index
		/// </summary>
		/// <param name="index">
		/// индекс удаляемого элемента
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
		/// Добавдение в массив элемента с номером index
		/// </summary>
		/// <param name="index">
		/// индекс добавляемого элемента
		/// </param>
		/// <param name="item">
		/// добавляемый элемент
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
		/// копирующий конструктор
		/// </summary>
		/// <param name="other">
		/// Вектор, который копируют
		/// </param>
		vector(const vector& other) {
			this->len = other.len;
			this->mas = new T[this->len];
			for (int i = 0; i < this->len; i++) {
				this->mas[i] = other.mas[i];
			}
		}
		/// <summary>
		/// перегрузка оператора присваивания копированием 
		/// </summary>
		/// <param name="other">
		/// вектор, который копируют
		/// </param>
		/// <returns>
		/// возвращает указатель на текущий вектор
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
		/// Итератор
		/// </summary>
		/// <returns>
		///  Возвращает указатель на начальный элемент массива
		/// </returns>
		Iterator begin() const {
			return Iterator(this->mas);
		}
		/// <summary>
		/// Итератор
		/// </summary>
		/// <returns>
		/// возвращает указатель на конечный элемент массива 
		/// </returns>
		Iterator end() const {
			return Iterator(this->mas+(this->len));
		}
		/// <summary>
		/// Поиск 
		/// </summary>
		/// <param name="num">
		/// номер искомого элемента
		/// </param>
		/// <returns>
		/// передаёт указатель на элемент массива num
		///</returns>
		Iterator find(int num) const {
			if (num < 0 || num > this->len) {
				num = this->len;
			}
			return Iterator(this->mas + num * (sizeof(T)));
		}
		/// <summary>
		/// Добавление нового элемента
		/// </summary>
		/// <param name="new_el">
		/// Новый элемент
		/// </param>
		void push_back(T new_el) {
			resize(this->len + 1);
			this->mas[this->len - 1] = new_el;
		}
		/// <summary>
		/// Проверка на то, пуст ли вектор
		/// </summary>
		/// <returns>
		/// True если пустой, False если нет
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

