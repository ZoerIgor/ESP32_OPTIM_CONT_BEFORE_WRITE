#pragma once
#ifndef _MAIN_
    #define _MAIN_
    #include <Arduino.h>
    #include <list>
    #include <iterator>
    using namespace std;

    template <typename T> void ConvertStaticArrayToList(const T staticArray[], const size_t sizeArray, list <T> &list);
    template <typename T> void ConvertStaticArrayToList(const T staticArray[], const size_t sizeArray, const T terminationSymbol, list <T> &list);
    template <typename T> bool ConvertListToStaticArray(list <T> list, T staticArray[], const size_t sizeArray);
    template <typename T> bool ConvertListToStaticArray(list <T> list, T staticArray[], const size_t sizeArray, const T terminationSymbol);
    template <typename T> size_t LinkingLists(bool emplaceFront, list <T> &generalList, list <T> attachList);
    template <typename T> size_t LinkingLists(list <T> &generalList, list <T> beginList, list <T> endList);
    template <typename T> size_t LinkingLists(list <T> &generalList, list <T> beginList, T separator, list <T> endList);
    template <typename T> void InsertValueInEdgesList(list <T> &list, const T value, const bool end);
    template <typename T> bool SplitList(list <T> generalList, const T separator, bool eraseSeparator, list <T> &beginList, list <T> &endList);
    template <typename T> bool LinkingListsWithSubstitution(const size_t maxLenghtGeneralList, list <T> &generalList, list <T> attachList);
    template <typename T> bool LinkingListsWithSubstitution(const size_t maxLenghtGeneralList, list <T> &generalList, const T code, list <T> attachList);
    template <typename T> bool EracePartFromList(list <T> &list, const T code);
    template <typename T> bool EracePartFromList(list <T> &list, const T code, const T lenght);
    template <typename T> void CodeOffset(list <T> &list, T firstCode);
    template <typename T> void CodeOffset(list <T> &generalList, list <T> &offsetCodes, const T lenght);
    template <typename T> T GetLastCodeFromList(list <T> list, const T beginCode, const T endCode);
    template <typename T> T GetNextCodeFromList(bool add, T lastCode, const T beginCode, const T endCode);
    template <typename T> bool FindCodeInList(list <T> list, const T code);
    template <typename T> size_t GetRangeSize(list <T> list, T code);
    template <typename T> size_t CopyPartFromList(list <T> originalList, list <T> &copyList, const T code);
    template <typename T> size_t CopyPartFromList(list <T> originalList, list <T> &copyList, const T code, const T lenght);
    template <typename T> size_t ExtractValidValuesFromList(list <T> originalList, list <T> &copyList, const T minValue, const T maxValue);

    template <typename T> class CodeInList
    {
        public:
            CodeInList(list <T> mainList, const T beginCode, const T endCode);
            void setCounter(list <T> mainList);
            T getCounter();
            T getCounter(bool increment);
            T getNext();
            T getIncrement();
            T getDecrement();
            bool setIncrement();
            bool setDecrement();
        private:
            T _beginCode, _endCode;
            T _counter;
    };
#endif