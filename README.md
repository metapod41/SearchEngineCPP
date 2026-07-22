# Search Engine in C++

Building a search engine from scratch in modern C++.

Started: July 2026

<div align="center">

# SearchEngineCPP

### A Full-Stack Document Search Engine built from scratch in **C++**

Search through TXT and PDF documents using a custom-built search engine implementing an **Inverted Index**, **Trie**, **TF-IDF Ranking**, **Boolean Query Parsing**, **Phrase Search**, **Fuzzy Search**, and **Snippet Generation**.

React • Express • C++

![C++](https://img.shields.io/badge/C%2B%2B-17-blue)
![React](https://img.shields.io/badge/React-Frontend-61DAFB)
![Express](https://img.shields.io/badge/Express-Backend-green)
![License](https://img.shields.io/badge/License-MIT-orange)

</div>

---

# Overview

SearchEngineCPP is a search engine that indexes user-uploaded documents and retrieves the most relevant results using classical Information Retrieval algorithms.

Unlike applications that rely on existing search libraries, this project implements the core search algorithms from scratch in C++.

The frontend and backend act only as an interface—the actual search engine is completely implemented in C++.

---

# Features

## Document Support

- TXT Documents
- PDF Documents (automatic text extraction)

---

## Search Features

- Keyword Search
- Multi-word Search
- Phrase Search
- Boolean Queries
  - AND
  - OR
  - NOT
- Ranked Search (TF-IDF)
- Multi-word Autocomplete
- Fuzzy Search (Levenshtein Distance)
- Search Suggestions

---

## Result Features

- Ranked Results
- Keyword Highlighting
- Context Snippet Generation
- Filename Display

---

# Architecture

```text
                 React Frontend
                        │
                  HTTP Requests
                        │
                Express Backend
                        │
           PDF → Text Conversion
                        │
                SearchEngine.exe
                        │
      ┌────────────────────────────┐
      │       Search Engine         │
      │                             │
      │  Tokenizer                  │
      │  Inverted Index             │
      │  Trie                       │
      │  Query Parser               │
      │  Boolean Evaluator          │
      │  TF-IDF Ranker              │
      │  Fuzzy Search               │
      │  Snippet Generator          │
      └────────────────────────────┘
```

---

# Algorithms Implemented

## Tokenization

- Lowercasing
- Punctuation Removal
- Word Extraction

---

## Inverted Index

Stores

```text
word
   ↓
document id
   ↓
positions
```

Example

```text
compiler

↓

Document 2 → [15,29]
Document 5 → [4,18]
Document 9 → [91]
```

---

## Trie

Used for

- Prefix Search
- Autocomplete
- Multi-word Autocomplete

Time Complexity

```text
O(length of prefix)
```

---

## TF-IDF Ranking

Ranking Score

```text
TF = termFrequency / documentLength

IDF = log(totalDocuments / documentFrequency)

Score = TF × IDF
```

Documents are sorted by decreasing score.

---

## Boolean Query Parsing

Supports

```text
compiler AND design

compiler OR parser

compiler AND NOT parser
```

using an Abstract Syntax Tree.

---

## Phrase Search

Supports

```text
"machine learning"

"compiler design"
```

using positional indexes.

---

## Fuzzy Search

Implemented using Levenshtein Distance.

Example

```text
compilor

↓

compiler
```

---

## Snippet Generation

Displays a small portion of text around the matched keyword.

Example

```text
...Explain the phases of a compiler by translating...
```

---

# Project Structure

```text
SearchEngineCPP/

│
├── backend/
│   ├── controllers/
│   ├── routes/
│   ├── services/
│   └── uploads/
│
├── frontend/
│   ├── src/
│   └── public/
│
├── data/
│
├── tokenizer/
├── index/
├── search/
├── models/
│
└── main.cpp
```

---

# How it Works

1. Upload TXT or PDF documents.
2. PDFs are converted into plain text.
3. The C++ engine indexes every document.
4. Queries are parsed.
5. TF-IDF scores are computed.
6. Results are ranked.
7. Snippets are generated.
8. Matching keywords are highlighted.

---

# Tech Stack

### Frontend

- React
- CSS

### Backend

- Node.js
- Express
- Multer

### Core Engine

- Modern C++17
- STL

---

# Screenshots

## Home

> *(Add screenshot here)*

---

## Upload

> *(Add screenshot here)*

---

## Search Results

> *(Add screenshot here)*

---

## Highlighting

> *(Add screenshot here)*

---

# Complexity

| Component | Complexity |
|------------|------------|
| Tokenization | O(n) |
| Index Construction | O(total words) |
| Trie Search | O(prefix length) |
| Boolean Search | O(result size) |
| Phrase Search | O(total positions) |
| TF-IDF Ranking | O(m log m) |
| Fuzzy Search | O(dictionary × word length²) |

---

# Future Improvements

- BM25 Ranking
- Incremental Indexing
- Stop-word Removal
- Stemming
- Wildcard Queries
- Parallel Index Construction
- Persistent Index Storage

---

# Key Learnings

While building this project, I learned

- Information Retrieval
- Search Engine Architecture
- Trie Data Structure
- TF-IDF Ranking
- Levenshtein Distance
- Boolean Query Parsing
- React ↔ Express ↔ C++ Integration
- File Upload Pipelines
- PDF Text Extraction

---

# Why This Project?

Most search applications use existing search libraries such as Elasticsearch or Lucene.

The goal of this project was different.

The objective was to understand how a search engine works internally by implementing the core algorithms from scratch.

---

# Contributing

Contributions, suggestions, and improvements are welcome.

Feel free to fork the repository and open a pull request.

---

# License

This project is licensed under the MIT License.

---
