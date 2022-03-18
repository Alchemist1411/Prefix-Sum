#include <hpx/hpx.hpp>
#include <hpx/hpx_init.hpp>


// #include <iostream>
// #include <chrono>
// #include <vector>
#include <bits/stdc++.h>


using array_vector = std::vector<std::uint64_t>;
using time_result  = std::pair<std::chrono::duration<double>, array_vector>;

// Sequential
time_result prefixSum_seq(std::uint64_t n, const array_vector& input, const array_vector& output)
{
    array_vector result(n);
    result[0] = input[0];

    auto startTime = std::chrono::high_resolution_clock::now();

    for (int i = 1; i < n; i++)
    {
        result[i] = result[i - 1] + input[i];
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_taken = (endTime - startTime)*1000;


    /* Just for printing the result[n]
    for (int i = 0; i < n; i++)
        std::cout << result[i] << " ";

    std::cout << std::endl;
    */
    
    return std::make_pair(time_taken, result);
}


// Parallel
time_result prefixSum_par(const uint64_t n, const array_vector& input, const array_vector& output)
{
    array_vector result(n);
    result[0] = input[0];

    auto startTime = std::chrono::high_resolution_clock::now();

    hpx::experimental::for_loop(hpx::execution::par, 1, n, [&](auto j) 
                    { result[j] = result[j - 1] + input[j]; });

    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_taken = (endTime - startTime)*1000;

    /* Just for printing the result[n]
    for (int i = 0; i < n; i++)
        std::cout << result[i] << " ";

    std::cout << std::endl;
    */
    return std::make_pair(time_taken, result);
}


int hpx_main(hpx::program_options::variables_map& vm)
{
    std::uint64_t n = vm["n"].as<std::uint64_t>();

    array_vector input(n); 
    for (uint64_t i; i < n; i++)
    {
        input[i] = 5;
    }
    array_vector output(n); 

    auto seq_res = prefixSum_seq(n, input, output);
    auto par_res = prefixSum_par(n, input, output);

    std::cout << "Time required in Sequential : " << seq_res.first.count()<< "ms\n";
    std::cout << "Time required in Parallel   : " << par_res.first.count()<< "ms\n";

    return hpx::finalize();
}

int main(int argc, char* argv[])
{
    using namespace hpx::program_options;

    options_description desc_commandline;
    desc_commandline.add_options()(
        "n", value<std::uint64_t>()->default_value(10000000), "Array Size");

    hpx::init_params init_args;
    init_args.desc_cmdline = desc_commandline;

    return hpx::init(argc, argv, init_args);
}