#include "main.h"
#define ARRAY_SIZE 20
#define TERMINATION_SYMBOL 255
int staticArray[ARRAY_SIZE] = {1,2,3,4,5,6,7,8,9,10};
list <byte> mainList = {103,193,224,15,6,7,105,194,225,20,4,8,106,135,163,17,4,5};
list <byte> firstList = {5,4,2,2,2,2,2};
list <byte> secondtList = {107,132,226,12,8,7};
byte miniNumber = 103;
#define MAX_SIZE 30
#define BEGIN_CODE 40
#define END_CODE 45

template <typename T> void ConvertStaticArrayToList(const T staticArray[], const size_t sizeArray, list <T> &list)
{
    list.clear();
    for (size_t i = 0; i < sizeArray; i++)
    {
        list.emplace_back(staticArray[i]);
    }
}
template <typename T> void ConvertStaticArrayToList(const T staticArray[], const size_t sizeArray, const T terminationSymbol, list <T> &list)
{
    list.clear();
    for (size_t i = 0; i < sizeArray; i++)
    {
        if (staticArray[i] != terminationSymbol)
        {
            list.emplace_back(staticArray[i]);
        }
        else
        {
            break;
        }
    }
}
template <typename T> bool ConvertListToStaticArray(list <T> list, T staticArray[], const size_t sizeArray)
{
    if (list.size() > sizeArray)
    {
        return false;
    }
    size_t counter = 0;
    for (auto i = list.begin(); i != list.end(); i++)
    {
        staticArray[counter++] = *i;
    }
    return true;
}
template <typename T> bool ConvertListToStaticArray(list <T> list, T staticArray[], const size_t sizeArray, const T terminationSymbol)
{
    if (list.size() > sizeArray)
    {
        return false;
    }
    size_t counter = 0;
    for (auto i = list.begin(); i != list.end(); i++)
    {
        staticArray[counter++] = *i;
    }
    while (counter < sizeArray)
    {
        staticArray[counter++] = terminationSymbol;
    }
    return true;
}
template <typename T> size_t LinkingLists(bool emplaceFront, list <T> &generalList, list <T> attachList)
{
    if (emplaceFront)
    {
        for (auto i = attachList.rbegin(); i != attachList.rend(); i++)
        {
            generalList.emplace_front(*i);
        }
    }
    else
    {
        for (auto i = attachList.begin(); i != attachList.end(); i++)
        {
            generalList.emplace_back(*i);
        }
    }
    return generalList.size();
}
template <typename T> size_t LinkingLists(list <T> &generalList, list <T> beginList, list <T> endList)
{
    generalList = beginList;
    for (auto i = endList.begin(); i != endList.end(); i++)
    {
        generalList.emplace_back(*i);
    }
    return generalList.size();
}
template <typename T> size_t LinkingLists(list <T> &generalList, list <T> beginList, T separator, list <T> endList)
{
    generalList = beginList;
    generalList.emplace_back(separator);
    for (auto i = endList.begin(); i != endList.end(); i++)
    {
        generalList.emplace_back(*i);
    }
    return generalList.size();
}
template <typename T> void InsertValueInEdgesList(list <T> &list, const T value, const bool end)
{
    if (end)
    {
        list.emplace_back(value);
    }
    else
    {
        list.emplace_front(value);
    }
}
template <typename T> bool SplitList(list <T> generalList, const T separator, bool eraseSeparator, list <T> &beginList, list <T> &endList)
{
    typename list <T>::iterator generalIt = generalList.begin();
    size_t beforeSeparator = 0;
    size_t afterSeparator = 0;
    size_t generalSize = generalList.size();
    while (*generalIt != separator) // Поиск разделителя
    {
        generalIt++;
        if (++beforeSeparator == generalSize)
        {
            break;
        }
    }
    if (beforeSeparator == generalSize) // Разделитель не найден
    {
        return false;
    }
    generalIt = generalList.begin();
    beginList.clear();
    endList.clear();
    while (afterSeparator < beforeSeparator) // Первый список
    {
        afterSeparator++;
        beginList.emplace_back(*generalIt++);
    }
    if (eraseSeparator)
    {
        generalIt++;
        afterSeparator++;
    }
    while (afterSeparator < generalSize) // Второй список
    {
        afterSeparator++;
        endList.emplace_back(*generalIt++);
    }
    return true;
}
template <typename T> bool LinkingListsWithSubstitution(const size_t maxLenghtGeneralList, list <T> &generalList, list <T> attachList)
{
    typename list <T>::iterator generalIt = generalList.begin();
    typename list <T>::iterator attachIt = attachList.begin();
    size_t attachSize = attachList.size();
    size_t counter = 0;
    size_t partCounter = 0;
    size_t offset = 0;
    bool notFound = true;
    bool nextCode = false;
    for (auto i = generalList.begin(); i != generalList.end(); i++)
    {
        if (partCounter++ == 0)
        {
            if (*i == *attachIt)
            {
                notFound = false;
                offset = counter;
                advance(generalIt, offset);
            }
            if (*i > *attachIt && !nextCode)
            {
                if (notFound)
                {
                    offset = counter;
                    advance(generalIt, offset);
                }
                nextCode = true;
            }
        }
        if (partCounter == attachSize)
        {
            partCounter = 0;
        }
        counter++;
    }
    if (!notFound) // Предварительное удаление старого присоединенного массива из основного
    {
        typename list <T>::iterator i = generalIt;
        advance(i, attachSize);
        generalList.erase(generalIt, i);
        advance(generalIt, offset);
    }
    // Присоединение массива
    if (generalList.size() + attachSize <= maxLenghtGeneralList || maxLenghtGeneralList == 0) // Проверка превышения длины основного массива
    {
        if (!nextCode) // Присоединение нового массива в конец основного
        {
            for (auto i = attachList.begin(); i != attachList.end(); i++)
            {
                generalList.emplace_back(*i);
            }
        }
        else //Вставляем новый массив на порядковое место
        {
            if(offset == 0)
            {
                generalIt = generalList.begin();
            }
            for (auto i = attachList.begin(); i != attachList.end(); i++)
            {
                generalList.insert(generalIt, *i);
            }
        }
        return true;
    }
    return false; // Сумма массивов превосходит максимальную длинну основного массива
}
template <typename T> bool LinkingListsWithSubstitution(const size_t maxLenghtGeneralList, list <T> &generalList, const T code, list <T> attachList)
{
    typename list <T>::iterator generalIt = generalList.begin();
    typename list <T>::iterator attachIt = attachList.begin();
    if (code != 0)
    {
        attachList.insert(attachIt, code);
    }
    size_t generalSize = generalList.size();
    size_t attachSize = attachList.size();
    size_t beginPart = 0;
    size_t endPart = 0;
    size_t maxFindNumber = 0;
    while (*generalIt <= code && endPart < generalSize) // Поиск позиции по возростанию для присоединяемых кодового номера и массива
    {
        if (*generalIt == code)
        {
            beginPart = endPart;
        }
        if(maxFindNumber < *generalIt)
        {
            maxFindNumber = *generalIt;
        }
        generalIt++;
        endPart++;
    }
    if (endPart == generalSize) // Присоединение нового массива в конец основного
    {
        if (generalSize + attachSize <= maxLenghtGeneralList || maxLenghtGeneralList == 0) // Проверка превышения длины основного массива
        {
            for (auto i = attachList.begin();i != attachList.end(); i++)
            {
                generalList.emplace_back(*i);
            }
            return true;
        }
        else
        {
            return false; // Сумма массивов превосходит максимальную длинну основного массива
        }
    }
    else if (*--generalIt <= code) // Добавление нового массива в начало или в середину
    {
        if (generalSize - (endPart - beginPart) + attachSize <= maxLenghtGeneralList || maxLenghtGeneralList == 0) // Проверка превышения длины основного массива
        {
            generalIt++;
            if (maxFindNumber == code) // Присоединяемый массив уже существует
            {
                typename list <T>::iterator i = generalList.begin();
                advance(i, beginPart);
                for (; i != generalIt; i++) // Удаляем область старого массива
                {
                    generalList.erase(i);
                }
            }
            if (maxFindNumber == 0) // Указываем начало основного массива в качестве начала вставляемого массива
            {
                generalIt = generalList.begin();
            }
            for (auto i = attachList.begin(); i != attachList.end(); i++) //Вставляем новый массив на порядковое место
            {
                generalList.insert(generalIt, *i);
            }
            return true;
        }
        else
        {
            return false; // Сумма массивов превосходит максимальную длинну основного массива
        }
    }
    return false;
}
template <typename T> bool EracePartFromList(list <T> &list, const T code)
{
    size_t counter = 0;
    size_t beginPart = 0;
    size_t endPart = 0;
    bool beginFound = false;
    bool endFound = false;
    for (auto i = list.begin(); i != list.end(); i++) // Поиск кодового номера в массиве
    {
        if (*i == code)
        {
            beginFound = true;
            beginPart = counter;
        }
        if(*i > code && !endFound)
        {
            endPart = counter;
            endFound = true;
        }
        counter++;
    }
    if (beginFound && !endFound)
    {
        endPart = list.size();
    }
    if (beginFound) // Кодовый номер найден
    {
        typename list <T>::iterator iBegin = list.begin();
        advance(iBegin, beginPart);
        typename list <T>::iterator iEnd = list.begin();
        advance(iEnd, endPart);
        for (; iBegin != iEnd; iBegin++) // Удаляем область массива
        {
            list.erase(iBegin);
        }
        return true;
    }
    return false; // Кодовый номер не найден
}
template <typename T> bool EracePartFromList(list <T> &list, const T code, const T lenght)
{
    typename list <T>::iterator i = list.begin();
    bool find = false;
    for (; i != list.end(); i++) // Поиск кодового номера в массиве
    {
        if (*i == code)
        {   
            find = true;
            break;
        }
    }
    if (find)
    {
        for (auto n = 0; n < lenght; n++)
        {
            list.erase(i++);
        }
        return true;
    }
    return false;
}
template <typename T> void CodeOffset(list <T> &list, T firstCode)
{
    typename list <T>::iterator i = list.begin();
    if (*i != firstCode)
    {
        *i = firstCode;
    }
    T counter = firstCode;
    for (; i != list.end(); i++)
    {
        if (*i > counter)
        {
            *i = ++counter;
        }
    }
}
template <typename T> void CodeOffset(list <T> &generalList, list <T> &offsetCodes, const T lenght)
{
    typename list <T>::iterator itGen = generalList.begin();
    typename list <T>::iterator i = offsetCodes.begin();
    size_t offsetSize = offsetCodes.size();
    bool toBegin = false;
    if (*itGen < *i)
    {
        advance(itGen, lenght);
        toBegin = true;
    }
    while (itGen != generalList.end())
    {
        for (auto itOff = offsetCodes.begin(); itOff != offsetCodes.end(); itOff++)
        {
            if (*itGen >= *itOff)
            {
                *itGen = *itOff;
                *itOff = *itOff + 1;
            }
            itGen++;
        }
        advance(itGen, lenght - offsetSize);
    }
    if (toBegin)
    {
        itGen = generalList.begin();
        for (auto itOff = offsetCodes.begin(); itOff != offsetCodes.end(); itOff++)
        {
            if (*itGen > *itOff)
            {
                *itGen = *itOff;
            }
            itGen++;
        }
    }
    
}
template <typename T> T GetLastCodeFromList(list <T> list, const T beginCode, const T endCode)
{
    T value = 0;
    for (auto i = list.begin(); i != list.end(); i++)
    {
        if (*i >= beginCode && *i <= endCode && *i > value)
        {
            value = *i;
        }
    }
    if (value == 0)
    {
        return beginCode - 1;
    }
    return value;
}
template <typename T> T GetNextCodeFromList(bool add, T lastCode, const T beginCode, const T endCode)
{
    if (add)
    {
        if (++lastCode > endCode)
        {
            return endCode;
        }
        return lastCode;
    }
    if (--lastCode < beginCode)
    {
        return beginCode;
    }
    return lastCode;
}
template <typename T> bool FindCodeInList(list <T> list, const T code)
{
    for (auto i = list.begin(); i != list.end(); i++)
    {
        if (*i == code)
        {
            return true;
        }
    }
    return false;
}
template <typename T> size_t GetRangeSize(list <T> list, T code)
{
    typename list <T>::iterator i = list.begin();
    for (; i != list.end(); i++) // Поиск кода
    {
        if (*i == code)
        {
            break;
        }
    }
    if (i != list.end()) // Код найден
    {
        code++;
        size_t counter = 0;
        for (; i != list.end(); i++) // Подсчет диаппазона
        {
            if (*i >= code)
            {
                break;
            }
            counter++;
        }
        return counter;
    }
    return 0; // Код не найден
}
template <typename T> size_t CopyPartFromList(list <T> originalList, list <T> &copyList, const T code)
{
    typename list <T>::iterator i = originalList.begin();
    for (; i != originalList.end(); i++)
    {
        if (*i == code)
        {
            i++;
            break;
        }
    }
    for (; i != originalList.end(); i++)
    {
        if (*i > code)
        {
            break;
        }
        copyList.emplace_back(*i);
    }
    return copyList.size();
}
template <typename T> size_t CopyPartFromList(list <T> originalList, list <T> &copyList, const T code, const T lenght)
{
    typename list <T>::iterator i = originalList.begin();
    for (; i != originalList.end(); i++)
    {
        if (*i == code)
        {
            i++;
            break;
        }
    }
    for (T n = 0; n < lenght; n++)
    {
        copyList.emplace_back(*i++);
    }
    return copyList.size();
}
template <typename T> size_t ExtractValidValuesFromList(list <T> originalList, list <T> &copyList, const T minValue, const T maxValue)
{
    for (auto i = originalList.begin(); i != originalList.end(); i++)
    {
        if (*i >= minValue && *i <= maxValue)
        {
            copyList.emplace_back(*i);
        }
    }
    return copyList.size();
}

