priority = {
    "^": 5,
    "*": 3, "/": 4,
    "+": 1, "-": 2,
    "(": 0, ")": 0
}

def in2po(i):

    def add_operation(operations, current, result):
        ''' append op to operation stack or pop if neccessery '''
        if len(operations) > 0:
            while priority[current] <= priority[operations[-1]]:
                result += ' ' + operations.pop()
                if len(operations) == 0:
                    break
        operations.append(current)
        return result

    i = list(i)
    operations = []
    result = ""
    last = "+"
    for current in i:
        if current not in priority and current != ' ':
            if last not in priority:
                result += current  # digit of 1 number
            else:
                if last == ')':  # excaly after ) ended so it is multiply by before
                    result = add_operation(operations, "*", result)
                result += ' ' + current  # another num started
            last = current
        else:
            if current is " ":
                continue
            elif current is "(":  # add * if necessary to stack then append (
                if last not in priority or last == ")":
                    result = add_operation(operations, "*", result)
                operations.append(current)
                last = current
            elif current is ")":
                while operations[-1] is not '(':  # pop until reach )
                    result += ' ' + operations.pop()
                operations.pop()
                last = current
            elif current != ' ':  # it is operation so add it to stack
                result = add_operation(operations, current, result)
                last = current
    while operations:
        result += ' ' + operations.pop()
    return result
    # result += operations.pop()


def calculate(num1, op, num2):
    if op == "*":
        return num1 * num2
    elif op == "/":
        return int (num1 / num2)
    elif op == "+":
        return num1 + num2
    elif op == "-":
        return num1 - num2
    elif op == "^":
        return pow(num1, num2)


def evaluate(postfix):
    # for index in range(len(postfix)):
    index = 0
    while index < len(postfix):
        current = postfix[index]
        if current in priority:
            postfix[index-2] = calculate (int(postfix[index-2]), current, int(postfix[index-1]) )
            del postfix[index]
            del postfix[index-1]
            index -= 2
        index += 1
    return postfix


# infix = "(23 + 3 * 4) / 6 - 2" # test 1
# infix = "3 - 2 ^ 4 * 5" # test 2

# infix = "(12+34)(56+78)"
# infix = "3(1+2)"
# infix = "(1 + 3)4 + (1 + 1)2 ^ (3)3"
infix = input()
print( evaluate( in2po(infix).split() )[0])
