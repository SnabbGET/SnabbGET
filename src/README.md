# How does it work?

The `core` folder contain the terminal.  
The `graphics` folder contain the GUI.

Schema:

```mermaid
flowchart LR

A{Main} ===> |Text, commands results| B
B(GUI)  ===> |Buttons, inputs...| A
A       ---> |Errors| D(std)
C[Core] <==> |All| A
```

For the moment, the GUI is `std` (CLI).

You can also use the command-line version

```sh
$ <SnabbGET file path> say hello
> hello
```

```mermaid
flowchart LR

C(Terminal) ==> |Command|A
A --> |Analysis| A
A{Main} ==> |Command| B
B[Core] ==> |Result| A
A ==> |Result| C
```
