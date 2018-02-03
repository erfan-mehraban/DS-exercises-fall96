import re


class ArrayStack:
    def __init__(self):
        self.__stack_size = 0
        self.__capacity = 1
        self.__items = [None] * self.__stack_size

    def __len__(self):
        return self.__stack_size

    def _resize(self):
        if self.__stack_size + 1 <= self.__capacity and \
                self.__stack_size * 3 >= self.__capacity:
            return

        new_capacity = max(1, 2 * self.__stack_size)
        new_items = [None] * new_capacity

        for i in range(self.__stack_size):
            new_items[i] = self.__items[i]
        self.__items = new_items
        self.__capacity = new_capacity

    def pop(self):
        if self.__stack_size == 0:
            return None

        tmp = self.__items[self.__stack_size - 1]
        self.__stack_size -= 1
        self._resize()
        return tmp

    def peek(self):
        return self.__items[self.__stack_size - 1]

    def push(self, value):
        self._resize()
        self.__items[self.__stack_size] = value
        self.__stack_size += 1


class Deque:
    def __init__(self):
        self.__capacity = 1
        self.__deque_size = 0
        self.__first_item_index = 0
        self.__items = [None] * self.__capacity
        self.__iter_index = 0

    def __len__(self):
        return self.__deque_size

    def __iter__(self):
        return self

    def __next__(self):
        self.__iter_index += 1
        if self.__iter_index - 1 < self.__deque_size:
            return self[self.__iter_index - 1]
        else:
            self.__iter_index = 0
            raise StopIteration  # Done iterating.
    next = __next__  # python2.x compatibility

    def __str__(self):
        string = ''
        for i in range(self.__deque_size):
            string += str(self[i]) + ' '
        return string

    def __getitem__(self, index):
        return self.__items[(index + self.__first_item_index) %
                            self.__capacity]

    def __setitem__(self, index, item):
        self.__items[(index + self.__first_item_index) %
                     self.__capacity] = item

    def _resize(self):
        if self.__deque_size + 1 <= self.__capacity and \
                self.__deque_size * 3 >= self.__capacity:
            return

        new_capacity = max(1, 2 * self.__deque_size)
        new_items = [None] * new_capacity

        for i in range(self.__deque_size):
            new_items[i] = self[i]
        self.__items = new_items
        self.__capacity = new_capacity
        self.__first_item_index = 0

    def is_empty(self):
        return self.__deque_size == 0

    def add(self, index, item):
        self._resize()

        if index < self.__deque_size / 2:
            if self.__first_item_index == 0:
                self.__first_item_index = self.__capacity - 1
            else:
                self.__first_item_index -= 1

            for i in range(index - 1):
                self[i] = self[i + 1]
        else:
            for i in range(self.__deque_size, index, -1):
                self[i] = self[i - 1]
        self[index] = item
        self.__deque_size += 1

        return self

    def add_right(self, item):
        return self.add(self.__deque_size, item)

    def add_left(self, item):
        return self.add(0, item)

    def remove(self, index):
        tmp = self[index]
        if index < self.__deque_size / 2:
            for i in range(index, 0, -1):
                self[i] = self[i - 1]
            self.__first_item_index = (
                self.__first_item_index + 1) % self.__capacity
        else:
            for i in range(index, self.__deque_size - 1):
                self[i] = self[i + 1]
        self.__deque_size -= 1
        self._resize()
        return tmp

    def remove_right(self):
        return self.remove(self.__deque_size - 1)

    def remove_left(self):
        return self.remove(0)


def tokenize(infix_expression):
    infix_expression = re.sub(r'\)\(', r') * (', infix_expression)
    infix_expression = re.sub(r'(\d)\(', r'\1 * (', infix_expression)
    infix_expression = re.sub(r'\)(\d)', r') * \1', infix_expression)

    tokenized_expression = Deque()
    number = ''
    for char in infix_expression:
        if char in '1234567890':
            number = number + char
        else:
            if number != '':
                tokenized_expression.add_right(number)
            number = ''

        if char in '()+-/*^':
            tokenized_expression.add_right(char)

    if number != '':
        tokenized_expression.add_right(number)

    return tokenized_expression


def infix_to_postfix(infix_expression):
    operators_precedence = {'^': 5, '/': 4, '*': 3, '-': 2, '+': 1, '(': 0}
    tokenized_expression = tokenize(infix_expression)
    operators_stack = ArrayStack()
    postfixed_expression = Deque()

    for token in tokenized_expression:
        if token == '(':
            operators_stack.push(token)
        elif token == ')':
            while operators_stack.peek() != '(':
                postfixed_expression.add_right(operators_stack.pop())
            operators_stack.pop()
        elif token in operators_precedence.keys():
            while (operators_stack and
                   operators_precedence[operators_stack.peek()]
                   >= operators_precedence[token]):
                postfixed_expression.add_right(operators_stack.pop())
            operators_stack.push(token)
        else:
            postfixed_expression.add_right(token)

    while operators_stack:
        postfixed_expression.add_right(operators_stack.pop())
    return postfixed_expression


def evaluate_postfix_expression(tokenized_postfix_expression):
    operands_stack = ArrayStack()
    for token in tokenized_postfix_expression:
        if token in '^/*-+':
            second_operand = int(operands_stack.pop())
            first_operand = int(operands_stack.pop())
            result = calculate(first_operand, second_operand, token)
            operands_stack.push(result)
        else:
            operands_stack.push(token)

    return operands_stack.pop()


def calculate(first_operand, second_operand, operator):
    if operator == '^':
        return first_operand ** second_operand
    if operator == '/':
        return first_operand / second_operand
    if operator == '*':
        return first_operand * second_operand
    if operator == '-':
        return first_operand - second_operand
    if operator == '+':
        return first_operand + second_operand

    print "WTF?"
    return 0


def main():
    infix_expression = raw_input()
    postfixed = infix_to_postfix(infix_expression)
    print postfixed
    print evaluate_postfix_expression(postfixed)


if __name__ == '__main__':
    main()