template <typename T> CodeInList<T>::CodeInList(list <T> mainList, const T beginCode, const T endCode)
{
    _beginCode = beginCode;
    _endCode = endCode;
    _counter = 0;
    for (auto i = mainList.begin(); i != mainList.end(); i++)
    {
        if (*i >= _beginCode && *i <= _endCode)
        {
            _counter++;
        }
    }
}
template <typename T> void CodeInList<T>::setCounter(list <T> mainList)
{
    for (auto i = mainList.begin(); i != mainList.end(); i++)
    {
        if (*i >= _beginCode && *i <= _endCode)
        {
            _counter++;
        }
    }
}
template <typename T> T CodeInList<T>::getCounter()
{
    return _beginCode + _counter;
}
template <typename T> T CodeInList<T>::getCounter(bool increment)
{
    if (increment)
    {
        if (_counter == _endCode)
        {
            return _endCode;
        }
        else
        {
            return _beginCode + _counter++;
        }
    }
    else
    {
        if (_counter <= _beginCode)
        {
            return _beginCode;
        }
        else
        {
            return _beginCode + _counter--;
        }
    }
}
template <typename T> T CodeInList<T>::getNext()
{
    return _beginCode + _counter + 1;
}
template <typename T> T CodeInList<T>::getIncrement()
{
    if (_counter == _endCode)
    {
        return _endCode;
    }
    else
    {
        return _beginCode + _counter++;
    }
}
template <typename T> T CodeInList<T>::getDecrement()
{
    if (_counter <= _beginCode)
    {
        return _beginCode;
    }
    else
    {
        return _beginCode + _counter--;
    }
}
template <typename T> bool CodeInList<T>::setIncrement()
{
    if (_counter == _endCode)
    {
        return false;
    }
    _counter++;
    return true;
}
template <typename T> bool CodeInList<T>::setDecrement()
{
    if (_counter == _beginCode)
    {
        return false;
    }
    _counter--;
    return true;
}

