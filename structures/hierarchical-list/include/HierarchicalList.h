#ifndef _HIERARCHICAL_LIST_
#define _HIERARCHICAL_LIST_

#include <cassert>
#include <iostream>
#include <memory>
#include <vector>
#include <compare>

/// <summary>
/// Список с пропусками
/// </summary>
template <class TValue>
class HierarchicalList {
public:
    class Iterator;

    // Определения типов для совместимости с STL.
    using value_type = TValue;
    using iterator = Iterator;
    using const_iterator = const Iterator;
    using pointer = value_type*;
    using reference = value_type&;
    using const_reference = const reference;
    using size_type = size_t;

protected:
    struct Node;
    using spNode = std::shared_ptr<Node>;
    using wpNode = std::weak_ptr<Node>;

    /// <summary>
    /// Структура-узел, содержит указатель.
    /// </summary>
    struct Node {
        value_type Value;

        wpNode Next;
        wpNode Down;

        Node(const reference Value, spNode Next = spNode(), spNode Down = spNode());
    };


    /// <summary>
    /// Длина списка
    /// </summary>
    size_type length;

    /// <summary>
    /// Начальный узел
    /// </summary>
    spNode Start;

    /// <summary>
    /// Слабый указатель на последний узел.
    /// (Узел, у которого нет узлов в полях Next и Down)
    /// </summary>
    wpNode End;
public:
    /// <summary>
    /// Класс-итератор
    /// </summary>
    class Iterator{
		std::shared_ptr<HierarchicalList> List;
		friend class HierarchicalList<value_type>;

		/// <summary>
		/// Текущий узел, на который указывает объект итератора
		/// </summary>
		spNode Node;
	public:
		/// <summary>
		/// Конструктор копирования
		/// </summary>
		/// <param name="it">Другой итератор</param>
		Iterator(const iterator& it);

		/// <summary>
		/// Конструктор-обыкновенный
		/// </summary>
		/// <param name="list">Указатель на список</param>
		/// <param name="node">Опционально. Указатель на узел, с которого начнётся итерация</param>
		Iterator(HierarchicalList& list, spNode node = spNode());

        /// <summary>
        /// Оператор присваивания.
        /// </summary>
        /// <param name="other">Другой итератор</param>
        /// <returns>Возвращает *this</returns>
        Iterator& operator=(const Iterator& other);

        /// <summary>
        /// При приобразовании к bool, фактически выполняется проверка на конец списка
        /// </summary>
        operator bool();

		/// <summary>
		/// Spaceship-оператор, обеспечивающий трехсторонне сравнение
		/// </summary>
		/// <param name="other">Другой итератор</param>
		/// <returns></returns>
		auto operator<=>(const iterator& other) const;

        /// <summary>
        /// Проверка равенства итераторов
        /// </summary>
        /// <param name="other">Другой итератор</param>
        /// <returns>true, если итератеры равны, иначе false</returns>
        bool operator==(const iterator& other) const;

        /// <summary>
        /// Префиксное смещение итератора вперед
        /// </summary>
        /// <returns>Возвращает *this</returns>
        iterator& operator++() const;

        /// <summary>
        /// Префиксное смещение итератора назад
        /// </summary>
        /// <returns>Возвращает *this</returns>
        iterator& operator--() const;

        /// <summary>
        /// Постфиксное смещение итератора вперед
        /// </summary>
        /// <returns>Возвращает *this</returns>
        iterator operator++(int) const;

        /// <summary>
        /// Постфиксное смещение итератора назад
        /// </summary>
        /// <returns>Возвращает *this</returns>
        iterator operator--(int) const;

        /// <summary>
        /// Происзвольное смещение итератора вперед
        /// </summary>
        /// <param name="n">Величина смещения</param>
        /// <returns>Возвращает *this</returns>
        iterator& operator+=(size_type n) const;

        /// <summary>
        /// Происзвольное смещение итератора назад
        /// </summary>
        /// <param name="n">Величина смещения</param>
        /// <returns>Возвращает *this</returns>
        iterator& operator-=(size_type n) const;

        /// <summary>
        /// Разыменование итератора
        /// </summary>
        /// <returns>Ссылка на данные, на которые указывает итератор</returns>
        reference operator*();

        /// <summary>
        /// Константное разыменование итератора
        /// </summary>
        /// <returns>Ссылка на данные, на которые указывает итератор</returns>
        const_reference operator*() const;
	};

    /// <summary>
    /// Конструктор-обыкновенный.
    /// Arr будет добавлен в один верхний уровень.
    /// </summary>
    /// <param name="Arr">Опционально. Указатель на массив данных, которые будут скопированны</param>
    /// <param name="ArrSize">Опционально (обязательно, при использовании Arr). Размер массива данных</param>
    HierarchicalList(pointer Arr = nullptr, size_type ArrSize = 0);

    /// <summary>
    /// Конструктор копирования
    /// </summary>
    /// <param name="other">Другой иерархический список</param>
    HierarchicalList(const HierarchicalList& other);

    /// <summary>
    /// Оператор присваивания.
    /// </summary>
    /// <param name="other">Другой иерархический список</param>
    /// <returns>Возвращает *this</returns>
    HierarchicalList& operator=(const HierarchicalList& other);

    /// <summary>
    /// Возвращает итератор произвольного доступа, указывающий на первый элемент в списке.
    /// </summary>
    /// <returns>Итератор произвольного доступа</returns>
    iterator begin() const;

    /// <summary>
    /// Возвращает итератор произвольного доступа, указывающий на последний элемент в списке.
    /// </summary>
    /// <returns>Итератор произвольного доступа</returns>
    iterator end() const;

    /// <summary>
    /// Возвращает итератор произвольного доступа, указывающий на найденный элемент в списке.
    /// </summary>
    /// <returns>Итератор произвольного доступа.</returns>
    iterator find(const reference value) const noexcept;

    /// <summary>
    /// Возвращает количество элементов в списке.
    /// </summary>
    /// <returns>Текущая длина списка.</returns>
    size_type size() const noexcept;

    /// <summary>
    /// Проверяет, пуст ли список.
    /// </summary>
    /// <returns>true значение, если список пуст. false значение, если список не пуст.</returns>
    bool empty() const noexcept;

    /// <summary>
    /// Очищает элементы вектора.
    /// </summary>
    void clear() const noexcept;

    /// <summary>
    /// Вставить новый элемент в список
    /// </summary>
    /// <param name="value">Значение для элемента списка</param>
    void insert(const reference value) noexcept;

    /// <summary>
    /// Удалить элемент по значению.
    /// Если элемента нет в списке, ничего не делать
    /// </summary>
    /// <param name="value">Элемент списка</param>
    void remove(const reference value) noexcept;

    /// <summary>
    /// Вывод списка в поток
    /// </summary>
    /// <param name="os">Поток вывода</param>
    /// <param name="list">Экземпляр списка</param>
    /// <returns>Поток вывода</returns>
    friend std::ostream& operator<<(std::ostream& os, HierarchicalList& list);
};

#include "../src/HierarchicalList.hpp"

#endif
