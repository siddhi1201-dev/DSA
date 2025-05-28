# Plagiarism Detector in C (Using Hashing)

 Overview

This is a simple **Plagiarism Detection Tool** implemented in **C**, designed to compare multiple text files and detect similarities using **hashing techniques**. It helps identify potential plagiarism by analyzing word or phrase overlaps between files.

 How It Works

- Each file is read and tokenized into words or n-grams.
- Each word or n-gram is hashed using a custom or standard hash function.
- A hash table is used to keep track of occurrences.
- Similarity scores are computed based on common hashes between documents.

 Features

- Fast file comparison using hash-based lookup
- Adjustable n-gram size for more accurate comparison
- Command-line interface
- Outputs similarity scores between file pairs