const byte maxSizeArhive = 200;
byte arhiveArray[maxSizeArhive] = {101,193,224,15,6,7,102,194,225,20,4,8,103,131,163,17,4,5,255,193,3,4,5,6,194,3,5,6,4,8,9,5,3,224,6,5,4,3,225,3,6,5,4,1,2,5,7};
list <byte> arhiveList;
list <byte> descriptionCatalog;
list <byte> catalogUserProg;
list <byte> catalogBuildProg;
list <byte> headerUserProg;
list <String> headerBuildProg;
list <byte> description;
list <byte> ampProg;
list <byte> speedProg;
byte progCode;
byte ampCode;
byte speedCode;
byte workTime;
byte ampLimit;
byte speedLimit;
#define WORK_TIME 15;
#define AMP_LIMIT 6;
#define SPEED_LIMIT 6;
const byte PROG_NUMBER_DEF = 100;
const byte PROG_NUMBER_BEG = 101;
const byte PROG_NUMBER_END = 130;
const byte BUILD_AMP_BEG = 131;
const byte BUILD_AMP_END = 161;
const byte BUILD_SPEED_BEG = 162;
const byte BUILD_SPEED_END = 192;
const byte USER_AMP_BEG = 193;
const byte USER_AMP_END = 223;
const byte USER_SPEED_BEG = 224;
const byte USER_SPEED_END = 254;
const byte NUL = 0;
const byte SEPARATOR = 255;
const byte CODE_LENGTH = 5;
const byte DESCRIPTION_LENGTH = CODE_LENGTH + 1;
CodeInList <byte> UserProgCode(descriptionCatalog, PROG_NUMBER_BEG, PROG_NUMBER_END);
CodeInList <byte> UserAmpCode(catalogUserProg, USER_AMP_BEG, USER_AMP_END);
CodeInList <byte> UserSpeedCode(catalogUserProg, USER_SPEED_BEG, USER_SPEED_END);
CodeInList <byte> BuildAmpCode(catalogBuildProg, BUILD_AMP_BEG, BUILD_AMP_END);
CodeInList <byte> BuildSpeedCode(catalogBuildProg, BUILD_SPEED_BEG, BUILD_SPEED_END);

