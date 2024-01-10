#include <iostream>
#include <initializer_list>
#include <iterator>

template <typename T> class StackBasedOnUnidirectionalList
{
public:
    // Конструктор по умолчанию
    StackBasedOnUnidirectionalList();

    // Конструктор копирования
    StackBasedOnUnidirectionalList(const StackBasedOnUnidirectionalList& other);

    // Конструктор перемещения
    StackBasedOnUnidirectionalList(StackBasedOnUnidirectionalList&& other);

    // Конструктор с использованием списка инициализации
    StackBasedOnUnidirectionalList(std::initializer_list<int> list);

    // Деструктор
    ~StackBasedOnUnidirectionalList();

    // Перегрузка оператора присваивания для копирования стека
    StackBasedOnUnidirectionalList& operator=(const StackBasedOnUnidirectionalList& other);

    // Перегрузка оператора присваивания для перемещения стека
    StackBasedOnUnidirectionalList& operator=(StackBasedOnUnidirectionalList&& other);

    // Перегрузка оператора присваивания для списка инициализации
    StackBasedOnUnidirectionalList& operator=(std::initializer_list<int> ilist);

    template <typename T>
    friend std::ostream& operator<<(std::ostream& stream, const StackBasedOnUnidirectionalList<T>& _object)
    {
        if (_object.head == nullptr) return stream << "Stack is empty";
        stack* temp = _object.head;
        int size = _object.GetSize();
        for (int i = 0; i < size; i++)
        {
            stream << temp->value << " ";
            temp = temp->index;
        }
        return stream;
    }

    int GetSize() const;
    void InsertAt(int value, int index);
    int RemoveAt(int index);
    bool Push(const T& element);
    bool Pop(T& element);
    bool Peek(T& element);


private:
    struct stack// Структура для хранения элементов стека
    {
        T value;//Поле для хранения значения элемента стека
        stack* index; // Поле для хранения следующего элемента
    };
    stack* head; // указатель, хранящий адрес головы стека
    int size; //Текущий размер стека
};

template <typename T>
StackBasedOnUnidirectionalList<T>::StackBasedOnUnidirectionalList()
{
    head = nullptr;
    size = 0;
}


template <typename T>
StackBasedOnUnidirectionalList<T>::~StackBasedOnUnidirectionalList()
{
    if (head == nullptr) return;
    while (this->GetSize() > 0)
    {
        this->Pop(head->value);
    }
    head = nullptr;
}

template <typename T>
StackBasedOnUnidirectionalList<T>::StackBasedOnUnidirectionalList(const StackBasedOnUnidirectionalList& other)
: head(nullptr), size(0) {
        *this = other;
}

template <typename T>
StackBasedOnUnidirectionalList<T>::StackBasedOnUnidirectionalList(StackBasedOnUnidirectionalList&& other)
{
    if (other.head == nullptr)
    {
        head = nullptr;
        return;
    }
    head = other.head;
    other.head = nullptr;

}

template <typename T>
StackBasedOnUnidirectionalList<T>::StackBasedOnUnidirectionalList(std::initializer_list<int> ilist)
{

    for (const auto& element : ilist)
    {
        this->Push(element);
    }
}

template <typename T>
int StackBasedOnUnidirectionalList<T>::GetSize() const
{
    return size;
}


// Перегрузка оператора присваивания для копирования стека
template <typename T>
StackBasedOnUnidirectionalList<T>& StackBasedOnUnidirectionalList<T>::operator=(const StackBasedOnUnidirectionalList& other)
{
    if (this == &other || other.head == nullptr) return *this;
    int pop;
    for (int size = this->GetSize(); size > 0; size--)
        this->Pop(pop);
    stack* temp = other.head;
    int size = other.GetSize();
    for(int i = 0; i<size; i++)
    {
        this->Push(temp->value);
        temp = temp->index;
    }
    return *this;

}

// Перегрузка оператора присваивания для перемещения стека
template <typename T>
StackBasedOnUnidirectionalList<T>& StackBasedOnUnidirectionalList<T>::operator=(StackBasedOnUnidirectionalList&& other)
{
    if (this == &other || other.head == NULL) return *this;
    head = other.head;
    other.head = NULL;
    return *this;
}

