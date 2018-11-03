# getrusage() wrapper
- known to work on Linux and OpenBSD
- created as my simple "time for x in {1..100}; ..." benchmarks were a lot less pleasant on OpenBSD.

## build
```
make
```

## usage and examples
```
$ getr 1000 ./fizzbuzz >/dev/null
User time      : 0 s, 180000 us
System time    : 0 s, 700000 us
Time           : 880 ms (0.880 ms/per)
Max RSS        : 1100 kB
Shared RSS     : 0 kB
Unshared Data  : 0
Unshared Stack : 0
Page reclaims  : 112164
Page faults    : 0
Swaps          : 0
Block inputs   : 0
Block outputs  : 0
Sigs received  : 0
vol ctx switches   : 0
invol ctx switches : 0

$ getr 100 $(which python3) -c ''
User time      : 1 s, 570000 us
System time    : 0 s, 810000 us
Time           : 2380 ms (23.800 ms/per)
Max RSS        : 6964 kB
Shared RSS     : 0 kB
Unshared Data  : 0
Unshared Stack : 0
Page reclaims  : 168356
Page faults    : 0
Swaps          : 0
Block inputs   : 0
Block outputs  : 9
Sigs received  : 0
vol ctx switches   : 0
invol ctx switches : 0

$ getr 100 $(which perl) -le ''
User time      : 0 s, 60000 us
System time    : 0 s, 260000 us
Time           : 320 ms (3.200 ms/per)
Max RSS        : 3040 kB
Shared RSS     : 0 kB
Unshared Data  : 0
Unshared Stack : 0
Page reclaims  : 48690
Page faults    : 0
Swaps          : 0
Block inputs   : 0
Block outputs  : 1
Sigs received  : 0
vol ctx switches   : 0
invol ctx switches : 0
```

## defects and room for improvement
- no $PATH resolution occurs
- output is lengthy and probably mostly uninteresting
- output is in an ad-hoc text format that machine consumers would need to parse manually
- only posix_spawn is used, but fork&exec might be preferred for timings more like a fork&exec-using application
- this command lacks a manpage
- 'getr' is probably a poor name
- kB and ms are always used even when number ranges might be easier to understand in MB or s, or GB or min:s