void CreatCodeInLists()
{
    UserProgCode.setCounter(descriptionCatalog);
    UserAmpCode.setCounter(catalogUserProg);
    UserSpeedCode.setCounter(catalogUserProg);
    BuildAmpCode.setCounter(catalogBuildProg);
    BuildSpeedCode.setCounter(catalogBuildProg);
}
void CreatBuildProgramm()
{
    headerBuildProg.emplace_back("Постоянная");
    ampProg = {9};
    LinkingListsWithSubstitution(maxSizeArhive, catalogBuildProg, BuildAmpCode.getCounter(true), ampProg);
    headerBuildProg.emplace_back("Возростающая");
    ampProg = {1,2,3,4,5,6,7,8,9};
    LinkingListsWithSubstitution(maxSizeArhive, catalogBuildProg, BuildAmpCode.getCounter(true), ampProg);
    headerBuildProg.emplace_back("Убывающая");
    ampProg = {9,8,7,6,5,4,3,2,1};
    LinkingListsWithSubstitution(maxSizeArhive, catalogBuildProg, BuildAmpCode.getCounter(true), ampProg);
    headerBuildProg.emplace_back("Пиковая");
    ampProg = {1,3,5,7,9,7,5,3,1};
    LinkingListsWithSubstitution(maxSizeArhive, catalogBuildProg, BuildAmpCode.getCounter(true), ampProg);
    headerBuildProg.emplace_back("Пилообразная");
    ampProg = {3,7,3,7,3,7,3,7,3,7};
    LinkingListsWithSubstitution(maxSizeArhive, catalogBuildProg, BuildAmpCode.getCounter(true), ampProg);
    headerBuildProg.emplace_back("Постоянная");
    speedProg = {9};
    LinkingListsWithSubstitution(maxSizeArhive, catalogBuildProg, BuildSpeedCode.getCounter(true), speedProg);
    headerBuildProg.emplace_back("Возростающая");
    speedProg = {1,2,3,4,5,6,7,8,9};
    LinkingListsWithSubstitution(maxSizeArhive, catalogBuildProg, BuildSpeedCode.getCounter(true), speedProg);
    headerBuildProg.emplace_back("Убывающая");
    speedProg = {9,8,7,6,5,4,3,2,1};
    LinkingListsWithSubstitution(maxSizeArhive, catalogBuildProg, BuildSpeedCode.getCounter(true), speedProg);
    headerBuildProg.emplace_back("Пиковая");
    speedProg = {1,3,5,7,9,7,5,3,1};
    LinkingListsWithSubstitution(maxSizeArhive, catalogBuildProg, BuildSpeedCode.getCounter(true), speedProg);
    headerBuildProg.emplace_back("Пилообразная");
    speedProg = {3,7,3,7,3,7,3,7,3,7};
    LinkingListsWithSubstitution(maxSizeArhive, catalogBuildProg, BuildSpeedCode.getCounter(true), speedProg);
}
void ExtractArhive()
{
    ConvertStaticArrayToList(arhiveArray,maxSizeArhive, NUL, arhiveList);
    SplitList(arhiveList, SEPARATOR, true, descriptionCatalog, catalogUserProg);
}
bool CheckProgramm(byte code)
{
    if (code != PROG_NUMBER_DEF)
    {
        return true;
    }
    list <byte>::iterator i = descriptionCatalog.begin();
    if (*i == PROG_NUMBER_DEF)
    {
        return true;
    }
    return false;
}
void DefaultProgramm()
{
    ampProg.clear();
    CopyPartFromList(catalogBuildProg, ampProg, BUILD_AMP_BEG);
    speedProg.clear();
    CopyPartFromList(catalogBuildProg, speedProg, BUILD_SPEED_BEG);
    workTime = WORK_TIME;
    ampLimit = AMP_LIMIT;
    speedLimit = SPEED_LIMIT;
}
bool ExtractProgramm(const byte code)
{
    description.clear();
    CopyPartFromList(descriptionCatalog, description, code, CODE_LENGTH);
    list <byte>::iterator i = description.begin();
    ampProg.clear();
    if (FindCodeInList(catalogBuildProg, *i))
    {
        CopyPartFromList(catalogBuildProg, ampProg, *i);
    }
    else if (FindCodeInList(catalogUserProg, *i))
    {
        CopyPartFromList(catalogUserProg, ampProg, *i);
    }
    else
    {
        return false; // + Код ошибки
    }
    speedProg.clear();
    i++;
    if (FindCodeInList(catalogBuildProg, *i))
    {
        CopyPartFromList(catalogBuildProg, speedProg, *i);
    }
    else if (FindCodeInList(catalogUserProg, *i))
    {
        CopyPartFromList(catalogUserProg, speedProg, *i);
    }
    else
    {
        return false; // + Код ошибки
    }
    workTime = *++i;
    ampLimit = *++i;
    speedLimit = *++i; 
    return true;
}
short PreparingProgramm()
{
    short size = 0;
    if (ampCode >= USER_AMP_BEG && ampCode <= USER_AMP_END)
    {
        size += ampProg.size();
    }
    else
    {
        ampProg.clear();
    }
    if (speedCode >= USER_SPEED_BEG && speedCode <= USER_SPEED_END)
    {
        size += speedProg.size();
    }
    else
    {
        speedProg.clear();
    }
    return size;
}
bool PreparingDescription(short progSize)
{
    if (arhiveList.size() + DESCRIPTION_LENGTH + progSize  <= maxSizeArhive)
    {
        description.clear();
        if (progCode <= PROG_NUMBER_END) // Проверка резерва кодов программы (а следовательно и кодов амплитуды и скорости, т.к. коды амплитуды или скорости меньше или равны количеству программ)
        {
            if (progCode == PROG_NUMBER_DEF)
            {
                description.emplace_back(PROG_NUMBER_DEF);
            }
            else
            {
                if (!FindCodeInList(descriptionCatalog, progCode))
                {
                    description.emplace_back(UserProgCode.getIncrement());
                }
                else
                {
                    description.emplace_back(progCode);
                }
            }
            byte amp = ampCode;
            if (ampCode >= USER_AMP_BEG && ampCode <= USER_AMP_END)
            {
                amp = UserAmpCode.getIncrement();
            }
            description.emplace_back(amp);
            byte speed = speedCode;
            if (speedCode >= USER_SPEED_BEG && speedCode <= USER_SPEED_END)
            {
                speed = UserSpeedCode.getIncrement();
            }
            description.emplace_back(speed);
            description.emplace_back(workTime);
            description.emplace_back(ampLimit);
            description.emplace_back(speedLimit);
        }
        else
        {
            return false;
        }
        return true;
    }
    return false;
}
bool CompilingArhive(bool write)
{
    if (write)
    {
        list <byte>::iterator i = description.begin();
        if (ampProg.size() > 0)
        {
            LinkingListsWithSubstitution(maxSizeArhive, catalogUserProg, *++i, ampProg);
        }
        if (speedProg.size() > 0)
        {
            LinkingListsWithSubstitution(maxSizeArhive, catalogUserProg, *++i, speedProg);
        }
        if (LinkingListsWithSubstitution(maxSizeArhive, descriptionCatalog, description))
        {
            arhiveList.clear();
            LinkingLists(arhiveList, descriptionCatalog, SEPARATOR, catalogUserProg);
            ConvertListToStaticArray(arhiveList, arhiveArray, maxSizeArhive, NUL);
            return true;
        }
    }
    return false;
}
bool DeleteProgramm(const byte code)
{
    description.clear();
    CopyPartFromList(descriptionCatalog, description, code, CODE_LENGTH);
    list <byte> offsetCodes;
    if (code != PROG_NUMBER_DEF)
    {
        offsetCodes.emplace_back(code);
        UserProgCode.setDecrement();
    }
    else
    {
        offsetCodes.emplace_back(PROG_NUMBER_BEG);
    }
    list <byte>::iterator itDes = description.begin();
    byte first = *itDes++;
    byte second = *itDes--;
    if (first >= USER_AMP_BEG || second >= USER_AMP_BEG) // В каталоге программ существует запись, которую надо удалить
    {
        catalogUserProg.emplace_back(SEPARATOR);
        list <byte>::iterator itCat = catalogUserProg.begin();
        list <byte> ampCatalog;
        list <byte> speedCatalog;
        while (*itCat < USER_SPEED_BEG) // Разделяем каталог
        {
            ampCatalog.emplace_back(*itCat++);
        }
        while (*itCat < SEPARATOR) // Разделяем каталог
        {
            speedCatalog.emplace_back(*itCat++);
        }
        if (first >= USER_AMP_BEG && first <= USER_AMP_END) // Удаляем программу
        {
            EracePartFromList(ampCatalog, first);
            CodeOffset(ampCatalog, USER_AMP_BEG);
            offsetCodes.emplace_back(first);
            UserAmpCode.setDecrement();
        }
        if (second >= USER_SPEED_BEG && second <= USER_SPEED_END) // Удаляем программу
        {
            EracePartFromList(speedCatalog, second);
            CodeOffset(speedCatalog, USER_SPEED_BEG);
            offsetCodes.emplace_back(second);
            UserSpeedCode.setDecrement();
        }
        catalogUserProg.clear();
        LinkingLists(catalogUserProg, ampCatalog, speedCatalog);
    }
    EracePartFromList(descriptionCatalog, code, DESCRIPTION_LENGTH);
    CodeOffset(descriptionCatalog, offsetCodes, DESCRIPTION_LENGTH);
    arhiveList.clear();
    LinkingLists(arhiveList, descriptionCatalog, SEPARATOR, catalogUserProg);
    if (ConvertListToStaticArray(arhiveList, arhiveArray, maxSizeArhive, NUL))
    {
        return true;
    }
    return false;
}
bool SaveArrayInEEprom(bool save)
{
    if (save)
    {
        // Вызов функции записи массива в энергонезависимую память
        return true;
    }
    else
    {
        Serial.println("Номер ошибки (4) для генерирования сообщения пользователю");
        return false;
    }
}
void CreateHeaderUserProg()
{
    if (descriptionCatalog.size() == 0)
    {
        headerUserProg.emplace_back(PROG_NUMBER_DEF);
    }
    else
    {
        for (list <byte>::iterator i = descriptionCatalog.begin(); i != descriptionCatalog.end(); advance(i, DESCRIPTION_LENGTH))
        {
            headerUserProg.emplace_back(*i);
        }
    }
}