// Перегрузка оператора присваивания для списка инициализации
template <typename T>
StackBasedOnUnidirectionalList<T>& StackBasedOnUnidirectionalList<T>::operator=(std::initializer_list<int> ilist)
{
    int temp;
    for (int size = this->GetSize(); size > 0; size--)
        this->Pop(temp);
    for (const auto& element : ilist)
    {
        this->Push(element);
    }
    return *this;
}




// Метод для добавления элемента в конец стека
template <typename T>
bool StackBasedOnUnidirectionalList<T>::Push(const T& element)
{

    try {
        size++;
        stack* temp = head;
        head = new(stack);
        head->index = temp;
        head->value = element;
        return true;
    }

    catch (...)
    {
        return false;
    }
}

// Метод для удаления элемента из конца стека
template <typename T>
bool StackBasedOnUnidirectionalList<T>::Pop(T& element)
{
    if (size == 0)
        return false;

    else {
        stack* temp = head;
        element = head->value;
        head = head->index;
        delete temp;
        size--;
        return true;
    }
}

// Метод для просмотра элемента в конце стека, не удаляя его
template <typename T>
bool StackBasedOnUnidirectionalList<T>::Peek(T& element)
{
    if (size > 0)
    {
        element = head->value;
        return true;
    }
    else
        return false;
}
template<typename T>
void StackBasedOnUnidirectionalList<T>::InsertAt(int _value, int _index)
{
    int size = this->GetSize() + 1;
    StackBasedOnUnidirectionalList<int>* temp_obj{ std::move(this) };
    int tmp;
    if (_index <= size)
        for (int i = size; i > 0; i--)
        {
            temp_obj->Pop(tmp);
            this->Push(tmp);
            if (_index == i)
            {
                this->Push(_value);
                continue;
            }
        }
}

template<typename T>
int StackBasedOnUnidirectionalList<T>::RemoveAt(int _index)
{
    int size = this->GetSize();
    StackBasedOnUnidirectionalList<int>* temp_obj{ std::move(this) };
    int removedElement{};
    int tmp;
    if (_index <= size)
        for (int i = 0; i < size; i++)
        {
            temp_obj->Pop(tmp);
            this->Push(tmp);
            if (_index == i)
            {
                temp_obj->Pop(removedElement);
                continue;
            }
            
        }
    return removedElement;
}

int main()
{
    // Тестирование конструкторов
    StackBasedOnUnidirectionalList<int> stack1;  // Конструктор по умолчанию
    StackBasedOnUnidirectionalList<int> stack2 = { 1, 2, 3, 4, 5 };  // Конструктор с использованием списка инициализации
    StackBasedOnUnidirectionalList<int> stack2copy{ stack2 };
    StackBasedOnUnidirectionalList<int> stack3;
    // Тестирование оператора присваивания для списка инициализации
    stack1 = { 10, 20, 30 };
    stack3 = stack2;
    // Тестирование методов Push, Pop, Peek
    stack1.Push(100);
    stack1.Push(200);
    stack1.Push(300);

    int poppedElement;
    if (stack1.Pop(poppedElement))
        std::cout << "Popped element: " << poppedElement << std::endl;
    else
        std::cout << "Stack is empty, cannot pop." << std::endl;

    int peekedElement;
    if (stack1.Peek(peekedElement))
        std::cout << "Peeked element: " << peekedElement << std::endl;
    else
        std::cout << "Stack is empty, cannot peek." << std::endl;

    // Вывод размеров очередей
    std::cout << "Size of stack1: " << stack1.GetSize() << std::endl;
    std::cout << "Size of stack2: " << stack2.GetSize() << std::endl;
    //Вывод всех элеметов стека
    std::cout << "stack1: " << stack1 << std::endl;
    std::cout << "stack2: " << stack2 << std::endl;
    std::cout << "stack2copy: " << stack2copy << std::endl;
    std::cout << "InsertAt >> RemoveAt:" << std::endl;
    std::cout << "All elements of stack1 before InsertAt(1): " << std::endl;
    std::cout << stack1 << std::endl;
    std::cout << "All elements of stack1 after InsertAt(1000, 1): " << std::endl;
    stack1.InsertAt(1000, 1);
    std::cout << stack1<< std::endl;
    std::cout << "All elements of stack1 after RemoveAt(2): " << std::endl;
    stack1.RemoveAt(2);
    std::cout << stack1 << std::endl;
    return 0;
}
