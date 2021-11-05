# Produtor-Consumidor

## Como compilar e rodar

Para compilar o Shell através de Makefile, utilize o `make`. Exemplo:
```
make
```
Após compilado, basta apenas rodá-lo através do terminal e seguir os prompts do programa:
```
./main
```

Outro comando de utilidade é o `make clean`: 
```
make clean
```
Ele pode ser usado para limpar os arquivos gerados pelo `make`, assim podendo recompilar após alterações.

## Detalhes extras

Essa solução para o problema de produtor-consumidor foi desenvolvido utilizando as três bibliotecas externas `pthreads.h`, `semaphore.h` e `unistd.h` para utilizar-mos de threads, mutex e semáforos para a implementação. Os únicos arquivos necessários para a compilação são os ``main.c`` e ``Makefile`` Essa solução foi implementada no Windows através do Subsistema Linux (WSL2).
