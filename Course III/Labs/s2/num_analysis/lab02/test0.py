# print(" Hola! ")
import sys
import os


def hello():
    return "hello!"


def hola():
    return "hola!"


def main():
    print("\n Please, enter a command name: ")
    command = str(input()).lstrip("()")
    message = ""
    if command == "hello":
        message = hello()
    if command == "hola":
        message = hola()
    print(message)

if __name__ == '__main__':
    main()
