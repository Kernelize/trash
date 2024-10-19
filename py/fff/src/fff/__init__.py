import typing as t
import collections.abc as c

def hello() -> str:
    return "Hello from fff!"

def say_hello(names: t.Iterable) -> None:
    for name in names:
        print(f"Hello, {name}")
