#include <iostream>

using namespace std;

class AFIFO 
{
private:
	int* items; //tablica przechowujaca elementy kolejki
	int capacity; //maksymalna pojemnosc tablicy
	int fifo_size; //liczba elementow w tablicy, w kolejce
	int head; //wskazuje na pierwszy element w kolejce
	int tail; //wskazuje na ostatni element w kolejce
public:
	AFIFO(int c); //konstruktor, tworzy tablice o pojemnosci c, pusta kolejke
	bool empty(); //zwraca true, jesli kolejka jest pusta, false w przeciwnym razie
	bool full(); //zwraca true, jesli kolejka jest pelna, false w przeciwnym razie
	void enqueue(int x); //dodaje element do kolejki w pierwszym wolnym miejscu
	int dequeue();		//usuwa i zwraca daną z kolejki
	void clear();    //usuwa kolejke
	friend ostream& operator<<(ostream& out, AFIFO& s);
};

AFIFO::AFIFO(int c) 
{
	items = new int[c];
	capacity = c;
	fifo_size = 0;
	head = 0;
	tail = -1; //-1 mowi, ze kolejka jest pusta
}

bool AFIFO::empty() 
{
	/**if (fifo_size <= 0)
		return true;
	else
		return false;**/

	if (tail == -1)
		return true;
	return false;
}

bool AFIFO::full() 
{
	/**if (fifo_size >= capacity)
		return true;
	else
		return false;**/

	if (capacity <= fifo_size)
		return true;
	return false;
}

void AFIFO::enqueue(int x) 
{
	/**if ((tail < capacity - 1) && (fifo_size < capacity)) 
	{
		tail++;
		items[tail] = x;
		fifo_size++;
	}
	else if ((tail >= capacity - 1) && (fifo_size < capacity)) 
	{
		tail = 0;
		items[tail] = x;
		fifo_size++;
	}
	else 
	{
		//cout << "Kolejka jest pelna" << endl;
		return;
	}**/

	if (full())
		return;

	tail++;
	fifo_size++;
	items[tail] = x;

}

int AFIFO::dequeue() 
{
	/**if (!empty() && (head < capacity)) 
	{
		int wartosc = items[head];
		head++;
		if (head == tail) 
		{
			head = 0;
			tail = -1;
		}
		return wartosc;
	}
	else if (!empty() && (head >= capacity)) 
	{
		head = 0;
		int wartosc = items[head];
		head++;
		if (head == tail) 
		{
			head = 0;
			tail = -1;
		}
		return wartosc;
	}
	else 
	{
		//cout << "Kolejka jest pusta" << endl;
		return NULL;
	}**/

	if (empty())
		return NULL;

	int wartosc = items[head];
	for (int i = head; i < tail; i++)
	{
		items[i] = items[i + 1];
	}
	tail--;
	fifo_size--;
	return wartosc;
}

void AFIFO::clear() 
{
	/**while (!empty()) 
	{
		dequeue();
	}**/

	if (!empty())
	{
		head = 0;
		tail = -1;
		fifo_size = 0;
	}
	else
		return;
}

ostream& operator<<(ostream& out, AFIFO& q) 
{
	if (q.empty())
		return out;
	int index = q.head;
	while (index != q.tail+1) 
	{
		if (index < q.capacity) 
		{
			out << q.items[index] << " ";
			index++;
		}
		else 
		{
			index = 0;
		}
	}
	return out;

	/**do
	{
		if (index < q.capacity)
		{
			out << q.items[index] << " ";
			index++;
		}
		else
		{
			index = 0;
		}
	} while (index != q.tail);
	return out;**/
}

int main()
{
	//AFIFO kolejka(5);
	//drugi sposob
	AFIFO kolejka = AFIFO(5);

	kolejka.enqueue(1);
	kolejka.enqueue(3);
	kolejka.enqueue(5);
	kolejka.enqueue(7);
	cout << "Stan kolejki: " << kolejka << endl;

	kolejka.dequeue();
	kolejka.dequeue();
	cout << "Stan kolejki: " << kolejka << endl;

	kolejka.enqueue(2);
	kolejka.enqueue(4);
	kolejka.enqueue(6);
	kolejka.enqueue(8);
	cout << "Stan kolejki: " << kolejka << endl;

	kolejka.dequeue();
	kolejka.dequeue();
	kolejka.dequeue();
	kolejka.dequeue();
	kolejka.dequeue();
	kolejka.dequeue();
	cout << "Stan kolejki: " << kolejka << endl;
	return 0;
}