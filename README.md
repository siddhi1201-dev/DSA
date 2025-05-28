Plagiarism Detector in C (Using Custom Hashing)
Overview
This is a lightweight Plagiarism Detection Tool implemented in C, designed to compare multiple text files and identify similarities by leveraging a custom hashing technique. Instead of using standard hashing algorithms, it employs a simple and efficient bit-shift based hash function (e.g., using << 5) to generate hash values for words or n-grams. This method helps detect overlapping content quickly and with low computational overhead.

How It Works
Reads each input file and tokenizes the text into words or adjustable-sized n-grams.
Applies a custom hash function that uses bitwise operations (such as shifting bits left by 5) to convert tokens into hash values.
Stores these hashes in a hash table to track occurrences across documents.
Compares documents by counting the number of shared hashes, calculating a similarity score based on overlapping content.
Outputs similarity scores that help identify potential plagiarism or content reuse.

Features
Fast and lightweight file comparison using a custom bit-shift based hashing method.
Adjustable n-gram size for fine-tuning similarity detection.
Simple command-line interface.
Outputs clear similarity scores between pairs of files.
Scales to multiple files efficiently.