from typing import Any
#from containers import list
#printf(*values: Any, sep: str = " ", end: str = "\n")
def printf(*values: Any, sep: str = " ", end: str = "\n") -> None:
    print(*values, sep=sep, end=end)

def cheese():
    ...

printf("Hello", "World!", sep = "t")