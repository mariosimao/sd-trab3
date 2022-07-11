# Centralized algorithm for distributed mutual exclusion

## Compilation

To compile both coordinator server and client program:

```bash
$ make all
```

## Usage

To execute the coordinator server:

```bash
$ ./coordinator
```

To execute the client process:

```bash
$ ./process <k-seconds-to-wait> <r-repetitions>
```

Example:

```bash
$ ./process 1 3
```

## Cleanup

To remove the executables, result file, logs and free the coordinator server port (8081):

```bash
$ make clean
```
