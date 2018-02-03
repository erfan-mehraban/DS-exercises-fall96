sorted_operators = ['(', ')', '*', '/', '+', '-']


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


def tokenize(expression):
    tokenized = []

    i = 0
    while i < len(expression):
        char = expression[i]
        if char not in sorted_operators:
            tokenized.append([char])
        else:
            if char in sorted_operators[2:]:
                tokenized.append(char)
            else:
                bracket_counter = 0
                for j in range(i, len(expression)):
                    inbracket_char = expression[j]
                    if inbracket_char == '(':
                        bracket_counter += 1
                    elif inbracket_char == ')':
                        bracket_counter -= 1

                    if bracket_counter == 0:
                        tokenized.append(tokenize(expression[i + 1:j]))
                        i = j
                        break
        i += 1

    return tokenized


def infix_to_postfix(tokenized_expression):
    if tokenized_expression not in sorted_operators and type(tokenized_expression) is str:
        return tokenized_expression

    postfixed = ""
    operators_stack = ArrayStack()
    for i, term in enumerate(tokenized_expression):
        if term in sorted_operators:
            if len(operators_stack) == 0 or \
                    sorted_operators.index(term) / 2 < sorted_operators.index(operators_stack.peek()) / 2:
                operators_stack.push(term)
            elif sorted_operators.index(term) / 2 == sorted_operators.index(operators_stack.peek()) / 2:
                postfixed += operators_stack.pop()
                operators_stack.push(term)
            elif sorted_operators.index(term) / 2 > sorted_operators.index(operators_stack.peek()) / 2:
                for j in range(len(operators_stack)):
                    postfixed += operators_stack.pop()
                operators_stack.push(term)
        else:
            postfixed += infix_to_postfix(term)
    for j in range(len(operators_stack)):
        postfixed += operators_stack.pop()

    return postfixed


input_expression = raw_input()
tokenized_expression = tokenize(input_expression)
print infix_to_postfix(tokenized_expression)
