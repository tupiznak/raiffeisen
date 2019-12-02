# Тестовое задание
Был написан класс MyHashMap, который представляет собой хэш-таблицу с выделением памяти только при переполнении существующего массива элементов. Размер массива с каждым переполнением увеличивается в два раза, что позволяет не перегружать запись в кучу при большом количестве данных.

Было принято решение ввести дополнительную структуру MyHash с обязательным полем value для того, чтобы хэш-функция могла иметь произвольный тип, т.к. в условии о типе хэш-функции не было сказано. Это позволяет иметь хэши как в виде строки, так и, например, int (пример использования этих двух типов в main.cpp строка 67 - тип char*, строка 68 - тип size_t).

Для ускорения всех операций, вместо обычного заполнения массива, была использована концепция бинарного дерева, что позволило увеличить скорости операций в лучшем случае в log(n) раз. В отличие от классического способа реализации алгоритма, который оперирует с произвольной кучей, данный алгоритм располагает все элементы в адресном пространстве массива arrNodes. Для этого было необходимо ввести ссылку (индекс) на родительский элемент.
