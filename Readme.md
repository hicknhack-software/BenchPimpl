# BenchPimpl

Benchmark Collection for different private implementation (pimpl) solutions in C++.

Benefits of Pimpl:
* lower recompile times. More changes can be made that have no global impact.
* allow more ABI compatible changes. (Used intensively by Qt)
* better optimizations. (implementation is used more locally)
* better seaparation of API and internals

## Benchmarked Pimpl Variants

### Plain

No Pimpl usage at all.

* [x] fastest. (This is the baseline for the benchmarks)
* [ ] no implementation hiding

### UniquePimpl

`std::unique_ptr` based Pimpl.

* [x] implementation is hidden
* [x] allows derived implementation
* [x] allows non implementation aware derived classes
* [ ] requires one allocation for the private implementation

### SharedPimpl

`std::shared_ptr` based Pimpl.

* [x] implementation is hidden
* [x] allows derived implementation
* [x] allows non implementation aware derived classes
* [x] may be used for copy on write implementations (not implemented)
* [ ] requires one allocation for the private implementation
* [ ] requires maintanance of reference counters

### ChainedPimpl

allocates memory for interface and pimpl in one block.

* [x] implementation is hidden
* [x] offset between implementation and interface is known
* [x] allows non implementation aware derived classes
* [ ] no derived implementations allowed
* [ ] much more involved code basis
* [ ] requires custom allocator methods

### ChainedDeleterPimpl

allows derived implementations

* [x] implementation is hidden
* [x] offset between implementation and interface is known
* [x] allows derived implementation
* [x] allows non implementation aware derived classes
* [ ] much more involved code basis
* [ ] requires custom allocator methods
* [ ] requires custom destruct methods

## Results

### Visual Studio 2015.2

```
Run on (1 X 2595.25 MHz CPU )
05/17/16 16:15:54
Benchmark             Time(ns)    CPU(ns) Iterations
----------------------------------------------------
Plain                       62         63   11200000
SharedPlain                 87         87    8960000
UniquePimpl                124        126    5600000
SharedPimpl                172        173    4072727
BenchChainedPimpl           76         77   11200000
SharedChainedPimpl         108        109    7466667
ChainedDeleterPimpl         71         71   11200000
```

### MinGW 4.9.2

```
Run on (1 X 2594.78 MHz CPU )
05/17/16 16:23:14
Benchmark             Time(ns)    CPU(ns) Iterations
----------------------------------------------------
Plain                       66         66    8960000
SharedPlain                 80         80    8960000
UniquePimpl                130        131    5600000
SharedPimpl                167        165    4072727
BenchChainedPimpl           83         84    8960000
SharedChainedPimpl          94         94    7466667
ChainedDeleterPimpl         68         68    8960000
```

The benchmark is very allocation dependant.
Bigger objects that live longer should see a much lower impact.

ChainedPimpl is almost as fast as plain implementations.

## License

Apache License Version 2.0
See LICENSE file for more details
