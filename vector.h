#pragma once

#include <iostream>

namespace collections {

	// Створюємо скорочення
	using uint = unsigned int;

	// Клас, інкапсулючий логіку динамічного масиву

	template <typename T> // шаблон
	class vector {

		T* _arr;		// вказівник на масив
		uint _size;		// фактичний розмір масиву (кількість активних комірок)
		uint _capacity;	// фактичний розмір + кількість резервних комірок

	public:

		/// <summary>
		/// Конструктор по замовченню
		/// </summary>
		vector() {

			//cout << "Vector default constructor " << this << endl;

			// nullptr - адреса 000000000, вказівник нікуди не вказує
			_arr = nullptr;
			_size = 0;
			_capacity = 0;
		}

		/// <summary>
		/// Конструктор копіювання - приймає екземпляр цього ж класу
		/// Та створює незалежну копію
		/// </summary>
		/// <param name="other">Вектор, на основі котрого створюємо новий</param>
		vector(const vector<T>& other) {

			/*cout << "Vector copy constructor "
				<< "from " << &other << " to " << this << endl;*/

				// Створюємо новий незалежний масив такого же розміру як в оригіналі
			this->_arr = new T[other._capacity];
			// Копіюємо значення розміру
			this->_size = other._size;
			this->_capacity = other._capacity;

			// З оригінального масиву поелементно копіюємо значення в наш масив
			for (int i = 0; i < _size; i++) {
				this->_arr[i] = other._arr[i];
			}
		}

		/// <summary>
		/// Конструктор переносу - переносить дані з other в this та очищує other
		/// </summary>
		/// <param name="other">Вектор з котрого взяти дані та обнулити його</param>
		vector(vector<T>&& other) {

			this->_size = other._size;
			this->_capacity = other._capacity;

			// Просто "забираємо" у other вектора адресу масиву та обрубаємо його зв'язок з масивом
			this->_arr = other._arr;
			other._arr = nullptr;
			other._size = 0;
			other._capacity = 0;
		}

		/// <summary>
		/// Конструктор, що створює масив вказаного розміру та заповнює комірки масива вказаним значенням.
		/// </summary>
		/// <param name="size">Розмір масиву</param>
		/// <param name="value">Значення, яким заповнити комірки масиву</param>
		vector(const uint size, const T value) {

			// cout << "Vector(size, value) constructor " << this << endl;

			/*this->_arr = new T[size];*/
			this->setCapacity(size + size / 2);
			this->_size = size;

			for (int i = 0; i < _size; i++) {
				this->_arr[i] = value;
			}
		}

		// Деструктор - метод, котрий автоматично викликається при "знищенні"
		// екземпляру вектора. Знищуватись об'єкт буде або в кінці зони дії
		// або ручному виклиці delete
		~vector() {

			// cout << "Vector destructor " << this << endl;

			delete[] _arr;
		}

		/// <summary>
		/// Отримати розмір вектору
		/// </summary>
		/// <returns>Розмір масиву</returns>
		uint getSize() const {
			return _size;
		}

		/// <summary>
		/// Отримати capacity
		/// </summary>
		/// <returns>Size + кількість резервних комірок</returns>
		uint getCapacity() const {
			return _capacity;
		}

		/// <summary>
		/// Встановити нове capacity
		/// </summary>
		/// <param name="capacity">Розмір масиву з резервними комірками</param>
		void setCapacity(const uint capacity) {

			// capacity не може бути менше розміру масиву
			// бо capacity = size + резервні комірки
			if (capacity < _size) {
				throw std::exception("capacity out of range");
			}

			// немає сенсу створювати новий масив з таким же capacity
			// бо в ньому нічого не зміниться
			if (capacity == _capacity)
				return;

			T* temp = new T[capacity];

			for (int i = 0; i < _size; i++)
				temp[i] = _arr[i];

			delete[] _arr;
			_arr = temp;

			this->_capacity = capacity;
		}

		/// <summary>
		/// Додати новий елемент в кінець масиву
		/// </summary>
		/// <param name="value">Значення нового елементу</param>
		void pushBack(const T value) {

			// якщо є резервні комірки - немає необхідності створювати новий масив
			if (_capacity > _size) {
				// в резервну комірку вставляємо нове значення
				_arr[_size] = value;
				_size++;
				return;
			}

			// якщо немає резервних комірок

			// Додаємо +1 комірку під нове значення та size/2 резервних комірок для майбутнього
			this->setCapacity(_size / 2 + 1 + _size);

			// В нову комірку вставляємо значення
			_arr[_size] = value;

			// +1 к розміру
			_size++;
		}

		/// <summary>
		/// Видалення останнього елемента вектору
		/// </summary>
		void popBack() {

			if (_size == 0) return;

			_size--;
		}

		/// <summary>
		/// Сортування за зростанням
		/// </summary>
		void sortAscending() {

			for (int i = 0; i < _size - 1; i++) {

				for (int j = 0; j < _size - i - 1; j++) {

					if (_arr[j] > _arr[j + 1]) {

						T temp = _arr[j];
						_arr[j] = _arr[j + 1];
						_arr[j + 1] = temp;
					}
				}
			}
		}

