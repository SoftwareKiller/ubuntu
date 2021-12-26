print("Hello Python World")

message = "Hello Python World"

print(message)

message = "python is script"
print(message)

print(message.title())
print(message.upper())

one = "1"
two = "2"
expression = one + " + " + two
print(expression)

def greet_user(username):
    print("你好～" + username.title())

greet_user("jay")

def chg_list():
    fruit = ["banana","apple","orange"]
    print(fruit)
    fruit[1] = "strawberry"
    print(fruit)
    fruit.append("watermelon")
    print(fruit)
    fruit.insert(1, "peach")
    print(fruit)
    del fruit[0]
    print(fruit)
    eat_fruit = fruit.pop()
    print(eat_fruit, fruit)
    fruit.sort()
    print(fruit)
    for one in fruit:
        print(one)
    for val in range(1, 5):
        print(val)
chg_list()

def squares():
    sqare = [val**2 for val in range(1,11)]
    print(sqare)
    print(sum(sqare))

squares()
