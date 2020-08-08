# k-mer

### An attempt on designing an arbitrary length k-mer class, and to statically generate the codes of the classes for all k-values at compile-time using template metaprogramming

To use the correct and statically compiled _k_-mer class code for any of your required _k_-values (provided at runtime) in your algorithm, you need to:

- modify the `Program_Params` class to include the fields to be passed to your algorithm as input parameters;
- and define the two public methods (the constructor `Algorithm<k>(const Program_Params&)` and the algorithm executor `execute()`) in the `Algorithm` class as per your requirement.

The `Application` class should be able to take care of everything in order to use the correct statically compiled _k_-mer class throughout the code.

Fix the maximum possible value of `k` that you anticipate to be possibly used by the algorithm, and the invokation should go like this:

```cpp
constexpr uint16_t MAX_K = 512; // Fixing the max k-value

const Program_Params params(/* input parameters */);  // Instantiate a parameters wrapper with the required input

Application<MAX_K> app(params); // Instatiate the top-level driver application

app.execute();  // Invoke your algorithm
```

## Compile and run the example algorithm

(out-of-source build)

```bash
mkdir build && cd build
cmake ..
make install
```

(executing from the project directory)

```bash
./bin/k_mer <ref_file> <k>
```

## Overview

More specifically, the classes that support the entire stuff:

- The [`Kmer<k>`](https://github.com/jamshed-k/k-mer/blob/master/include/Kmer.hpp) class is the arbitrary length _k_-mer class (with a non-templated base class `Kmer_Utility`).

- The [`Algorithm<k>`](https://github.com/jamshed-k/k-mer/blob/master/include/Algorithm.hpp) class should either just invoke your algorithm or contain its implementation. Your algorithm and anywhere you used _k_-mers need to be templatized on `k`. An example algorithm implementation is provided at the class that given a reference file name, prints out the lexicographically largest canonical _k_-mer present at the reference. You can safely strip all the private members of the `Algorithm` class off, and only need to define the public constructor and the top-level driver method `execute()` for your algorithm, and add whatever else necessary to the class.

- The [`Application`](https://github.com/jamshed-k/k-mer/blob/master/include/Application.hpp) class generates the concrete code (specifically, a hierarchy of classes ordered on `k`) for all possible _k_-values (in the context of your algorithm), and dynamically selects which of these statically compiled classes need to be used throughout the algorithm.

For very large _k_-values, typical compilation approaches can fail, and you should try using `-ftemplate-depth=` to increase the maximum template instantiation depth. Please note that, the higher the `MAX_K` values are set, the more expensive the compilations become.
