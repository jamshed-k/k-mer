
#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP



#include "Kmer.hpp"
#include "kseq/kseq.h"

#include <string>
#include "zlib.h"


// Declare the type of file handler and the read() function.
// Required for FASTA/FASTQ file reading using the kseq library.
KSEQ_INIT(int, read);


// This is the class for your top-level algorithm, and it is
// required to be templatized on the k-parameter. The example
// class defined here just functions as a printer for the
// lexicographically maximum canonical k-mer of the provided
// reference file (at the constructor).
template <uint16_t k>
class Algorithm
{
private:

    constexpr static char PLACEHOLDER_NUCLEOTIDE = 'N';

    // Name of the file containing the reference to be processed.
    std::string ref_file_name;


    // Processes the sequence `seq` of length `seq_len`.
    Kmer<k> process_sequence(const char* const seq, const size_t seq_len) const;

    // Returns the index of the first valid k-mer, i.e. the first k-mer without
    // the placeholder nucleotide 'N', in the index range `[left_end, right_end]`
    // of the sequence `seq`. If no such k-mer is found, returns the first invalid
    // index after its assigned range, i.e. `right_end + 1`.
    size_t search_valid_kmer(const char* const seq, const size_t left_end, const size_t right_end) const;


public:

    Algorithm(const std::string& ref_file_name): ref_file_name(ref_file_name)
    {}

    // Processes the reference at the file named `ref_file_name`.
    void process() const;
};


template <uint16_t k>
inline Kmer<k> Algorithm<k>::process_sequence(const char* const seq, const size_t seq_len) const
{
    Kmer<k> max_kmer;

    size_t kmer_idx = 0;
    while(kmer_idx <= seq_len - k)
    {
        kmer_idx = search_valid_kmer(seq, kmer_idx, seq_len - k);

        if(kmer_idx > seq_len - k)
            break;

        
        Kmer<k> kmer(seq, kmer_idx);
        Kmer<k> rev_compl = kmer.reverse_complement();

        while(true)
        {
            max_kmer = std::max(max_kmer, kmer.canonical(rev_compl));

            if(kmer_idx + k == seq_len || seq[kmer_idx + k] == PLACEHOLDER_NUCLEOTIDE)
            {
                // Advance the running index to a next potential location.
                kmer_idx += (k + 1);
                break;
            }
            
            kmer.roll_to_next_kmer(seq[kmer_idx + k], rev_compl);
            kmer_idx++;
        }
    }


    return max_kmer;
}


template <uint16_t k>
size_t Algorithm<k>::search_valid_kmer(const char* const seq, const size_t left_end, const size_t right_end) const
{
    size_t valid_start_idx;
    uint16_t nucl_count;
    

    size_t idx = left_end;
    while(idx <= right_end)
    {
        // Go over the contiguous subsequence of 'N's.
        for(; idx <= right_end && seq[idx] == PLACEHOLDER_NUCLEOTIDE; idx++);

        // Go over the contiguous subsequence of non-'N's.
        if(idx <= right_end)
        {
            valid_start_idx = idx;
            nucl_count = 0;

            for(; idx <= right_end + k - 1 && seq[idx] != PLACEHOLDER_NUCLEOTIDE; ++idx)
                if(++nucl_count == k)
                    return valid_start_idx;
        }
    }


    return right_end + 1;
}


template <uint16_t k>
inline void Algorithm<k>::process() const
{
    // Open the file handler for the FASTA / FASTQ file containing the reference.
    FILE* input = fopen(ref_file_name.c_str(), "r");
    if(input == NULL)
    {
        std::cerr << "Error opening input file " << ref_file_name << ". Aborting.\n";
        std::exit(EXIT_FAILURE);
    }

    
    // Initialize the parser.
    kseq_t* parser = kseq_init(fileno(input));


    // Parse sequences one-by-one, and continue processing through them.
    Kmer<k> max_kmer;
    uint32_t seqCount = 0;
    while(kseq_read(parser) >= 0)
    {
        const char* const seq = parser->seq.s;
        const size_t seq_len = parser->seq.l;

        std::cout << "Processing sequence " << ++seqCount << ", with length " << seq_len << ".\n";

        // Nothing to process for sequences with length shorter than `k`.
        if(seq_len < k)
            continue;

        
        max_kmer = std::max(max_kmer, process_sequence(seq, seq_len));
    }


    std::cout << "Lexicographically maximum k-mer (canonical): " << max_kmer << "\n";
}



#endif
