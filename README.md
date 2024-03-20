# АНДРЕЙ НОСОВ НЕ ВИНОВАТ 
#FREENOSOV
# Processor Emulator
based on C++ to code on assembly-like language

## Usage

```assembly

factorial:
    push 1
    jae return
    pop
    popr ax
    pushr ax
    push 1
    pushr ax
    sub
    call factorial
    mul
    ret
    return:
        pop
        ret


begin
in
call factorial
out
end
```
