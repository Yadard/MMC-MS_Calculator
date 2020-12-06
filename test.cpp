#include<iostream>

using namespace std;

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

void translInput(unsigned int* translated, int size){
    char input[360];
    std::cout << "Input the numbers to MMC (separete numbers with \", \" i.e, \"25, 50 , 75\")" << std::endl;
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
                break;
            }
            currentIndex = i + 1;
        }
        else if (currentIndexTranslated + 1 >= size)
        {
            break;
        }
    }
}

unsigned int* getMin(unsigned int* inputs, int size){
    int minNode = inputs[0];
    unsigned int* adress = &inputs[0];
    for (unsigned short i = 0; i < size; i++)
    {
        if (inputs[i] < minNode && inputs[i] != 0)
        {
            minNode = inputs[i];
            adress = &inputs[i];
        }
    }
    return adress;
}

int main(){
    int istrue[5] = {0 * 5};
    istrue[3] += 5; 
    for (size_t i = 0; i < 5; i++)
    {
        if (i < 4)
        {
            cout << istrue[i] << ", ";
            if (istrue[i])
            {
                cout << "worked as a True";
            }
        }
        else
        {
            cout << istrue[i] << endl;
        }
    }
    cin.get();
}