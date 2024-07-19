#include <iostream>
#include <cstring>
using namespace std;

class BigInteger {
private:
    char* number;
    int digits;
    char sign;

    void printMembers() {
        char* ptr = number;
        while (*ptr != '\0') {
            cout << *ptr++;
        }
        cout << endl;
        cout << "Digits: " << digits << endl;
        cout << "Sign: " << sign << endl;
    }

    void reverse(char* str, int length) const {
        int start = 0;
        int end = length - 1;
        while (start < end) {
            swap(*(str + start), *(str + end));
            start++;
            end--;
        }
    }

    void removeLeadingZeros()  {
        int i = 0;
        while (number[i] == '0' && i < digits - 1) {
            i++;
        }
        if (i > 0) {
            for (int j = 0; j < digits - i; j++) {
                number[j] = number[j + i];
            }
            digits -= i;
            number[digits] = '\0';
        }
    }

   
    void intToString(int num, char* str) {
       if (num == 0) {
        str[0] = '0';
        str[1] = '\0';
        return;
    }

    int i = 0;
    bool isNegative = false;

    if (num < 0) {
        isNegative = true;
        num = -num;
    }

    while (num != 0) {
        int digit = num % 10;
        str[i++] = digit + '0';
        num /= 10;
    }

    if (isNegative) {
        str[i++] = '-';
    }

    str[i] = '\0';

    // Reverse the string
    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}


public:
    BigInteger() {
        number = new char[2];
        number[0] = '0';
        number[1] = '\0';
        digits = 1;
        sign = '+';
    }

    BigInteger(const char *num) {
        digits = strlen(num);
        number = new char[digits + 1];
        strcpy(number, num);
        if (num[0] == '-') {
            sign = '-';
            removeLeadingZeros();
        } else {
            sign = '+';
        }
    }

    BigInteger(int num) {
        int temp = num;
        if (num < 0) {
            sign = '-';
            temp = -temp;
        } else {
            sign = '+';
        }
        digits = 0;
        while (temp != 0) {
            temp /= 10;
            digits++;
        }
        if (digits == 0) 
         digits = 1;
        number = new char[digits + 1];
        intToString(num, number);
    }

    BigInteger(const BigInteger &num) {
        digits = num.digits;
        number = new char[digits + 1];
        strcpy(number, num.number);
        sign = num.sign;
    }

    BigInteger add( const BigInteger &num) const  {
        int maxLength = max(digits, num.digits);
        char *result = new char[maxLength + 2];
        int carry = 0;
        int i = digits - 1, j = num.digits - 1, k = 0;
        while (i >= 0 || j >= 0 || carry) {
            int sum = carry;
            if (i >= 0) sum += number[i--] - '0';
            if (j >= 0) sum += num.number[j--] - '0';
            result[k++] = sum % 10 + '0';
            carry = sum / 10;
        }
        result[k] = '\0';
        reverse(result, k);
        BigInteger res(result);
        delete[] result;
        return res;
    }
    bool operator>=(const BigInteger &num) const {
        if (sign == '+' && num.sign == '-') return true;
        if (sign == '-' && num.sign == '+') return false;
        if (digits > num.digits) return true;
        if (digits < num.digits) return false;
        for (int i = 0; i < digits; ++i) {
            if (number[i] > num.number[i]) return true;
            if (number[i] < num.number[i]) return false;
        }
        return true; 
    }
    BigInteger subtract(BigInteger &num) {
        char *result = new char[digits + 1];
        int borrow = 0;
        int i = digits - 1, j = num.digits - 1, k = 0;
        while (i >= 0) {
            int sub = (number[i--] - '0') - borrow;
            if (j >= 0) sub -= num.number[j--] - '0';
            if (sub < 0) {
                sub += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            result[k++] = sub + '0';
        }
        result[k] = '\0';
        reverse(result, k);
        BigInteger res(result);
        delete[] result;
        return res;
    }
 
    BigInteger multiply(BigInteger &num) {
        int m = digits, n = num.digits;
        int *temp = new int[m + n]();

        for (int i = m - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                int mul = (number[i] - '0') * (num.number[j] - '0');
                int sum = mul + temp[i + j + 1];
                temp[i + j] += sum / 10;
                temp[i + j + 1] = sum % 10;
            }
        }

        char *result = new char[m + n + 1];
        for (int i = 0; i < m + n; ++i) {
            result[i] = temp[i] + '0';
        }
        result[m + n] = '\0';
        BigInteger res(result);
        delete[] temp;
        delete[] result;
        return res;
    }
   bool isZero() const {
    return (digits == 1 && number[0] == '0');
}
    void print() {
        char *ptr = number;
    
        while (*ptr != '\0') {
            cout << *ptr++;
        }
        cout << endl;
    }

    ~BigInteger() {
        delete[] number;
    }
};

int main() {
    int num11,num22,num33;
    cout<<"enter three numbers";
    cin>>num11>>num22>>num33;
    BigInteger num1(num11);
    BigInteger num2(num22); // Enclose negative number in quotes
    BigInteger num3(num33);
    cout<<"num1 "<<endl;
    num1.print();
    cout<<"num2 "<<endl;
    num2.print();
    cout<<"num 3"<<endl;
    num3.print();
    cout<<"sum "<<endl;
    BigInteger sum = num1.add(num3);
    sum.print();
    cout<<"difference "<<endl;
    BigInteger difference = num1.subtract(num3);
    difference.print();
    cout<<"product of num1 and num3 "<<endl;
    BigInteger product = num1.multiply(num3);
    product.print();

    return 0;
}