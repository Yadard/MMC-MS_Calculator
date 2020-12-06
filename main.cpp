#include <iostream>
#include <conio.h>

int powerOf10(int exponent){
    switch (exponent)
    {
    case 0:
        return 1;
        break;
    case 1:
        return 10;
        break;
    default:
        int result = 10;
        for (unsigned short i = 1; i < exponent; i++)
        {
            result = result * 10;
        }
        return result;
        break;
    }
}

void getPrimes(unsigned int* primes, int amount){
    unsigned int numberProcessor = 2;
    unsigned short currentIndex = 0;
    while (currentIndex < amount)
    {
        bool isPrime = true;
        for (unsigned int j = 2; j < numberProcessor; j++)
        {
            if (numberProcessor % j == 0)
            {
                isPrime = false;
            }
        }
        if (isPrime)
        {
            primes[currentIndex] = numberProcessor;
            currentIndex++;
        }
        numberProcessor++;
    }
}

unsigned short translInput(unsigned int* translated, int size){
    char input[360];
    std::cout << "Input the numbers to MMC (separete numbers with \", \" i.e, \"25,50,75\")" << std::endl;
    std::cin >> input;
    unsigned int currentIndexTranslated = 0;
    unsigned int currentIndex = 0;
    for (unsigned short i = 0; i < sizeof(input); i++)
    {
        if (input[i] == ',' || input[i] == '\0' && currentIndexTranslated + 1 < size)
        {
            unsigned short number = 0;
            unsigned short currentDecimalHouse = i-1-currentIndex;
            for (unsigned int j = currentIndex; j < i; j++)
            {
                if ((int) input[j] > 47 && (int) input[j] < 58) //IF it is a numeric digit
                {
                   number = number + ((int) input[j] - 48) * powerOf10(currentDecimalHouse);
                }
                currentDecimalHouse--;
            }
            translated[currentIndexTranslated] = number; 
            currentIndexTranslated++;
            if (input[i] == '\0')
            {
                if (currentIndexTranslated < size-1)
                {
                    for (short i = currentIndexTranslated; i < size; i++)
                    {
                        translated[i] = 0;
                    } 
                }
                return currentIndexTranslated;
            }
            currentIndex = i + 1;
        }
        else if (currentIndexTranslated + 1 >= size)
        {
            break;
        }
    }
    return size;
}

unsigned int* getMax(unsigned int* inputs, int size){
    int maxNode = inputs[0];
    unsigned int* adress = &inputs[0];
    for (unsigned short i = 0; i < size; i++)
    {
        if (inputs[i] > maxNode && inputs[i] != 0)
        {
            maxNode = inputs[i];
            adress = &inputs[i];
        }
    }
    return adress;
}

void separator(unsigned short size){
    for (unsigned short i = 0; i < size; i++)
    {
        if (i == 0)
        {
            std::cout << "<";
        }
        else if (i == size - 1)
        {
            std::cout << ">" << std::endl;
        }
        else
        {
            std::cout << "=";
        }
    }
}

void API(unsigned int* Ms, unsigned int sizeInputs, unsigned int MMC, unsigned int simplifier, unsigned int* inputs){
    short answer;
    do
    {
    system("cls");
    separator(110);
    for (unsigned short i = 0; i < sizeInputs; i++)
    {
        if (sizeInputs == 1 && i == 0)
        {
            std::cout << "The input was [" << inputs[i] << "], ";
        }
        
        else if (i == 0)
        {
            std::cout << "The input was [" << inputs[i] << ", ";
        }
        else if (i == sizeInputs - 1)
        {
            std::cout << inputs[i] << "], ";
        }
        else
        {
            std::cout << inputs[i] << ", ";
        } 
    }
    
    std::cout << "Type the keynum to chose the output:\n"
    << "\t\t MMC[1]\tMaximum simplifier[2]" << std::endl;
    answer = std::cin.get();
    } while(!(answer > 47 && answer < 51));
    separator(110);
    if (answer == 48)
    {
        for (size_t i = 0; i < 10000000; i++)
        {
            if (Ms[i+1] == 0)
            {
                std::cout << Ms[i] << "]"<< std::endl;
                break;
            }
            if (i == 0)
            {
                std::cout << "steps = [" << Ms[i] << ", ";
            }
            std::cout << Ms[i] << ", ";
        }
        std::cout << "MMC = " << MMC << std::endl;
    }
    else
    {
        std::cout << "Max simplifier = " << simplifier << std::endl;
    }
    
}

int main(){
    unsigned int StepsToMMC[100], inputsBase[8], inputs[8], prime[500], simplifier = 1, MMCResult = 1;
    unsigned short currentIndex = 0, lenInputs;
    bool isDone = true, isAllM = true;
    getPrimes(prime, 500);
    lenInputs = translInput(inputs, 8);
    for (unsigned short i = 0; i < lenInputs; i++)
    {
        inputsBase[i] = inputs[i];
    }
    bool inputsIsM[lenInputs] = {false*lenInputs};
    for (unsigned short i = 0; i < sizeof(prime)/sizeof(int); i++)
    {
        unsigned int* max = getMax(inputs, lenInputs);
        isAllM = true;
        if (prime[i] < *max)
        {
            for (unsigned int j = 0; j < lenInputs; j++)
            {
                isDone = true;
                if (inputs[j] != 1)
                {
                    isDone = false;
                }
                while(inputs[j] > 1)
                {
                    if (inputs[j] % prime[i] == 0)
                    {
                        StepsToMMC[currentIndex] = prime[i];
                        for (unsigned short l = 0; l < lenInputs; l++)
                        {
                            if (inputs[l] % prime[i] == 0)
                            {
                                inputs[l] /= prime[i];
                                inputsIsM[l] = true;
                            } 
                            if (!inputsIsM[l])
                            {
                                isAllM = false;
                            }
                        }
                        if (isAllM)
                        {
                            simplifier *= prime[i];
                        }
                        MMCResult *= prime[i];
                        currentIndex++;
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
        else if (isDone)
        {
            break;
        }
    }
    StepsToMMC[currentIndex] = 0;
    API(StepsToMMC, lenInputs, MMCResult, simplifier, inputsBase);
    system("pause");
    return 0;
}