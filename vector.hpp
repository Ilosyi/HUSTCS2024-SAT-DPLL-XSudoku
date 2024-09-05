#pragma once
#include <algorithm> // for std::copy
#include <stdexcept> // for std::out_of_range

template <class T>
class vector {
public:
    // ����
    T* data;
    // ��С
    int Size;
    // ����
    int capacity;

    // ���캯��
    vector() : Size(0), capacity(1), data(new T[1]) {}

    // ��������
    ~vector() {
        delete[] data;
    }
	//���ι��캯��(��ʼ����С,Ԫ��)
	vector(int n, T t) : Size(n), capacity(n), data(new T[n]) {
		for (int i = 0; i < n; i++) {
			data[i] = t;
		}
	}
    // �������캯��
    vector(const vector& v) : Size(v.Size), capacity(v.capacity), data(new T[v.capacity]) {
        std::copy(v.data, v.data + v.Size, data);
    }

    // ��ֵ�����
    vector& operator=(const vector& v) {
        if (this != &v) {
            T* new_data = new T[v.capacity];
            std::copy(v.data, v.data + v.Size, new_data);
            delete[] data;
            data = new_data;
            Size = v.Size;
            capacity = v.capacity;
        }
        return *this;
    }

    // ���Ԫ��
    void push_back(T t) {
        if (Size == capacity) {
            resize(capacity * 2);
        }
        data[Size++] = t; // ���Ԫ��
    }

    // ɾ��Ԫ��
	void pop_back() // ɾ�����һ��Ԫ��
    {
        if (Size > 0) Size--;
    }

    // ���ش�С
    int size() const {
        return Size;
    }

    // ����Ԫ�أ��� const �汾��
    T& operator[](int index) {
        if (index < 0 || index >= Size) {
			throw std::out_of_range("Index out of range");//�׳��쳣
        }
        return data[index];
    }

    // ����Ԫ�أ�const �汾��
    const T& operator[](int index) const
    {
        if (index < 0 || index >= Size) {
			throw std::out_of_range("Index out of range");//�׳��쳣
        }
        return data[index];
    }
    //�ж��Ƿ�Ϊ��
	bool empty() const
	{
		return Size == 0;
	}
	void clear() {
		Size = 0;
	}
    // ��������
    class iterator {
    public:
        T* ptr;

        iterator(T* p) : ptr(p) {}

        T& operator*() const { return *ptr; }
        T* operator->() const { return ptr; }

        iterator& operator++() { ++ptr; return *this; }
        iterator operator++(int) { iterator tmp = *this; ++ptr; return tmp; }

        iterator& operator--() { --ptr; return *this; }
        iterator operator--(int) { iterator tmp = *this; --ptr; return tmp; }

        bool operator==(const iterator& other) const { return ptr == other.ptr; }
        bool operator!=(const iterator& other) const { return ptr != other.ptr; }
    };

    // ������������
    class const_iterator {
    public:
        const T* ptr;

        const_iterator(const T* p) : ptr(p) {}

        const T& operator*() const { return *ptr; }
        const T* operator->() const { return ptr; }

        const_iterator& operator++() { ++ptr; return *this; }
        const_iterator operator++(int) { const_iterator tmp = *this; ++ptr; return tmp; }

        const_iterator& operator--() { --ptr; return *this; }
        const_iterator operator--(int) { const_iterator tmp = *this; --ptr; return tmp; }

        bool operator==(const const_iterator& other) const { return ptr == other.ptr; }
        bool operator!=(const const_iterator& other) const { return ptr != other.ptr; }
    };

    // ���ص������Ŀ�ʼ
    iterator begin() { return iterator(data); }

    // ���ص������Ľ���
    iterator end() { return iterator(data + Size); }

    // ���س����������Ŀ�ʼ
    const_iterator begin() const { return const_iterator(data); }

    // ���س����������Ľ���
    const_iterator end() const { return const_iterator(data + Size); }

    // ��������
    void resize(int new_capacity) {
		T* new_data = new T[new_capacity];//�½�һ������
		std::copy(data, data + Size, new_data);//��������
		delete[] data;//ɾ��ԭ��������
        data = new_data;
        capacity = new_capacity;
    }
};

