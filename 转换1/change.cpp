#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

#define MAX_SIZE 100  // 栈的最大大小

// 操作符优先级
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// 定义栈
class Stack {
private:
    char stack[MAX_SIZE];
    int top;

public:
    Stack() : top(-1) {}  // 构造函数初始化栈为空

    // 压栈操作
    void push(char c) {
        if (top < MAX_SIZE - 1) {
            stack[++top] = c;
        }
    }

    // 弹栈操作
    char pop() {
        if (top >= 0) {
            return stack[top--];
        }
        return '\0';  // 空栈时返回空字符
    }

    // 获取栈顶元素
    char peek() {
        if (top >= 0) {
            return stack[top];
        }
        return '\0';  // 空栈时返回空字符
    }

    // 判断栈是否为空
    bool isEmpty() {
        return top == -1;
    }
};

// 判断字符是否是数字
bool isDigit(char c) {
    return (c >= '0' && c <= '9') || c == '.' || c == '-';
}

// 处理数字到字符串
void processNumber(const char* exp, int& i, char* numBuffer) {
    int j = 0;

    // 处理负号
    if (exp[i] == '-' || exp[i] == '+') {
        if (i == 0 || exp[i - 1] == '(' || exp[i - 1] == ' ' || exp[i - 1] == '+' || exp[i - 1] == '-' || exp[i - 1] == '*' || exp[i - 1] == '/') {
            // 如果是数字前的符号（比如 "-3" 或 "+5"）
            numBuffer[j++] = exp[i++];
        }
    }

    // 读取数字部分
    while (isDigit(exp[i])) {
        numBuffer[j++] = exp[i++];
    }

    numBuffer[j] = '\0';  // 结束符
}

// 中缀转后缀函数
void infixToPostfix(const char* infix) {
    Stack operators;  // 操作符栈
    char output[MAX_SIZE] = "";  // 用于存储后缀表达式的结果
    char numBuffer[MAX_SIZE];  // 存储临时数字
    int outIndex = 0;  // 后缀表达式的当前索引
    int i = 0;

    while (infix[i] != '\0') {
        char c = infix[i];

        // 忽略空格
        if (c == ' ') {
            i++;
            continue;
        }

        // 如果是数字，则处理数字并加入输出
        if (isDigit(c)) {
            processNumber(infix, i, numBuffer);
            // 将数字加入输出
            int j = 0;
            while (numBuffer[j] != '\0') {
                output[outIndex++] = numBuffer[j++];
            }
            output[outIndex++] = ' ';  // 数字后加空格
            continue;
        }

        // 如果是左括号
        if (c == '(') {
            operators.push(c);
        }

        // 如果是右括号
        else if (c == ')') {
            while (!operators.isEmpty() && operators.peek() != '(') {
                output[outIndex++] = operators.pop();
                output[outIndex++] = ' ';
            }
            operators.pop();  // 弹出 '('
        }

        // 如果是运算符
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            // 弹出栈中优先级较高的运算符
            while (!operators.isEmpty() && precedence(operators.peek()) >= precedence(c)) {
                output[outIndex++] = operators.pop();
                output[outIndex++] = ' ';
            }
            operators.push(c);
        }
        i++;
    }

    // 将栈中剩余的运算符加入输出
    while (!operators.isEmpty()) {
        output[outIndex++] = operators.pop();
        output[outIndex++] = ' ';
    }

    // 输出结果（去掉最后的空格）
    if (outIndex > 0 && output[outIndex - 1] == ' ') {
        outIndex--;
    }
    output[outIndex] = '\0';
    cout << output << endl;
}

int main() {
    char infix[MAX_SIZE];
    // 输入中缀表达式
    cin.getline(infix, MAX_SIZE);
    infixToPostfix(infix);
    return 0;
}