		/// <summary>
		/// Сортування за спаданням
		/// </summary>
		void sortDescending() {

			for (int i = 0; i < _size - 1; i++) {

				for (int j = 0; j < _size - i - 1; j++) {

					if (_arr[j] < _arr[j + 1]) {

						T temp = _arr[j];
						_arr[j] = _arr[j + 1];
						_arr[j + 1] = temp;
					}
				}
			}
		}

		/// <summary>
		/// Отримання даних по індексу
		/// </summary>
		/// <param name="index">Індекс масиву</param>
		/// <returns>Посилання на елемент по індексу</returns>
		T& getByIndex(const uint index) {

			if (index >= _size) {
				// навмисно викликаємо помилку
				throw std::exception("index out of range");
			}

			return _arr[index];
		}

		/// <summary>
		/// Порівняння вектору з іншим
		/// </summary>
		/// <param name="other">Вектор для порівняння</param>
		/// <returns>Чи однакові вектора</returns>
		bool equals(const vector<T>& other) const {

			// Якщо розміри різні - вектори не рівні
			if (this->_size != other._size) {
				return false;
			}

			// полементно перевіряємо
			for (int i = 0; i < _size; i++) {

				if (this->_arr[i] != other._arr[i]) {

					return false;
				}
			}

			return true;
		}

		/// <summary>
		/// Зклеїти два вектори в один і повернути
		/// </summary>
		/// <param name="other">Другий вектор</param>
		/// <returns>Новий вектор зліплений з двух</returns>
		vector<T> concatenate(const vector<T>& other) const {

			// Новий вектор, результат функції
			vector<T> result;

			// Вручну ініціалізуємо розмір та масив
			int totalSize = _size + other._size;

			result.setCapacity(totalSize + totalSize / 2);
			result._size = totalSize;
			/*result._arr = new T[result._size];*/

			// Копіюємо дані з першого масиву в ліву половину
			for (int i = 0; i < this->_size; i++) {
				result._arr[i] = this->_arr[i];
			}

			// Копіюємо дані з другого масиву в праву половину
			for (int i = 0; i < other._size; i++) {
				result._arr[i + this->_size] = other._arr[i];
			}

			return result;
		}

		/// <summary>
		/// Додати до поточного вектора нові комірки з другого
		/// </summary>
		/// <param name="other">Другий вектор</param>
		void append(const vector<T>& other) {

			// Якщо масив котрий ми хочемо додати до нашого повністю влазить в резервні комірки
			if (other._size <= (this->_capacity - this->_size)) {

				for (int i = 0; i < other._size; i++) {

					_arr[i + _size] = other._arr[i];
				}
				_size += other._size;
				return;
			}

			int totalSize = this->_size + other._size;
			this->setCapacity(totalSize + totalSize / 2);

			for (int i = 0; i < other._size; i++) {

				_arr[i + _size] = other._arr[i];
			}
			_size += other._size;
		}

		/// <summary>
		/// Переписати поточний вектор даними з переданого
		/// </summary>
		/// <param name="other">Другий вектор</param>
		void assign(const vector<T>& other) {

			// Видаляємо старі дані
			delete[] this->_arr;

			// Створюємо новий масив
			this->_size = other._size;
			this->_capacity = other._capacity;

			this->_arr = new T[other._capacity];

			// Переносимо дані з другого масива в наш
			for (int i = 0; i < other._size; i++) {
				this->_arr[i] = other._arr[i];
			}
		}

		/// <summary>
		/// Очистити вектор
		/// </summary>
		void clear() {
			delete[] this->_arr;
			this->_arr = nullptr;
			this->_size = 0;
			this->_capacity = 0;
		}

		/// <summary>
		/// Перегрузка оператора порівняння векторів
		/// </summary>
		/// <param name="other">Вектор для порівняння</param>
		/// <returns>Чи однакові вектори</returns>
		bool operator ==(const vector<T>& other) const {
			return this->equals(other);
		}

		/// <summary>
		/// Перегрузка оператора непорівняння векторів
		/// </summary>
		/// <param name="other">Вектор для порівняння</param>
		/// <returns>Чи різні вектори</returns>
		bool operator !=(const vector<T>& other) const {
			return !this->equals(other);
		}

		/// <summary>
		/// Перегрузка оператора конкатенації векторів
		/// </summary>
		/// <param name="other">Другий вектор</param>
		/// <returns>Новий вектор зліплений з двух</returns>
		vector<T> operator +(const vector<T>& other) const {
			return this->concatenate(other);
		}

		/// <summary>
		/// Перегрузка оператору додавання елементів до вектору з іншого
		/// </summary>
		/// <param name="other">Другий вектор</param>
		void operator +=(const vector<T>& other) {
			this->append(other);
		}

		/// <summary>
		/// Перегрузка оператора присвоєння
		/// </summary>
		/// <param name="other">Другий масив</param>
		void operator =(const vector<T>& other) {
			this->assign(other);
		}

		/// <summary>
		/// Перегрузка звернення по індексу
		/// </summary>
		/// <param name="index">Індекс елементу</param>
		/// <returns>Елемент по індексу</returns>
		T& operator [](const uint index) {
			return this->getByIndex(index);
		}
	};
}