void Test()
{
    // Подготовка
        ExtractArhive();
        CreatCodeInLists();
        CreatBuildProgramm();
    // Добавление или изменение программы
        progCode = UserProgCode.getCounter();
        ampCode = UserAmpCode.getCounter();
        //ampCode = BuildAmpCode.getCounter() - 2;
        ampProg = {1,2,3,4,5};
        speedCode = UserSpeedCode.getCounter();
        //speedCode = BuildSpeedCode.getCounter() - 3;
        speedProg = {5,4,3,2,1};
        workTime = 14;
        ampLimit = 5;
        speedLimit = 6;
        if (CompilingArhive(PreparingDescription(PreparingProgramm())))
        {
            // Вызов функции записи массива в энергонезависимую память
            for (list <byte>::iterator i = arhiveList.begin(); i != arhiveList.end(); i++)
            {
                Serial.print(String(*i, DEC) + " ");
            }
            Serial.println();
            /* for (auto i = 0; i < maxSizeArhive; i++)
            {
                Serial.print(String(arhiveArray[i], DEC) + " ");
            }
            Serial.println(); */
        }
        else
        {
            Serial.println("Номер ошибки (1) для генерирования сообщения пользователю");
        }
    // Добавление или изменение программы
        progCode = UserProgCode.getCounter();
        ampCode = UserAmpCode.getCounter();
        //ampCode = BuildAmpCode.getCounter() - 2;
        ampProg = {2,5};
        speedCode = UserSpeedCode.getCounter();
        //speedCode = BuildSpeedCode.getCounter() - 3;
        speedProg = {5,4,3};
        workTime = 11;
        ampLimit = 7;
        speedLimit = 5;
        if (CompilingArhive(PreparingDescription(PreparingProgramm())))
        {
            // Вызов функции записи массива в энергонезависимую память
            for (list <byte>::iterator i = arhiveList.begin(); i != arhiveList.end(); i++)
            {
                Serial.print(String(*i, DEC) + " ");
            }
            Serial.println();
            /* for (auto i = 0; i < maxSizeArhive; i++)
            {
                Serial.print(String(arhiveArray[i], DEC) + " ");
            }
            Serial.println(); */
        }
        else
        {
            Serial.println("Номер ошибки (1) для генерирования сообщения пользователю");
        }
    // Изменение программы по умолчанию
        progCode = PROG_NUMBER_DEF;
        ampCode = UserAmpCode.getCounter();
        //ampCode = BuildAmpCode.getCounter() - 2;
        ampProg = {8,2,7,3,5};
        speedCode = UserSpeedCode.getCounter();
        //speedCode = BuildSpeedCode.getCounter() - 3;
        speedProg = {5,2,3,4,5};
        workTime = 25;
        ampLimit = 9;
        speedLimit = 5;
        if (CompilingArhive(PreparingDescription(PreparingProgramm())))
        {
            // Вызов функции записи массива в энергонезависимую память
            for (list <byte>::iterator i = arhiveList.begin(); i != arhiveList.end(); i++)
            {
                Serial.print(String(*i, DEC) + " ");
            }
            Serial.println();
        }
        else
        {
            Serial.println("Номер ошибки (1) для генерирования сообщения пользователю");
        }
    // Извлечение программы
        byte code = 100;
        if (CheckProgramm(code))
        {
            if (!ExtractProgramm(code))
            {
                DefaultProgramm();
                Serial.println("Номер ошибки (2) для генерирования сообщения пользователю");
            }
        }
        else
        {
            DefaultProgramm();
        }
        for (list <byte>::iterator i = ampProg.begin(); i != ampProg.end(); i++)
        {
            Serial.print(String(*i, DEC) + " ");
        }
        Serial.println();
        for (list <byte>:: iterator i = speedProg.begin(); i != speedProg.end(); i++)
        {
            Serial.print(String(*i, DEC) + " ");
        }
        Serial.println();
        Serial.println(workTime);
        Serial.println(ampLimit);
        Serial.println(speedLimit);
    //Удаление программы
        byte code2 = 102;
        if (DeleteProgramm(code2))
        {
            // Вызов функции записи массива в энергонезависимую память
        }
        else
        {
            Serial.println("Номер ошибки (3) для генерирования сообщения пользователю");
        }
    // Извлечение программы
        if (CheckProgramm(code))
        {
            if (!ExtractProgramm(code))
            {
                DefaultProgramm();
                Serial.println("Номер ошибки (2) для генерирования сообщения пользователю");
            }
        }
        else
        {
            DefaultProgramm();
        }
        for (list <byte>::iterator i = ampProg.begin(); i != ampProg.end(); i++)
        {
            Serial.print(String(*i, DEC) + " ");
        }
        Serial.println();
        for (list <byte>:: iterator i = speedProg.begin(); i != speedProg.end(); i++)
        {
            Serial.print(String(*i, DEC) + " ");
        }
        Serial.println();
        Serial.println(workTime);
        Serial.println(ampLimit);
        Serial.println(speedLimit);
    // Добавление или изменение программы
        progCode = UserProgCode.getCounter();
        ampCode = UserAmpCode.getCounter();
        //ampCode = BuildAmpCode.getCounter() - 2;
        ampProg = {5};
        speedCode = UserSpeedCode.getCounter();
        //speedCode = BuildSpeedCode.getCounter() - 3;
        speedProg = {6};
        workTime = 50;
        ampLimit = 1;
        speedLimit = 2;
        if (CompilingArhive(PreparingDescription(PreparingProgramm())))
        {
            // Вызов функции записи массива в энергонезависимую память
            for (list <byte>::iterator i = arhiveList.begin(); i != arhiveList.end(); i++)
            {
                Serial.print(String(*i, DEC) + " ");
            }
            Serial.println();
            /* for (auto i = 0; i < maxSizeArhive; i++)
            {
                Serial.print(String(arhiveArray[i], DEC) + " ");
            }
            Serial.println(); */
        }
        else
        {
            Serial.println("Номер ошибки (1) для генерирования сообщения пользователю");
        }
    // Чтение архива
    for (list <byte>:: iterator i = arhiveList.begin(); i != arhiveList.end(); i++)
    {
        Serial.print(String(*i, DEC) + " ");
    }
    Serial.println();
    //Удаление программы
        code2 = 100;
        if (DeleteProgramm(code2))
        {
            // Вызов функции записи массива в энергонезависимую память
        }
        else
        {
            Serial.println("Номер ошибки (3) для генерирования сообщения пользователю");
        }
    // Чтение архива
        for (list <byte>:: iterator i = arhiveList.begin(); i != arhiveList.end(); i++)
        {
            Serial.print(String(*i, DEC) + " ");
        }
        Serial.println("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    // Изменение программы по умолчанию
        progCode = PROG_NUMBER_DEF;
        ampCode = UserAmpCode.getCounter();
        //ampCode = BuildAmpCode.getCounter() - 2;
        ampProg = {1,2,3};
        speedCode = UserSpeedCode.getCounter();
        //speedCode = BuildSpeedCode.getCounter() - 3;
        speedProg = {3,2,1};
        workTime = 40;
        ampLimit = 10;
        speedLimit = 11;
        if (CompilingArhive(PreparingDescription(PreparingProgramm())))
        {
            // Вызов функции записи массива в энергонезависимую память
            for (list <byte>::iterator i = arhiveList.begin(); i != arhiveList.end(); i++)
            {
                Serial.print(String(*i, DEC) + " ");
            }
            Serial.println();
        }
        else
        {
            Serial.println("Номер ошибки (1) для генерирования сообщения пользователю");
        }
    // Добавление или изменение программы
        progCode = UserProgCode.getCounter();
        ampCode = UserAmpCode.getCounter();
        //ampCode = BuildAmpCode.getCounter() - 2;
        ampProg = {9,9,9};
        speedCode = UserSpeedCode.getCounter();
        //speedCode = BuildSpeedCode.getCounter() - 3;
        speedProg = {8,8,8};
        workTime = 88;
        ampLimit = 15;
        speedLimit = 16;
        if (CompilingArhive(PreparingDescription(PreparingProgramm())))
        {
            // Вызов функции записи массива в энергонезависимую память
            for (list <byte>::iterator i = arhiveList.begin(); i != arhiveList.end(); i++)
            {
                Serial.print(String(*i, DEC) + " ");
            }
            Serial.println();
            /* for (auto i = 0; i < maxSizeArhive; i++)
            {
                Serial.print(String(arhiveArray[i], DEC) + " ");
            }
            Serial.println(); */
        }
        else
        {
            Serial.println("Номер ошибки (1) для генерирования сообщения пользователю");
        }
   //Удаление программы
        code2 = 100;
        if (DeleteProgramm(code2))
        {
            // Вызов функции записи массива в энергонезависимую память
        }
        else
        {
            Serial.println("Номер ошибки (3) для генерирования сообщения пользователю");
        }
    // Чтение архива
        for (list <byte>:: iterator i = arhiveList.begin(); i != arhiveList.end(); i++)
        {
            Serial.print(String(*i, DEC) + " ");
        }
        Serial.println("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    // Заголовки программ
        CreateHeaderUserProg();
        for (list <byte>:: iterator i = headerUserProg.begin(); i != headerUserProg.end(); i++)
        {
            Serial.print(String(*i, DEC) + " ");
        }
        Serial.println();
}

void setup()
{
    setlocale(LC_ALL, "ru");
    Serial.begin(921600);
    Serial.println();
    Test();

    list <byte>::iterator i;
    byte a = UserAmpCode.getNext();


    /* // Соединение с замещением
    i = mainList.begin();
    bool record = LinkingListsWithSubstitution(MAX_SIZE, mainList, miniNumber++, firstList);
    if (record)
    {
        Serial.println("Список добавлен!");
    }
    else
    {
        Serial.println("Недостаточно свободного места!");
    }
    for(; i != mainList.end(); i++)
    {
        Serial.print(String(*i, DEC) + " ");
    }
    Serial.println(); */

    /* // Соединение кусков одинаковой длины с заменой
    byte maxSize = MAX_SIZE;
    LinkingListsWithSubstitution(maxSize, mainList, secondtList);
    i = mainList.begin();
    for(; i != mainList.end(); i++)
    {
        Serial.print(String(*i, DEC) + " ");
    }
    Serial.println(); */

    /* // Удаление части списка
    bool del = EracePartFromList(mainList, --miniNumber);
    if (del)
    {
        Serial.println("Список удален!");
        i = mainList.begin();
        for(; i != mainList.end(); i++)
        {
            Serial.print(String(*i, DEC) + " ");
        }
    }
    else
    {
        Serial.println("Совпадений не найдено");
    }
    Serial.println(); */

    /* // Соединение списков
    Serial.println("Список перезаписан из 2-х списков!");
    LinkingLists(mainList, firstList, secondtList);
    i = mainList.begin();
    for(; i != mainList.end(); i++)
    {
        Serial.print(String(*i, DEC) + " ");
    } */
    
    /* // Разделение списка
    if(SplitList(mainList, miniNumber, true, firstList, secondtList))
    {
        Serial.println("Разделение списка прошло успешно!");
        Serial.print("Первая часть разделенного списка: ");
        for(list <int>::iterator i = firstList.begin(); i != firstList.end(); i++)
        {
            Serial.print(String(*i, DEC) + " ");
        }
        Serial.println();
        Serial.print("Вторая часть разделенного списка: ");
        for(list <int>::iterator i = secondtList.begin(); i != secondtList.end(); i++)
        {
            Serial.print(String(*i, DEC) + " ");
        }
    }
    else
    {
        Serial.println("Разделитель не найден");
    } */

    /* // Конвертер статического массива в список без терминирующего знака
    ConvertStaticArrayToList(staticArray, ARRAY_SIZE, mainList);
    i = mainList.begin();
    Serial.print("Список полученный из массива: ");
    for(; i != mainList.end(); i++)
    {
        Serial.print(String(*i, DEC) + " ");
    }
    Serial.println(); */

    /* // Конвертер статического массива в список с терминирующим знаком
    ConvertStaticArrayToList(staticArray, ARRAY_SIZE, TERMINATION_SYMBOL, mainList);
    i = mainList.begin();
    Serial.print("Список полученный из массива: ");
    for(; i != mainList.end(); i++)
    {
        Serial.print(String(*i, DEC) + " ");
    }
    Serial.println(); */

    /* // Конвертер списка в статический массив без терминирующего знака
    if (ConvertListToStaticArray(mainList, staticArray, ARRAY_SIZE))
    {
        Serial.print("Массив полученный из списка: ");
        for (size_t i = 0; i < ARRAY_SIZE; i++)
        {
            Serial.print(String(staticArray[i], DEC) + " ");
        }
    }
    else
    {
        Serial.println("Длина списка превышает длиту статического массива");
    } */

    /* // Конвертер списка в статический массив с терминирующим знаком
    if (ConvertListToStaticArray(mainList, staticArray, ARRAY_SIZE, TERMINATION_SYMBOL))
    {
        Serial.print("Массив полученный из списка: ");
        for (size_t i = 0; i < ARRAY_SIZE; i++)
        {
            Serial.print(String(staticArray[i], DEC) + " ");
        }
    }
    else
    {
        Serial.println("Длина списка превышает длиту статического массива");
    } */

    /* // Получить последний код в нужном диаппазоне из списка
    Serial.println("Последний использованый код в диаппазоне от " + String(BEGIN_CODE, DEC) + " до " + String(END_CODE, DEC) + " - " + String(GetLastCodeFromList(mainList, BEGIN_CODE, END_CODE), DEC));
    i = mainList.begin();
    for(; i != mainList.end(); i++)
    {
        Serial.print(String(*i, DEC) + " ");
    }
    Serial.println(); */

    /* // Поиск кода в списке
    Serial.print("Результат поиска: ");
    if (FindCodeInList(mainList, 2))
    {
        Serial.println("код найден!");
    }
    else
    {
        Serial.println("код не найден");
    } */

    /* // Вставка кода в список
    InsertValueInEdgesList(mainList, 111, false);
    i = mainList.begin();
    for(; i != mainList.end(); i++)
    {
        Serial.print(String(*i, DEC) + " ");
    }
    Serial.println(); */

    /* // Получить следующий код
    Serial.println("Следующий код: " + String(GetNextCodeFromList(true, GetLastCodeFromList(mainList, PROG_NUMBER_BEG, PROG_NUMBER_END), PROG_NUMBER_BEG, PROG_NUMBER_END), DEC)); */

    /* // Получить размер диаппазона списка
    Serial.println("Размер диаппазона с кодом " + String(miniNumber, DEC) + " составляет: " + String(GetRangeSize(mainList, miniNumber), DEC)); */

    /* // Копирование части списка
    byte code = 50;
    firstList.clear();
    CopyPartFromList(mainList, firstList, code);
    i = firstList.begin();
    for(; i != firstList.end(); i++)
    {
        Serial.print(String(*i, DEC) + " ");
    }
    Serial.println(); */
    
    // Извлечение значений из списка соответствующих указанному диаппазону
    list <byte> testList;
    ExtractValidValuesFromList(arhiveList, testList, BUILD_SPEED_BEG, USER_SPEED_END);
    for(auto i = testList.begin(); i != testList.end(); i++)
    {
        Serial.print(String(*i, DEC) + " ");
    }
    Serial.println();
}

void loop(){}