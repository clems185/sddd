#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

#define MAX_SIZE 100  // ջ������С

// ���������ȼ�
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// ����ջ
class Stack {
private:
    char stack[MAX_SIZE];
    int top;

public:
    Stack() : top(-1) {}  // ���캯����ʼ��ջΪ��

    // ѹջ����
    void push(char c) {
        if (top < MAX_SIZE - 1) {
            stack[++top] = c;
        }
    }

    // ��ջ����
    char pop() {
        if (top >= 0) {
            return stack[top--];
        }
        return '\0';  // ��ջʱ���ؿ��ַ�
    }

    // ��ȡջ��Ԫ��
    char peek() {
        if (top >= 0) {
            return stack[top];
        }
        return '\0';  // ��ջʱ���ؿ��ַ�
    }

    // �ж�ջ�Ƿ�Ϊ��
    bool isEmpty() {
        return top == -1;
    }
};

// �ж��ַ��Ƿ�������
bool isDigit(char c) {
    return (c >= '0' && c <= '9') || c == '.' || c == '-';
}

// �������ֵ��ַ���
void processNumber(const char* exp, int& i, char* numBuffer) {
    int j = 0;

    // ������
    if (exp[i] == '-' || exp[i] == '+') {
        if (i == 0 || exp[i - 1] == '(' || exp[i - 1] == ' ' || exp[i - 1] == '+' || exp[i - 1] == '-' || exp[i - 1] == '*' || exp[i - 1] == '/') {
            // ���������ǰ�ķ��ţ����� "-3" �� "+5"��
            numBuffer[j++] = exp[i++];
        }
    }

    // ��ȡ���ֲ���
    while (isDigit(exp[i])) {
        numBuffer[j++] = exp[i++];
    }

    numBuffer[j] = '\0';  // ������
}

// ��׺ת��׺����
void infixToPostfix(const char* infix) {
    Stack operators;  // ������ջ
    char output[MAX_SIZE] = "";  // ���ڴ洢��׺���ʽ�Ľ��
    char numBuffer[MAX_SIZE];  // �洢��ʱ����
    int outIndex = 0;  // ��׺���ʽ�ĵ�ǰ����
    int i = 0;

    while (infix[i] != '\0') {
        char c = infix[i];

        // ���Կո�
        if (c == ' ') {
            i++;
            continue;
        }

        // ��������֣��������ֲ��������
        if (isDigit(c)) {
            processNumber(infix, i, numBuffer);
            // �����ּ������
            int j = 0;
            while (numBuffer[j] != '\0') {
                output[outIndex++] = numBuffer[j++];
            }
            output[outIndex++] = ' ';  // ���ֺ�ӿո�
            continue;
        }

        // �����������
        if (c == '(') {
            operators.push(c);
        }

        // �����������
        else if (c == ')') {
            while (!operators.isEmpty() && operators.peek() != '(') {
                output[outIndex++] = operators.pop();
                output[outIndex++] = ' ';
            }
            operators.pop();  // ���� '('
        }

        // ����������
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            // ����ջ�����ȼ��ϸߵ������
            while (!operators.isEmpty() && precedence(operators.peek()) >= precedence(c)) {
                output[outIndex++] = operators.pop();
                output[outIndex++] = ' ';
            }
            operators.push(c);
        }
        i++;
    }

    // ��ջ��ʣ���������������
    while (!operators.isEmpty()) {
        output[outIndex++] = operators.pop();
        output[outIndex++] = ' ';
    }

    // ��������ȥ�����Ŀո�
    if (outIndex > 0 && output[outIndex - 1] == ' ') {
        outIndex--;
    }
    output[outIndex] = '\0';
    cout << output << endl;
}

int main() {
    char infix[MAX_SIZE];
    // ������׺���ʽ
    cin.getline(infix, MAX_SIZE);
    infixToPostfix(infix);
    return 0;
}
